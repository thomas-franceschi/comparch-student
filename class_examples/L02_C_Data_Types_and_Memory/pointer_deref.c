/*
 * pointer_deref.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    char x, y, z;
    char *yptr;

    /*
     * Just to see where data is stored in memory
     * int should be stored on 32-bit boundary
     */
    printf("%p  %p  %p  %p\n", &x, &y, &z, &yptr);

    y = 0xab;
    printf("%hhx\n", y);
    yptr = &y;
    *yptr = 0x12;
    printf("%hhx\n", y);
}
