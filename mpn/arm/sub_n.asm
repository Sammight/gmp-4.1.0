dnl  ARM mpn_sub_n -- Subtract two limb vectors of the same length > 0 and
dnl  store difference in a third limb vector.
dnl  Contributed by Robert Harley.

dnl  Copyright 1997, 2000, 2001 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 2.1 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
dnl  the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
dnl  MA 02111-1307, USA.

include(`../config.m4')

C This code runs at 5 cycles/limb.

define(`rp',`r0')
define(`up',`r1')
define(`vp',`r2')
define(`n',`r3')

define(`sp',`r13')
define(`lr',`r14')
define(`pc',`r15')

changecom(@)	C need this since # is used for constants

ASM_START()
PROLOGUE(mpn_sub_n)
	stmfd	sp!, { r8, r9, lr }
	subs	r12, r12, r12
	tst	n, #1
	beq	skip1
	ldr	r12, [up], #4
	ldr	lr, [vp], #4
	subs	r12, r12, lr
	str	r12, [rp], #4
skip1:
	tst	n, #2
	beq	skip2
	ldmia	up!, { r8, r9 }
	ldmia	vp!, { r12, lr }
	sbcs	r8, r8, r12
	sbcs	r9, r9, lr
	stmia	rp!, { r8, r9 }
skip2:
	bics	n, n, #3
	beq	return
	stmfd	sp!, { r4, r5, r6, r7 }
sub_n_loop:
	ldmia	up!, { r4, r5, r6, r7 }
	ldmia	vp!, { r8, r9, r12, lr }
	sbcs	r4, r4, r8
	ldr	r8, [rp, #12]			C cache allocate
	sbcs	r5, r5, r9
	sbcs	r6, r6, r12
	sbcs	r7, r7, lr
	stmia	rp!, { r4, r5, r6, r7 }
	sub	n, n, #4
	teq	n, #0
	bne	sub_n_loop
	ldmfd	sp!, { r4, r5, r6, r7 }
return:
	sbc	r0, r0, r0
	and	r0, r0, #1
	ldmfd	sp!, { r8, r9, pc }
EPILOGUE(mpn_sub_n)