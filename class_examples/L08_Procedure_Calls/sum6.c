/*
 * sum6.c
 *
 *  Created on: Sep 13, 2016
 *      Author: Jay Brockman
 */

# include <stdio.h>

int sum6(int a, int b, int c, int d, int e, int f)
{
    int y = a+b+c+d+e+f;  // force use of $s0 (by our rules!)
    return y;
}

int main()
{
    int y = sum6(1, 2, 3, 4, 5, 6);
    printf("0x%1$x (%1$d)\n", y);
}
