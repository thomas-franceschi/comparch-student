/*
 * array_addresses.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    char cA[4];
    int  iA[4];

    printf("char array: %p  %p  %p  %p\n", &cA[0], &cA[1], &cA[2], &cA[3]);
    printf("int array:  %p  %p  %p  %p\n", &iA[0], &iA[1], &iA[2], &iA[3]);
    printf("==== add 1 to pointer to first element in array\n");
    printf("char array: &cA[0] + 1 = %p\n", &cA[0] + 1);
    printf("int array:  &iA[0] + 1 = %p\n", &iA[0] + 1);
}
