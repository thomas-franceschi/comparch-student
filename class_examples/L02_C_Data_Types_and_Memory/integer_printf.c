/*
 * integer_printf.c
 *
 *  Created on: Aug 13, 2016
 *      Author: jbb
 */

#include <stdio.h>

int main()
{
    int 			int_1 			= 1;
    int 			int_ffffffff	= 0xffffffff;
    unsigned int 	uint_1 			= 1;
    unsigned int 	uint_ffffffff 	= 0xffffffff;

    char			char_ff			= 0xff;
    unsigned char	uchar_ff		= 0xff;

    /*
     * Examine effects of hex, decimal, and unsigned printf formatting
     * on signed and unsigned integers
     */
    printf("%x  %d  %u\n", int_1, int_1, int_1);
    printf("%x  %d  %u\n", int_ffffffff, int_ffffffff, int_ffffffff);
    printf("%x  %d  %u\n", uint_1, uint_1, uint_1);
    printf("%x  %d  %u\n", uint_ffffffff, uint_ffffffff, uint_ffffffff);

    printf("%hhx, %hhd, %hhu\n", char_ff, char_ff, char_ff);
    printf("%hhx, %hhd, %hhu\n", uchar_ff, uchar_ff, uchar_ff);
    printf("%x,   %d,   %u\n",   char_ff, char_ff, char_ff);

    /*
     * Leading zeros on hex numbers
     */
    printf("%02hhx  %04hx  %08x\n", 1, 1, 1);
}
