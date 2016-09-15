/*
 * gcc_test.c
 *
 *  Created on: Sep 14, 2016
 *      Author: Jay Brockman
 */

void foo(int);

void gcc_test(int a, int b)
{
    int x = 5;
    int y = 7;
    int z = a + b + x + y;
    foo(z);
}
