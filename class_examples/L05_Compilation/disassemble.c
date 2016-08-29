/*
 * disassemble.c
 *
 *  Created on: Aug 28, 2016
 *      Author: jbb
 *
 *  Displays the contents of a function in memory,
 *  like objdump -d
 */

#include <stdio.h>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int i;
    int a = 1;
    int b = 2;
    int c = add(a, b);

    // print first 8 bytes of add
    unsigned char *add_ptr = (unsigned char *) add;
    for (i = 0;  i < 8;  i++)
        printf("%x: %x\n", add_ptr + i, *(add_ptr + i));
}
