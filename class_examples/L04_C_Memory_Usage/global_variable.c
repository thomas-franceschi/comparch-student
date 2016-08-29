/*
 * global_variable.c
 *
 *  Created on: Aug 28, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int x = 7;

void fcn()
{
    printf("&x from fcn():             %p\n", &x);
    x = 11;
}

int main()
{
    printf("&x from main:              %p\n", &x);
    printf("x from main before fcn():  %d\n", x);
    fcn();
    printf("x from main after fcn():   %d\n", x);
}


