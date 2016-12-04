/*
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 20160385 Oh Jinyoung
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	// A&B = ~((~A)|(~B))
	int a = ~x;
	int b = ~y;
	int c = a|b;
	int answr = ~c;
	return answr;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	int a = n << 3; // each byte is 8 bit
	x = x >> a; // delet MSBs
	x = x & 0x000000ff; // extract byte
	return x;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int b = (0x7F << 24) + (0xFF << 16) + (0xFF<< 8) + 0xFF; // to make 0x7FFFFFFF
	int a = x & b; // make MSB to 0
	int answr = a >> n; // arithmetic shift, but it is logical shift indeed. Because MSB is 0.
	int msb = (x >> 31) & 1; // origial MSB bit
	int mask = msb << 31 +( (~n) + 1);
	answr = answr | mask; // add original MSB bit
	return answr;
}
/*
 * bitCount - returns count of number of 1's in word

 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>

 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	int y, answr;
	y = 0x11 + (0x11<<8);
	y = y + (y << 16); // y == 0x 0001 0001 0001 0001 0001 0001...
	//printf("%x ",y);
	answr = x & y; // every 4n th bit
	answr += (x>>1) & y; // every 4n+1 th bit
	answr += (x>>2) & y; // every 4n+2 th bit
	answr += (x>>3) & y; // every 4n+3 th bit

	answr += answr >> 16; // LSB 16 bit has sum/sum/sum/sum [xxxx xxxx xxxx xxxx] (0 <= sum <= 0x1000)
	//printf("%x ",answr);
	y = 0xF;
	answr = ((answr >> 12)&y) + ((answr >> 8)&y) + ((answr >> 4)&y) + (answr&y); // sum 4 parts of sum
	//printf("%x\n",answr);

	//answr += answr >> 8;
	
	return answr & 0x3F; // maximum value of answr is 0x3F

	

	/*
	int y,z;
	int msb = (x>>31) & 1; // save msb. I'll make msb to 0 in order to logical shift
	
	z = x & ((0x55 << 24) + (0x55 << 16) + (0x55 << 8) + 0x55); // 2,4,6,8...th bit
	y = x + ~z + 2 + ~(msb << 31); // 1,3,5,7,...th bit

	y = y >> 1;
	x = y + z; //

	z = x & ((0x33 << 24) + (0x33 << 16) + (0x33 << 8) + 0x33);
	y = x + ~z + 1;

	y = y >> 2;
	x = y + z;

	z = x & ((0x0F << 24) + (0x0F << 16) + (0x0F << 8) + 0x0F);
	y = x + ~z + 1;

	y = y >> 4;
	x = y + z;

	z = x & ((0xFF<<16) + (0xFF));
	y = x + ~z + 1;

	y = y >> 8;
	x = y + z;
	
	z = x & ((0xFF<<8) + (0xFF));
	y = x + ~z +1;
	y = y >> 16;
	x = y + z;

	return x + msb; */
	/*int sum = 0;
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //2 
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //4
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //6
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //8
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //10
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //12
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //14
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //16
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //18
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //20
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //22
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //24
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //26
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //28
	sum += x & 1;	x = x >> 1;
	sum += x & 1;	x = x >> 1; //30
	sum += x & 1;	x = x >> 1; //31
	sum += x & 1; // check that if each bit is 1 while shifting bits
	return sum;
	*/
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int y = ~x + 1; // calculate x's two's complement
	// if and only if zero keeps it's MSB as zero
	int xmsb = (x >> 31) & 1;
	int ymsb = (y >> 31) & 1;
	int answr = xmsb | ymsb;
	answr = ~answr & 1; // to compute !
	return answr;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	int answr = (0x80 << 24);  // minimum two's complement integer is 0x80000000
	return answr;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int a =  32 + (~n + 1); // compute 32 - n
	int b = x << a;
	int answr;
	b = b >> a; // shift left and right again to check the variable keeps it's own value after shift.
	answr = x^b; // check
	return !answr;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int divpwr2(int x, int n) {
	int msb = (x >> 31) & 1; // get MSB
	int a = x << 33 + ~n; // to check remainder
	int answr;
	a = !!a; // make remainder to 1 in order to use for round up
	msb = msb & a;
	msb = msb & (!(!n)); // if n==0, round up for minus value of x is not computed
	answr += (x >> n)+msb; // divide and round up
	return answr;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	int answr = ~x +1; // in two's complement system, ~x +1 is a way to get -x
	return answr;

}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int msb = x>>31; // get MSB
	int chkzero = !x; // check that if x is zero
	int answr = msb | chkzero; // MSB is 1 when x<0. chkzero is 1 when x is zero.
	// Either negative or zero, answr will hass 1
	return !answr; // reverse answr to satisfy the problem's statement.
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int msb_x, msb_y, smsgn, sgn, smnbr, cmpr, answr;
	msb_x = (x >> 31)&1; // get MSB of x
	msb_y = (y >> 31)&1; // get MSB of y
	
	//compare x and y's MSB (are they have same sign?)
	smsgn = (msb_x ^ msb_y); // same sign = 0, different sign = 1
	// when their sign are different, variable with positive sign is bigger
	// so check that if y has positive sign
	sgn = smsgn & msb_x; // if y has positive sign and x has negative sign, sgn is 1
	// when sgn == 1, x is less than y so return value should be 1

	// compare x and y
	smnbr = ! (x ^ y); // same number = 1, different number = 0
	// when smnbr == 1, x is as same as y so return value should be 1

	// compare x and y when x and y have same sign
	// calculate x - y. but we can't calculate (0xF0000000's two's complement)
	y = ~y;// so just calculate ~y which means -y-1 
	cmpr = y+x; // x-y-1
	cmpr = (cmpr >> 31) & 1 & !smsgn; // when cmpr == 1, x <= y < y+1; when cmpr == 0, x >= y+1 > y
	// when cmpr == 1, x is less than y so return value should be 1

	answr = sgn | smnbr | cmpr;
	return answr;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int left, right, half1, half2, half3, half4, half5, answr;
	int a,b,c,d,e; // just variable for half1, half2, half3, half4

	// binary search algorithm to find leading 1
	left = x >> 16; // left 16 bits
	right = x & ((0xFF << 8) + 0xFF); // right 16 bits
	half1 = !!left; // == 1 when left 16 bit has 1, otherwise == 0
	a = (half1 << 31) >> 31; // fill all bits with 0 or 1
	// choose left or right bit for binary search
	x = (left & a) + (right & (~a));

	//<F5>printf("%x %x\n", half1, x);

	left = x >> 8; // left 8 bits
	right = x & 0xFF; // right 8 bits
	half2 = !!left; // works like half1
	b = (half2 << 31) >> 31;
	x = (left & b) + (right & (~b));
			
	//printf("%x %x\n", half2, x);

	left = x >> 4;
	right = x & 0xF;
	half3 = !!left;
	c = (half3 << 31) >> 31;
	x = (left & c) + (right & (~c));

	//printf("%x %x\n", half3, x);

	left = x >> 2;
	right = x & 0x3;
	half4 = !!left;
	d = (half4 << 31) >> 31;
	x = (left & d) + (right & (~d));

	//printf("%x %x\n", half4, x);
	
	left = x >> 1;
	right = x & 0x1;
	half5 = !!left;
	e = (half5 << 31) >> 31;
	x = (left & e) + (right & (~e));

	//printf("%x %x\n", half5, x);

	answr = (half1<<4) + (half2 <<3) + (half3<<2) + (half4<<1) + half5;
	return answr;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	int mask, answr, k;
	mask = (0x80 << 24);
	answr = uf ^ mask; // to change sign bit

	//exception for NaN
	//NaN == ?11111111xxx...x
	k = 0xFF << 23;
	if ((k&uf) == k){
		if ((uf << 9) != 0) {
			return uf; // by the definition of NaN
		}
	}
	
	//else
	return answr;

}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	int tmp, mask, mask2,  msb, exp, frac, intmin,i, answr;

	intmin = 0xCF000000;
	//exception
	if (x==0) return 0x0; //0 should be returned as 0
	if (x==0x80000000) return intmin; // exception for INT_MIN because there are no -INT_Min is int


	msb = (x >> 31) & 1 ;// save MSB (+,- sign)
	
	if(msb)	 x = -x; // make positive number

	// log_2(|x|)
	exp = 0 ;
	tmp = x;
	while(tmp/=2){
		
		exp++; // get exp value (log_2(|x|))
	}


	i = 0;
	
	mask = 1 << exp;
	x = x^mask;// frac is 1.xxxx and what we should account is only xxxx, so neglet 1.
	
	//printf("%d ", exp);
	if (exp<23){
		mask = 0;
		answr  = x<< (23-exp); // just shift left
	} else if(exp>23){
		mask = 1 << exp-24;
		i = mask & x; // leftmost bit of missing bits to check over than or equal as half-way
		mask--;
		mask = (mask&x) && 1; // check over than half-way
		answr = x >> exp-23; // shift right

	}else{ // exp == 23
		mask = 0;
		answr = x; // we don't have to shift
		//if (msb)frac--;
	}

	// round-up when 1 while (2 or 3)
	// 1. the leftmost bit of missing bits is 1.
	// 2. missing bits are bigger than half-way.
	// 3. lefted answr is not even number. (nearest even)
	if (i && (mask || answr&1)){
		answr++;
		//printf("frac++! ");
	}	

	exp = exp +127; // bias

	answr += msb << 31;
	answr += exp << 23;
	//printf("exp : %d 0x%x, frac : %x, mask : %d, !frac&1 : %d, i : %d\n",exp, exp, frac, mask, frac&1, i);
	return answr;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	int msb, e, m ;
	msb = uf & 0x80000000; // msb
	e = uf & 0x7f800000;
	m = uf & 0x007fffff;
	

	e = e >> 23;
	
	// exception for NaN
	if(e == 255 && (!m)) return uf;


	if(uf == 0 || uf == 0x80000000) return uf; // exception for 0
	if(e == 255){ // exception for 2*uf=NaN case
		return uf;
	}
	
	if(e == 0){
		msb += m << 1;
		return msb;
	}

	e++;
	
	msb += e << 23;
	msb += m;

	return msb;
	
}
