/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    if (!x && !y) {
        return 1;
    }
    else if (!x) return 0;
    else if (!y) return 0;
    else return !(sign_x ^ sign_y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;
    int b16 = ((v >> 16) > 0) << 4;
    v = v >> b16;
    int b8 = ((v >> 8) > 0) << 3;
    v = v >> b8;
    int b4 = ((v >> 4) > 0) << 2;
    v = v >> b4;
    int b2 = ((v >> 2) > 0) << 1;
    v = v >> b2;
    int b1 = (v >> 1) > 0;
    result = b16 | b8 | b4 | b2 | b1;
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_8 = n << 3;
    int m_8 = m << 3;
    int nth = (x >> n_8) & 0xFF;
    int mth = (x >> m_8) & 0xFF;
    int mask = (0xFF << n_8) | (0xFF << m_8);
    mask = ~mask;
    x = x & mask;
    x = x | (nth << m_8) | (mth << n_8);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    int q = 0;
    for(int i=0; 16-i; i++){
        int mask = 1 << (31 - i);
        int bit = (v & mask) >> (31 - (i << 1));
        result |= bit;
    }
    for(int i=16; 32-i; i++){
        int mask = 1 << (31 - i);
        int bit = (v & mask) << ((i << 1) - 31);
        result |= bit;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int n_zero_check = !!n; // n=0 check=0; n>0 check=1
    x = x >> n_zero_check;
    int mark = 1 << 31;
    mark = ~(mark & (~n_zero_check + 1));
    x = x & mark;
    x = x >> (n + (~n_zero_check + 1));
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int negative = ~x;
    int first_one = 0;
    // 为什么要保留 all_ones : 
    // x为全1时，返回的最高位1下标为0，但实则0位也是0
    // 其实很容易发现，x为000...0001时，才应该返回0位，结果得31
    // 易推出，x为全1时，返回值需要额外加1
    int all_ones = !negative;
    int b16 = negative >> 16;
    b16 = !!b16; 
    b16 = b16 << 4;
    negative = negative >> b16;
    int b8 = negative >> 8;
    b8 = !!b8;
    b8 = b8 << 3;
    negative = negative >> b8;
    int b4 = negative >> 4;
    b4 = !!b4;
    b4 = b4 << 2;
    negative = negative >> b4;
    int b2 = negative >> 2;
    b2 = !!b2;
    b2 = b2 << 1;
    negative = negative >> b2;
    int b1 = negative >> 1;
    b1 = !!b1;
    first_one = b16 | b8 | b4 | b2 | b1;
    return 31 + (~first_one + 1) + all_ones;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (x == 0) {
        return 0;
    }
    else if (x == 0x80000000){
        // Tmin无法用正数表示
        return 0xcf000000;
    }
    unsigned result = 0;
    // 求S
    if (x < 0) {
        result = 1 << 31;
        x = -x;
    }
    // 求E
    int index = 0;
    int temp = x;
    while (temp > 0){
        index++;
        temp = temp << 1;
    }
    index = 31 - index;
    unsigned int E = index + 127;
    // 求M
    int shift = 32 - index;
    int M = x << shift;
    int drop = M & 0x1FF; // 保留舍弃的部分
    if (M < 0) {
        M = M >> 1;
        M = M & 0x7FFFFFFF; // 最高位改为0
        M = M >> 8;
    }
    else{
        M = M >> 9;
    }
    // 计算小数部分的四舍五入
    if (drop > 0x100) {
        M += 1;
    }
    else if((drop == 0x100) + (M & 1) == 2){
        M += 1;
    }
    // 因为可能产生进位，所以用加法，等效实现进位+规格化
    result += M + (E << 23);
    return result;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    if ((uf == 0) + (uf == 0x80000000) > 0) {
        // 输入为0
        return uf;
    }
    else if((uf & 0x7F800000) == 0x7F800000) {
        // 输入为NaN或无穷大
        return uf;
    }
    else if((uf & 0x7F800000) == 0){
        // 非正规数
        unsigned M = uf & 0x007FFFFF;
        M = M << 1;
        uf = (uf & 0xFF800000) | M;
        return uf;
    }
    uf = uf + 0x00800000;
    return uf;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned E = (uf2 >> 20) & 0x7FF;
    int shift = E - 1023;
    if(!E){
        // 非规格化统一返回0
        return 0;
    }
    else if(!(E - 0x7FF)){
        // 正负无穷返回0x80000000
        return 0x80000000;
    }
    else if(E < 1023){
        // E < 1023返回0
        return 0;
    }
    else if(shift >= 31){
        // shift >= 31返回0x80000000,Tmin包含在内
        return 0x80000000;
    }
    int ans = 1 << shift;
    unsigned M1 = uf1, M2 = uf2 & 0x000FFFFF;
    if(shift > 20){
        ans = ans | (M2 << (shift - 20));
        ans = ans | (M1 >> (52 - shift));
    }
    else{
        ans = ans | (M2 >> (20 - shift));
    }
    // 最后再判断正负号
    if(uf2 & 0x80000000){
        ans = -ans;
    }
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x > 127){
        // x > 127, 返回+INF
        return 0x7F800000;
    }
    else if(x < -149){
        // x < -149, 返回0
        return 0;
    }
    else if(x >= -126 && x <= 127){
        // 规格化
        unsigned E = x + 127;
        return E << 23;
    }
    else{
        // 非规格化
        unsigned M = 1 << (x + 149);
        return M;
    }
}
