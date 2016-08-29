/*
 * malloc_free.c
 *
 *  Created on: Aug 28, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr1 = (int *) malloc(1024 * sizeof(int));
    printf("ptr1:  %p\n", ptr1);

    int *ptr2 = (int *) malloc(1024 * sizeof(int));
    printf("ptr2:  %p\n", ptr2);

    int *ptr3 = (int *) malloc(2048 * sizeof(int));
    printf("ptr3:  %p\n", ptr3);

    free(ptr2);

    int *ptr4 = (int *) malloc(512 * sizeof(int));
    printf("ptr4:  %p\n", ptr4);

    int *ptr5 = (int *) malloc(600 * sizeof(int));
    printf("ptr5:  %p\n", ptr5);
}
