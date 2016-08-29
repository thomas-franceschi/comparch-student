/*
 * array_addresses.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    int  A[4] = { 100, 200, 300, 400 };

    printf("==== address comparison\n");
    printf("int array:  %p  %p\n",     &A[2], A + 2);
    printf("==== content comparison\n");
    printf("int array:  %d  %d\n",     A[2], *(A + 2));
}
