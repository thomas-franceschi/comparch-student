/*
 * pointer_casting.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    int int_val     = 0xabcd1234;
    int *int_ptr    = &int_val;
    char *char_ptr  = (char *)int_ptr;

    printf("*int_ptr     = %x\n",   *int_ptr);
    printf("*char_ptr    = %hhx\n", *char_ptr);
    printf(" char_ptr[3] = %hhx\n",   char_ptr[3]);
}
