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

#ifndef INCLUDED_CRYPTO_SYM_DEC_IMPL_H
#define INCLUDED_CRYPTO_SYM_DEC_IMPL_H

#include <crypto/sym_dec.h>
#include <crypto/sym_ciph_desc.h>

namespace gr {
  namespace crypto {

    class sym_dec_impl : public sym_dec
    {
     private:
      // Nothing to declare in this block.

     public:
      sym_dec_impl(sym_ciph_desc &ciph_desc);
      ~sym_dec_impl();

    };

  } // namespace crypto
} // namespace gr

#endif /* INCLUDED_CRYPTO_SYM_DEC_IMPL_H */
