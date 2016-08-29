/*
 * call_stack.c
 *
 *  Created on: Aug 12, 2016
 *      Author: jbb
 */
#include <stdio.h>

/*
 * fcn1 doesn't call anything (leaf function)
 */
void fcn1 (int arg)
{
    printf("==> Enter fcn1\n");

    // declare a local variable
    int x;

    // print addresses of argument and local variable
    printf("&arg  %018p\n", &arg);
    printf("&x    %018p\n", &x);

    printf("<== Leave fcn1\n");
}

/*
 * fcn2 calls fcn1 (non-leaf function)
 */
void fcn2 (int arg)
{
    printf("==> Enter fcn2\n");

    // declare a local variable
    int x;

    // print addresses of argument and local variable
    printf("&arg  %018p\n", &arg);
    printf("&x    %018p\n", &x);

    // call fcn1 (which also prints addresses)
    fcn1(arg);

    printf("<== Leave fcn2\n");
}

/*
 * main function
 */
int main(void)
{
    printf("==> Enter main\n");

    // declare some local variables
    int arg;

    // print addresses of local variables
    printf("&arg  %018p\n", &arg);

    // call fcn1
    fcn1(arg);

    // call fcn2, which calls fcn1
    fcn2(arg);

    printf("<== Leave main\n");
}
