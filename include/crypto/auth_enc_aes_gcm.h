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


#ifndef INCLUDED_CRYPTO_AUTH_ENC_AES_GCM_H
#define INCLUDED_CRYPTO_AUTH_ENC_AES_GCM_H

#include <crypto/api.h>
#include <gnuradio/block.h>
#include <stdexcept>
#include <stdint.h>
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/rand.h>

namespace gr {
  namespace crypto {

    /*!
     * \brief <+description of block+>
     * \ingroup crypto
     *
     */
    class CRYPTO_API auth_enc_aes_gcm : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<auth_enc_aes_gcm> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of crypto::auth_enc_aes_gcm.
       *
       * To avoid accidental use of raw pointers, crypto::auth_enc_aes_gcm's
       * constructor is in a private implementation
       * class. crypto::auth_enc_aes_gcm::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::vector<uint8_t> key, int keylen, int ivlen);
    };

  } // namespace crypto
} // namespace gr

#endif /* INCLUDED_CRYPTO_AUTH_ENC_AES_GCM_H */

