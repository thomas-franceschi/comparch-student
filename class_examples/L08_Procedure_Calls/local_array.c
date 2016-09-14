/*
 * local_array.c
 *
 *  Created on: Sep 14, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

void swap(int *A, int x, int y)
{
    int temp;
    temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

int main()
{
    int array[4] = { 0xa, 0xb, 0xc, 0xd};
    printf("0x%1$x  (%1$d)\n", array[0]);
    swap(array, 0, 3);
    printf("0x%1$x  (%1$d)\n", array[0]);
}
