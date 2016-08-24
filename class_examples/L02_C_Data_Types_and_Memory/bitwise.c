/*
 * bitwise.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    int x = 0x0aaaaaaf;
    printf("%08x\n", x | 0x80000000);
    printf("%08x\n", x & 0xfffffffc);
    printf("%08x\n", x ^ 0x000000f0);
}
