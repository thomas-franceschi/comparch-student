/*
 * array_casting.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    char A[8] = { 0xef, 0xbe, 0xad, 0xde,
                  0xad, 0xfb, 0xca, 0xde };

    int *int_ptr = (int *) A;

    printf("int_ptr[0] = %x   int_ptr[1] = %x\n", int_ptr[0], int_ptr[1]);
}
