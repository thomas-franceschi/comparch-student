/*
 * shift.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    unsigned uint_val  = 0xffffffff;
    int int_val        = 0xffffffff;
    int x              = -100;

    printf("unsigned shifted left:  %08x\n", uint_val << 4);
    printf("unsigned shifted right: %08x\n", uint_val >> 4);
    printf("\n");
    printf("int shifted left:       %08x\n", int_val << 4);
    printf("int shifted right:      %08x\n", int_val >> 4);
    printf("\n");
    printf("-100 shifted left by 2:  %d\n", x << 2);
    printf("-100 shifted right by 2: %d\n", x >> 2);
}
