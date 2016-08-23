/*
 * arithmetic_examples.c
 *
 *  Created on: Aug 21, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    /*
     * Number formatting
     */
    printf("==== 8-bit\n");
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", -1);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 127);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", -127);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 128);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 250);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 95);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", -95);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 43);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", -43);
    printf("hex: %1$hhx \tunsigned: %1$hhu \tsigned: %1$hhd\n", 0xe0);
    printf("==== 16-bit\n");
    printf("hex: %1$hx \tunsigned: %1$hu \tsigned: %1$hd\n", -1);
    printf("hex: %1$hx \tunsigned: %1$hu \tsigned: %1$hd\n", -128);
    printf("==== 32-bit\n");
    printf("hex: %1$x \tunsigned: %1$u \tsigned: %1$d\n", -1);
    printf("hex: %1$x \tunsigned: %1$u \tsigned: %1$d\n", -128);

    /*
     * Addition
     */
    printf("\n==== 8-bit addition\n");
    printf("hex \t\t\tunsigned \t\tsigned\n");
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            1, 2, 1+2);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            87, 41, 87+41);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            -3, -2, -3 + -2);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            87, -50, 87 + -50);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            12, -17, 12 + -17);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            130, -140, 130 + -140);
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            140, -130, 140 + -130);
    /*
     * Subtraction
     */
    printf("\n==== 8-bit subtraction\n");
    printf("hex \t\t\tunsigned \t\tsigned\n");
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            1, 2, 1-2);
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            87, 41, 87-41);
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            -3, -2, -3 - -2);
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            87, -50, 87 - -50);
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            130, 140, 130 - 140);
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            140, 130, 140 - 130);
}
