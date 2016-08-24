/*
 * condition.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    unsigned char uc_ff = 0xff;
    unsigned char uc_0f = 0x0f;

    char c_ff = 0xff;
    char c_0f = 0x0f;

    if (uc_ff > uc_0f)
        printf("uc_ff is greater than uc_f0\n");
    else
        printf("uc_ff is less than uc_f0\n");

    if (c_ff > c_0f)
        printf("c_ff is greater than c_f0\n");
    else
        printf("c_ff is less than c_f0\n");

}
