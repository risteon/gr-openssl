/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H
#define INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H

#include <crypto/sym_enc_tagged_bb.h>
#include <crypto/sym_ciph_desc.h>
#include <fstream>
#include <stdexcept>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>


namespace gr {
  namespace crypto {

    class sym_enc_tagged_bb_impl : public sym_enc_tagged_bb
    {
     private:
        const EVP_CIPHER* d_ciph;
        EVP_CIPHER_CTX* d_ciph_ctx;


        std::vector<unsigned char> d_key;
        std::vector<unsigned char> d_iv;

        int d_key_len;
        int d_iv_len;
        int d_block_size;

        pmt::pmt_t d_iv_key;
        pmt::pmt_t d_iv_pmt;
        pmt::pmt_t d_new_iv_key;

    protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      sym_enc_tagged_bb_impl(const std::string keyfilename, const std::string cipher, const std::string& key_len);
      ~sym_enc_tagged_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace crypto
} // namespace gr

#endif /* INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H */
