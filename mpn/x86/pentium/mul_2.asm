dnl  Intel Pentium mpn_mul_2 -- mpn by limb multiplication.
dnl
dnl  P5: 24.0 cycles/limb

dnl  Copyright 2001 Free Software Foundation, Inc.
dnl 
dnl  This file is part of the GNU MP Library.
dnl 
dnl  The GNU MP Library is free software; you can redistribute it and/or
dnl  modify it under the terms of the GNU Lesser General Public License as
dnl  published by the Free Software Foundation; either version 2.1 of the
dnl  License, or (at your option) any later version.
dnl 
dnl  The GNU MP Library is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl  Lesser General Public License for more details.
dnl 
dnl  You should have received a copy of the GNU Lesser General Public
dnl  License along with the GNU MP Library; see the file COPYING.LIB.  If
dnl  not, write to the Free Software Foundation, Inc., 59 Temple Place -
dnl  Suite 330, Boston, MA 02111-1307, USA. */

include(`../config.m4')


C mp_limb_t mpn_mul_2 (mp_ptr dst, mp_srcptr src, mp_size_t size,
C                      mp_limb_t mult_low, mp_limb_t mult_high);
C
C At 24 c/l this is only 2 cycles faster than a separate mul_1 and addmul_1,
C but has the advantage of making just one pass over the operands.

defframe(PARAM_MULT_HIGH,20)
defframe(PARAM_MULT_LOW, 16)
defframe(PARAM_SIZE,     12)
defframe(PARAM_SRC,       8)
defframe(PARAM_DST,       4)

	TEXT
	ALIGN(8)
PROLOGUE(mpn_mul_2)
deflit(`FRAME',0)

	pushl	%esi		FRAME_pushl()
	pushl	%edi		FRAME_pushl()

	movl	PARAM_SRC, %esi
	movl	PARAM_DST, %edi

	movl	PARAM_SIZE, %ecx
	xorl	%eax, %eax		C initial low product

	pushl	%ebx		FRAME_pushl()
	pushl	%ebp		FRAME_pushl()

	leal	(%esi,%ecx,4), %esi	C src end
	leal	(%edi,%ecx,4), %edi	C dst end

	negl	%ecx			C -size

	xorl	%ebx, %ebx		C initial low carry
	xorl	%ebp, %ebp		C initial high carry

	xorl	%edx, %edx		C initial high product


L(top):
	C eax	low prod
	C ebx	low carry
	C ecx	counter, negative
	C edx	high prod
	C esi	src end
	C edi	dst end
	C ebp	high carry (0 or -1)

	andl	$1, %ebp		C 1 or 0
	addl	%eax, %ebx

	adcl	%edx, %ebp
	ASSERT(nc)
	movl	(%esi,%ecx,4), %eax

	mull	PARAM_MULT_LOW

	addl	%eax, %ebx		C low carry
	movl	(%esi,%ecx,4), %eax

	adcl	%ebp, %edx		C high carry
	movl	%ebx, (%edi,%ecx,4)

	sbbl	%ebp, %ebp		C new high carry, -1 or 0
	movl	%edx, %ebx		C new low carry

	mull	PARAM_MULT_HIGH

	incl	%ecx
	jnz	L(top)



	andl	$1, %ebp		C 1 or 0
	addl	%ebx, %eax

	adcl	%ebp, %edx
	ASSERT(nc)
	movl	%eax, (%edi)		C store carry low

	movl	%edx, %eax		C return carry high

	popl	%ebp
	popl	%ebx

	popl	%edi
	popl	%esi

	ret

EPILOGUE()