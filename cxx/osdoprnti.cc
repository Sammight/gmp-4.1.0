/* __gmp_doprnt_integer_ios -- integer formatted output to an ostream.

   THE FUNCTIONS IN THIS FILE ARE FOR INTERNAL USE ONLY.  THEY'RE ALMOST
   CERTAIN TO BE SUBJECT TO INCOMPATIBLE CHANGES OR DISAPPEAR COMPLETELY IN
   FUTURE GNU MP RELEASES.

Copyright 2001 Free Software Foundation, Inc.

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

#include <iostream.h>
#include <stdarg.h>    /* for va_list and hence doprnt_funs_t */
#include <string.h>

#include "gmp.h"
#include "gmp-impl.h"

#include <stdio.h>


/* The gmp_asprintf support routines never give an error, so
   __gmp_doprnt_mpf shouldn't fail and it's return can just be checked with
   an ASSERT.  */

ostream&
__gmp_doprnt_integer_ostream (ostream &o, const struct doprnt_params_t *p,
                              char *s)
{
  struct gmp_asprintf_t   d;
  char  *result;
  int   ret;

  GMP_ASPRINTF_T_INIT (d, &result);
  ret = __gmp_doprnt_integer (&__gmp_asprintf_funs_noformat, &d, p, s);
  ASSERT (ret != -1);
  __gmp_asprintf_final (&d);
  (*__gmp_free_func) (s, strlen(s)+1);

  gmp_allocated_string alloc = result;
  return o.write (result, strlen (result));
}