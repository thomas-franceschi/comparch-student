/*
 * simple.c
 *
 *  Created on: Aug 14, 2016
 *      Author: jbb
 */

#include <stdio.h>

int foo(int a, int b);

int main()
{
    int a = 1;
    int b = 2;
    int c;

    c = foo(a, b);
    printf("the result is %d\n", c);
}
