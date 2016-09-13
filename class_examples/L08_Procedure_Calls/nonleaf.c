/*
 * nonleaf.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Jay Brockman
 */
#include <stdio.h>

int shift(int x)
{
    int y = 2;
    return x << y;
}

int shift_add(int x)
{
    int y = 7;
    return shift(x) + shift(y);
}

int main()
{
    int x = 5;
    int z = shift_add(x);
    printf("%d\n", x);
    printf("%d\n", z);
}
