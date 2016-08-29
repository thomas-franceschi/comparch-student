/*
 * number_formatting.c
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

    printf("==== 16-bit\n");
    printf("hex: %1$hx \tunsigned: %1$hu \tsigned: %1$hd\n", -1);

    printf("==== 32-bit\n");
    printf("hex: %1$x \tunsigned: %1$u \tsigned: %1$d\n", -1);
}
