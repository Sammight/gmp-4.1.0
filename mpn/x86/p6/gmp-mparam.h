/* Intel P6 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */


#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4
#define BITS_PER_LONGINT 32
#define BITS_PER_INT 32
#define BITS_PER_SHORTINT 16
#define BITS_PER_CHAR 8


#ifndef UMUL_TIME
#define UMUL_TIME   5   /* cycles */
#endif
#ifndef UDIV_TIME
#define UDIV_TIME   39  /* cycles */
#endif

/* A test with gcc 2.95.2 on mpn_sb_divrem_mn suggests that in practice
   udiv_qrnnd_preinv is about 10 cycles faster than plain udiv_qrnnd. */
#ifndef UDIV_NORM_PREINV_TIME
#define UDIV_NORM_PREINV_TIME   31 /* cycles */
#endif

#ifndef COUNT_TRAILING_ZEROS_TIME
#define COUNT_TRAILING_ZEROS_TIME   2  /* cycles */
#endif


/* Generated by tuneup.c, 2000-10-27. */

#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD     23
#endif
#ifndef TOOM3_MUL_THRESHOLD
#define TOOM3_MUL_THRESHOLD        177
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD     56
#endif
#ifndef TOOM3_SQR_THRESHOLD
#define TOOM3_SQR_THRESHOLD        166
#endif

#ifndef DC_THRESHOLD
#define DC_THRESHOLD               117
#endif

#ifndef FIB_THRESHOLD
#define FIB_THRESHOLD               97
#endif

#ifndef POWM_THRESHOLD
#define POWM_THRESHOLD             159
#endif

#ifndef GCD_ACCEL_THRESHOLD
#define GCD_ACCEL_THRESHOLD          3
#endif
#ifndef GCDEXT_THRESHOLD
#define GCDEXT_THRESHOLD            54
#endif

#ifndef FFT_MUL_TABLE
#define FFT_MUL_TABLE  { 592, 1568, 2688, 6656, 14336, 40960, 0 }
#endif
#ifndef FFT_MODF_MUL_THRESHOLD
#define FFT_MODF_MUL_THRESHOLD     656
#endif
#ifndef FFT_MUL_THRESHOLD
#define FFT_MUL_THRESHOLD         5888
#endif

#ifndef FFT_SQR_TABLE
#define FFT_SQR_TABLE  { 688, 1632, 3200, 6656, 18432, 57344, 0 }
#endif
#ifndef FFT_MODF_SQR_THRESHOLD
#define FFT_MODF_SQR_THRESHOLD     704
#endif
#ifndef FFT_SQR_THRESHOLD
#define FFT_SQR_THRESHOLD         5888
#endif
