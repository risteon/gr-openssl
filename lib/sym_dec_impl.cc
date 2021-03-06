/* -*- c++ -*- */
/* 
 * Copyright 2016 Kristian Maier.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "sym_dec_impl.h"

namespace gr {
    namespace crypto {

        sym_dec::sptr
        sym_dec::make(sym_ciph_desc &ciph_desc)
        {
            return gnuradio::get_initial_sptr
                    (new sym_dec_impl(ciph_desc));
        }

        /*
         * The private constructor
         */
        sym_dec_impl::sym_dec_impl(sym_ciph_desc &ciph_desc)
                : gr::block("sym_dec",
                            gr::io_signature::make(0, 0, 0),
                            gr::io_signature::make(0, 0, 0))
        {
            d_iv_id = pmt::mp("iv");
            d_final_id = pmt::mp("final");

            message_port_register_out(pmt::mp("pdus"));
            message_port_register_in(pmt::mp("pdus"));
            set_msg_handler(pmt::mp("pdus"), boost::bind(&sym_dec_impl::msg_handler, this, _1));

            sym_ciph_desc *desc = &ciph_desc;
            d_ciph = desc->get_evp_ciph();
            d_iv.assign(d_ciph->iv_len, 0);
            d_key = desc->get_key();
            d_padding = desc->get_padding();

            d_ciph_ctx = EVP_CIPHER_CTX_new();

            //initialize decryption if no need for iv
            d_have_iv = false || (d_ciph->iv_len == 0);
            if (d_have_iv) {
                init_ctx();
            }
        }


        void
        sym_dec_impl::init_ctx(){
            if (1 != EVP_DecryptInit_ex(d_ciph_ctx, d_ciph, NULL, &d_key[0], &d_iv[0])) {
                ERR_print_errors_fp(stdout);
            }
            if (1 != EVP_CIPHER_CTX_set_padding(d_ciph_ctx, d_padding)) {
                ERR_print_errors_fp(stdout);
            }
        }

        void
        sym_dec_impl::msg_handler(pmt::pmt_t msg)
        {
            if (!pmt::is_pair(msg)) {
                throw std::runtime_error("sym_dec received non PDU input");
            }
            pmt::pmt_t meta = pmt::car(msg);
            pmt::pmt_t data = pmt::cdr(msg);

            if (pmt::is_null(meta)) {
                meta = pmt::make_dict();
            }
            else if (!pmt::is_dict(meta)) {
                throw std::runtime_error("sym_dec received non PDU input");
            }

            //iv received?
            pmt::pmt_t iv_val = pmt::dict_ref(meta, d_iv_id, pmt::PMT_NIL);
            if (pmt::is_u8vector(iv_val) && pmt::length(iv_val) == d_ciph->iv_len) {

                //final flag was not set before new iv -> output remaining bytes in extra msg, maybe unwanted?
                if(d_have_iv){
                    d_out_buffer.reserve(d_ciph->block_size);
                    int nout=0;
                    if (1 != EVP_DecryptFinal_ex(d_ciph_ctx, &d_out_buffer[0], &nout)) {
                        ERR_print_errors_fp(stdout);
                    }
                    if(nout){
                        message_port_pub(pmt::mp("pdus"), pmt::cons(pmt::make_dict(), pmt::init_u8vector(nout, d_out_buffer)));
                    }
                }

                d_iv = u8vector_elements(iv_val);
                d_have_iv = true;

                //remove iv from metadata
                meta = pmt::dict_delete(meta, d_iv_id);

                //init dec with new iv
                init_ctx();
            }

            if (pmt::is_u8vector(data) && pmt::length(data) != 0) {
                size_t inlen = pmt::length(data);
                const unsigned char *in = u8vector_elements(data, inlen);
                d_out_buffer.reserve(inlen + 2*d_ciph->block_size);

                if (!d_have_iv) {
                    throw std::runtime_error("ERROR decryption without iv\n");
                }

                //decrypt
                int nout = 0;
                int tmp = 0;
                if (1 != EVP_DecryptUpdate(d_ciph_ctx, &d_out_buffer[0], &tmp, in, inlen)) {
                    ERR_print_errors_fp(stdout);
                }
                nout=tmp;

                if(pmt::dict_has_key(meta, d_final_id)){
                    if (1 != EVP_DecryptFinal_ex(d_ciph_ctx, &d_out_buffer[nout], &tmp)) {
                        ERR_print_errors_fp(stdout);
                    }
                    nout+=tmp;
                    //need iv in next msg
                    d_have_iv = false || (d_ciph->iv_len == 0);
                }

                data = pmt::init_u8vector(nout, d_out_buffer);
            }else {
                throw std::runtime_error("sym_dec pdu data field not byte vector with data");
            }

            //publish
            message_port_pub(pmt::mp("pdus"), pmt::cons(meta, data));


        }


        sym_dec_impl::~sym_dec_impl()
        {
            d_key.assign(d_ciph->key_len, 0);
            EVP_CIPHER_CTX_free(d_ciph_ctx);
        }


    } /* namespace crypto */
} /* namespace gr */

