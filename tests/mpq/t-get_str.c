/* Test mpq_get_str.

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
MA 02111-1307, USA.
*/

#include <stdio.h>
#include "gmp.h"
#include "gmp-impl.h"
#include "tests.h"


void
check_one (mpq_srcptr q, int base, const char *want)
{
  char    *str, *ret;
  size_t  str_alloc;
  
  MPQ_CHECK_FORMAT (q);
  mp_trace_base = base;

  str_alloc =
    mpz_sizeinbase (mpq_numref(q), base) +
    mpz_sizeinbase (mpq_denref(q), base) + 3;
  
  str = mpq_get_str (NULL, base, q);
  if (strlen(str)+1 > str_alloc)
    {
      printf ("mpq_get_str size bigger than should be (passing NULL)\n");
      printf ("  got  size %u \"%s\"\n", strlen(str)+1, str);
      printf ("  want size %u\n", str_alloc);
      abort ();
    }
  if (strcmp (str, want) != 0)
    {
      printf ("mpq_get_str wrong (passing NULL)\n");
      printf ("  got  \"%s\"\n", str);
      printf ("  want \"%s\"\n", want);
      mpq_trace ("  q", q);
      abort ();
    }
  (*__gmp_free_func) (str, strlen (str) + 1);
  
  str = (char *) (*__gmp_allocate_func) (str_alloc);
  
  ret = mpq_get_str (str, base, q);
  if (str != ret)
    {
      printf ("mpq_get_str wrong return value (passing non-NULL)\n");
      printf ("  got  0x%lX\n", (unsigned long) ret);
      printf ("  want 0x%lX\n", (unsigned long) want);
      abort ();
    }
  if (strcmp (str, want) != 0)
    {
      printf ("mpq_get_str wrong (passing non-NULL)\n");
      printf ("  got  \"%s\"\n", str);
      printf ("  want \"%s\"\n", want);
      abort ();
    }
  (*__gmp_free_func) (str, str_alloc);
}


void
check_data (void)
{
  static const struct {
    int         base;
    const char  *num;
    const char  *den;
    const char  *want;
  } data[] = {
    { 10, "0", "1", "0" },
    { 10, "1", "1", "1" },

    { 16, "FFFFFFFF", "1", "ffffffff" },
    { 16, "FFFFFFFFFFFFFFFF", "1", "ffffffffffffffff" },

    { 16, "1", "FFFFFFFF", "1/ffffffff" },
    { 16, "1", "FFFFFFFFFFFFFFFF", "1/ffffffffffffffff" },
    { 16, "1", "10000000000000003", "1/10000000000000003" },

    { 10, "12345678901234567890", "9876543210987654323",
      "12345678901234567890/9876543210987654323" },
  };

  mpq_t  q;
  int    i;

  mpq_init (q);
  for (i = 0; i < numberof (data); i++)
    {
      mpz_set_str_or_abort (mpq_numref(q), data[i].num, data[i].base);
      mpz_set_str_or_abort (mpq_denref(q), data[i].den, data[i].base);
      check_one (q, data[i].base, data[i].want);
    }
  mpq_clear (q);
}


int
main (void)
{
  tests_start ();

  check_data ();

  tests_end ();
  exit (0);
}