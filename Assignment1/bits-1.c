/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 * Name- Anshika Saxena
 * Userid-23210018@iitgn.ac.in
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  2. Function arguments and local variables (no global variables).
  3. Local variables of type int and long
  4. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  5. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  6. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
// 2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
    return (x<<63)>>63;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 63 (most significant)
 *   Examples: allOddBits(0xFFFFFFFDFFFFFFFDL) = 0L,
 *             allOddBits(0xAAAAAAAAAAAAAAAAL) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 2
 */
long allOddBits(long x) {
	long x1=170;
	long y=x1<<8;
	long p=x1|y;
	long i=p<<16;
	long m=p|i;
	long o=m<<32;
	long t=m|o;		
    return !((x&t)^t);
}
/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5L, 5L) = 0L, isNotEqual(4L, 5L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
long isNotEqual(long x, long y) {
    return !(!(x^y));
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {

	
		long l=1;
		long i=~0;
	long p=(~x)+l;
	long g=(l<<n)+i;
	
	long j=!(!(p&(g)));
	long t=(((x>>63)&l)&j);
	
	
    return ((x)>>n)+t;
    
}
// 3
/*
 * remainderPower2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: remainderPower2(15L,2L) = 3, remainderPower2(-35L,3L) = -3L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
long remainderPower2(long x, long n) {
		long l=1;
		long i=~0;
		long s=(x>>63);
		long p=s&l;
	long p1=(x^s)+p;
	long g=(l<<n)+i;
	long j=p1&g;
		//printf("%ld\n",j);
    return (j^s)+p;
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 63
 *   Examples:
 *      rotateLeft(0x8765432187654321L,4L) = 0x7654321876543218L
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
long rotateLeft(long x, long n) {
   long p=64;
   long l=1;

		long p1=(x>>(p+((~n)+1)));
		
		long g=(l<<n)+(~0);
		long o=p1&g;
		
    return (x<<n)|o;
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   between lowbit and highbit
 *   Examples: bitMask(5L,3L) = 0x38L
 *   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long bitMask(long highbit, long lowbit) {
	long l=1;
    long x=(l<<63)>>63;
    long p=(((x<<(highbit))^x)<<1)+1;
    long o=x<<lowbit;
    return p&o;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5L) = 0L, isPower2(8L) = 1L, isPower2(0) = 0L
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
long isPower2(long x) {
	 long p = (x >> 63) & 1;
	  return !((!x ^ p) | (((x + ~0)) & x));
	
    
}
// 4
/*
 * allAsciiDigits - return 1 if each byte b in x satisfies
 *   0x30 <= b <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: allAsciiDigits(0x3031323536373839L) = 1L.
 *            allAsciiDigits(0x4031323536373839L) = 0L.
 *            allAsciiDigits(0x0031323536373839L) = 0L.
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 30
 *   Rating: 4
 */
long allAsciiDigits(long x) {
long x1=48;
	long y=x1<<8;
	long p=x1|y;
	long i=p<<16;
	long m=p|i;
	long o=m<<32;
	long mas1=m|o;
	long t=(x&mas1)^(mas1);
	long op=t;
	long formsb3=!!((op)|(((mas1<<2)&x)));  //if 1 then wrong
	
	
	
	long x2=0x08;
	long y1=x2<<8;
	long p1=x2|y1;
	long i1=p1<<16;
	long m1=p1|i1;
	long o1=m1<<32;
	long mas8=m1|o1;
	
	long for8=(x&mas8);
	
	long s11=((mas8>>1)&x)<<1;
	long s1x1=(x&(mas8>>2))<<2;
	long h=(s11)|(s1x1);
	
	long inv=(for8)&h;//if 1 11xx and 1x1x form
	long in=(formsb3|(inv));
	
    return !in;
    
    

  
    
    
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples:
 *    trueThreeFourths(11L) = 8
 *    trueThreeFourths(-9L) = -6
 *    trueThreeFourths(4611686018427387904L) = 3458764513820540928L (no
 * overflow) Legal ops: ! ~ & ^ | + << >> Max ops: 20 Rating: 4
 */
long trueThreeFourths(long x) {
		long l=1;
		long i=~0;
		long n=2;
		long s=(x>>63);
		long y=s&l;
	long p=(x^s)+y;
	
	long g=3;
	long rem=p&g;
	long f=rem+i;
	long r=(p>>n);
	long w=(((r)<<l)+(r))+((f>>63)^(f));
	s=s&(~(w>>63));
	long h=(w^s)+(s&y);
	
    return (h);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5L) = 2, bitCount(7L) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
long bitCount(long x) {
      
 /*    long x1=17;
	long y=x1<<8;
	long p=x1|y;
	long i=p<<16;
	long m=p|i;
	long o=m<<32;
	long t=m|o;
	long on=1;
	long on1=2;
	long on2=3;
	long fo=4;
	//long mask = (17 | (0x11 << 8) | (0x11 << 16) | (0x11 << 24)); 
    long s = x & t;
    s = s + ((x >> on) & t);
    s = s + ((x >> on1) & t);
    s = s + ((x >> on2) & t);
    long w=15;
 long lsb = (s& w)+ ((s >> fo)&w);
 //long a1=8;
 
  long secondByte = ((s >> ((long)8)) & 0xf) + ((s >> (long)12) & 0xf);
 long thirdByte = ((s >> (long)16) & 0xf) + ((s >> (long)20) & 0xf);
  long fourthByte = ((s >> (long)24) & 0xf) + ((s >> (long)28) & 0xf);
  long fiveByte = ((s >> ((long)32)) & 0xf) + ((s >> (long)36) & 0xf);
  long sixByte = ((s >> (long)40) & 0xf) + ((s >> (long)44) & 0xf);
  long sevenByte = ((s >> (long)48) & 0xf) + ((s >> (long)52) & 0xf);
  long eight=((s >> (long)56) & 0xf) + ((s >> (long)60) & 0xf);
  
  //  mask = 0x0F | 0x0F << 8;
    //s = (s & mask) + ((s >> 4) & mask);
    return (lsb + secondByte + thirdByte + fourthByte+fiveByte+sixByte+sevenByte+eight);
	*/
  long a=~0;
    long m=(0x33<<8)|0x33;
    m=m<<16|m;
    m=m<<32|m;
    
    long m1=(m<<1)^m;
    long m2=(0x0f<<8)|0x0f;
    m2=m2<<16|m2;
    m2=m2<<32|m2;
    
    long m3=0xff|(0xff<<16);
    m3=m3<<32|m3;
    
     long m4=0xff|(0xff<<8);
    m4=m4<<32|m4;
    
    long m5=0L;
    m5=~(a<<32);
    
    x=(x&m1)+((x>>1)&m1);
        x=(x&m)+((x>>2)&m);
        x=(x&m2)+((x>>4)&m2);
        x=(x&m3)+((x>>8)&m3);
        x=(x&m4)+((x>>16)&m4);
        x=(x&m5)+((x>>32)&m5);
    
    return x;	
	
  //  return 2;
}
