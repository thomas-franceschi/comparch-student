/*
 * addition_subtraction.c
 *
 *  Created on: Aug 21, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    /*
     * Addition
     */
    printf("\n==== 8-bit addition\n");
    printf("hex \t\t\tunsigned \t\tsigned\n");
    printf("%1$hhx + %2$hhx = %3$hhx\t\t%1$hhu + %2$hhu = %3$hhu\t\t%1$hhd + %2$hhd = %3$hhd\n",
            1, 2, 1+2);

    /*
     * Subtraction
     */
    printf("\n==== 8-bit subtraction\n");
    printf("hex \t\t\tunsigned \t\tsigned\n");
    printf("%1$hhx - %2$hhx = %3$hhx\t\t%1$hhu - %2$hhu = %3$hhu\t\t%1$hhd - %2$hhd = %3$hhd\n",
            1, 2, 1-2);
}
