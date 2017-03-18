/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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

/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
 // use ~ and | to replace &
int bitAnd(int x, int y){
  return ~(~x | ~y);
}


/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB最低有效位) to 3 (MSB最高有效位)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
 // n<<3 按位表示n    Examples:1000
 // x>>(n<<3) 将x算术右移n*(2^3)位    0000 0000 0001 0010 0011 0100 0101 0110
 // (x>>(n<<3)&0xFF) 掩码运算生成最低有效字节    0101 0110, 即0x56
int getByte(int x, int n) {
  return (x >> (n << 3) & 0xFF);
}


/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
 // x>>n 将x算术右移n位
 // 考虑当最高位为1时进行掩码运算
 // 掩码：~(((1<<31)>>n)<<1)
int logicalShift(int x, int n) {
  return (x >> n)&(~(((1 << 31) >> n) << 1));
}

// ! ! ! ?
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
 // 计算用二进制表示x时1的个数
int bitCount(int x) {
  int mask1 = 0x11 | (0x11<<8);
  int mask2 = mask1 | (mask1<<16);
  int sum = x&mask2;
  sum = sum+((x>>1)&mask2);
  sum = sum+((x>>2)&mask2);
  sum = sum+((x>>3)&mask2);
  sum = sum+(sum>>16);
  mask1 = 0xF | (0xF<<8);
  sum = (sum&mask1)+((sum>>4)&mask1);
  return ((sum+(sum>>8))&0x3F);
}


/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
 // x的逆元:～x+1; 掩码:0x01
 // 如果x!=0, 那么x或者~x+1的最高有效位为1, 右移之后即为最低有效位;
 // 执行掩码运算后最低有效位仍为1, 运算使之得到0即可;
 // 反之，则得到1;
 // (~((x | (~x+1))>>31))&0x01也是一样的.
int bang(int x) {
  return ((((x >> 31)& 0x01) | (((~x+ 1) >> 31)& 0x01)) ^0x01);
  // x = (x>>16) | x;
  // x = (x>>8) | x;
  // x = (x>>4) | x;
  // x = (x>>2) | x;
  // x = (x>>1) | x;
  // return ~x & 1;

}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
/* 最大的二进制补码整数:
 * 0111 1111 1111 1111 1111 1111 1111 1111
 * int tmax(void) {
 *   int x = 0x80;
 *   return (~(x << 24));
 * }
 */
 // 最小的二进制补码整数:1000 0000 0000 0000 0000 0000 0000 0000
int tmin(void) {
  return 1<<31;
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
  int shiftNumber= 32 + (~n + 1);// 32 - n
  return !(x^((x<<shiftNumber)>>shiftNumber));
   // 先左移32-n位，再右移32-n位，即保留最后n位数，再与x异或
   // 若两者相同表示x可被表示为一个n位整数，！0为1
}


/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
 // 将x右移n位，若x是负数则继续+1
int divpwr2(int x, int n) {
  int mask = (1<<n)+ ~0;
  int equalizer = (x>>31)& mask;
  return (x+ equalizer)>>n;
}


/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+ 1;
}


/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
// 使x<=0时返回0值,x>0时返回1
int isPositive(int x) {
  return !((x>>31) | (!x));
}
// 可以取m记录x的符号位，(!!x)判断x是否不为零


/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int singx = (x >> 31) & 1;
  int singy = (y >> 31) & 1;    //比较符号位 1 0 = 1,  0 1 = 0;
  int sing = (singx ^ singy) & singx; //保证singx和singy异号
  int tmp = x + ((~y) + 1); // x - y, 同号情况下,异号情况下会越界 0 0 = , 1 1 =
  tmp = ((tmp>>31)&1) & (!(singx ^ singy));// 保证singx 和 singy 同号
  //int t = (!(x ^ y)); //判断相等
  //printf("sing  =%d, tmp = %d\n", sing, tmp);
  return (sing | tmp | ((!(x ^ y)))); //
}


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
 // 最高位的1出现的位置
int ilog2(int x) {
  int bitsNumber=0;
    bitsNumber=(!!(x>>16))<<4;//
    bitsNumber=bitsNumber+((!!(x>>(bitsNumber+8)))<<3);
    bitsNumber=bitsNumber+((!!(x>>(bitsNumber+4)))<<2);
    bitsNumber=bitsNumber+((!!(x>>(bitsNumber+2)))<<1);
    bitsNumber=bitsNumber+(!!(x>>(bitsNumber+1)));
    bitsNumber=bitsNumber+(!!bitsNumber)+(~0)+(!(1^x));
    //当x为0时，还需要减一才能得到正确值。
    return bitsNumber;
}


/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point value.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
// 如果uf是NaN,返回NaN;否则，返回-f;
// 只要后面32位中有一位不是0就是NaN
// 首先判断是否是NaN,其次考虑规格化和非规格化的问题；
unsigned float_neg(unsigned uf) {
  if(~(((uf>>23)&0xFF)) || !(uf&((1<<23)-1))){
  uf ^= (1<<31);
}
    return uf;
}


/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /*int exponent=0;
   return ((sign<<31)|(exponent<<23)|fraction)+flag;*/
   int sign=x>>31&1;
   int i;
   int exponent;
   int fraction;
   int delta;
   int fraction_mask;
   if(x==0)//||x==0x8000000)
       return x;
   else if(x==0x80000000)
       exponent=158;
   else{
       if (sign)//turn negtive to positive
           x = -x;
       i = 30;
       while ( !(x >> i) )//see how many bits do x have(rightshift until 0)
           i--;
       //printf("%x %d\n",x,i);
       exponent = i + 127;
       x = x << (31 - i);//clean all those zeroes of high bits
       fraction_mask = 0x7fffff;//(1 << 23) - 1;
       fraction = fraction_mask & (x >> 8);//right shift 8 bits to become the fraction,sign and exp have 8 bits total
       x = x & 0xff;
       delta = x > 128 || ((x == 128) && (fraction & 1));//if lowest 8 bits of x is larger than a half,or is 1.5,round up 1
       fraction += delta;
       if(fraction >> 23) {//if after rounding fraction is larger than 23bits
           fraction &= fraction_mask;
           exponent += 1;
       }
   }
   return (sign<<31)|(exponent<<23)|fraction;
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
// 传入的数据类型是unsigned,符号位为0,所以特殊值NaN可表示为0x7F800000;
 // 若阶码域全为1,则返回本身，即(f&0x7F800000)==0x7F800000;return uf;
 // 若输入非规格化数uf=0000 0000 0xxx xxxx xxxx xxxx xxxx xxxx, 计算2*uf;
   // 如果这个数足够大（能转化为规格化数），将小数位向阶码位进位(<<1);
   // 如果这个数不够大，则用（f&0x007FFFFF)<<1来计算;
// 若输入规格化数，直接在阶码域加1，即f+0x80000000;
unsigned float_twice(unsigned uf) {
  unsigned f = uf;
  if((f&0x7F800000)==0){
    f = ((f&0x007FFFFF)<<1) | (0x80000000&f);
  }else if((f&0x7F800000)!=0x7F800000){
    f = f+0x80000000;
  }
  return f;
}
