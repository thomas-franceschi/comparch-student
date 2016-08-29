/*
 * printf_hex_float.c
 *
 *  Created on: Aug 24, 2016
 *      Author: Jay Brockman
 */

#include <stdio.h>

int main()
{
    printf("decimal: %1$f    scientific: %1$e    hex: %1$a\n", 1.5);
    printf("decimal: %1$f    scientific: %1$e    hex: %1$a\n", 8.5);
    printf("decimal: %1$f    scientific: %1$e    hex: %1$a\n", 1024.5);
}
