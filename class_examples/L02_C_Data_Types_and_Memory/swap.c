/*
 * swap.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int a = 11;
    int b = 22;
    printf("before:  a = %d    b = %d\n", a, b);
    swap(&a, &b);
    printf("after:   a = %d    b = %d\n", a, b);
}
