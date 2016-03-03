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


#ifndef INCLUDED_CRYPTO_SYM_CIPH_DESC_H
#define INCLUDED_CRYPTO_SYM_CIPH_DESC_H

#include <crypto/api.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

namespace gr {
  namespace crypto {

    /*!
     * \brief <+description+>
     *
     */
    class CRYPTO_API sym_ciph_desc
    {
    public:
      sym_ciph_desc(const std::string ciph_name, bool padding);
      ~sym_ciph_desc();
        const EVP_CIPHER* get_evp_ciph(){return d_evp_ciph;};
        bool get_padding(){return d_padding;};
    private:
        const EVP_CIPHER *d_evp_ciph;
        bool d_padding;
    };

  } // namespace crypto
} // namespace gr

#endif /* INCLUDED_CRYPTO_SYM_CIPH_DESC_H */
