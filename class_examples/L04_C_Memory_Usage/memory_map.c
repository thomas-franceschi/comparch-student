/*
 * memory_map.c
 *
 *  Created on: Aug 12, 2016
 *      Author: jbb
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Declare uninitialized global variables
 */
int global_a;
int global_b;
int global_c;

/*
 * Declare initialized global variables
 */
int global_init_a = 1;
int global_init_b = 2;
int global_init_c = 3;

/*
 * Declare initialized and uninitialized global arrays
 */
int global_array[4];
int global_init_array[4] = { 1, 2, 3, 4 };

/*
 * fcn1 doesn't call anything (leaf function)
 */
void fcn1 (int arg1, int arg2)
{
    // declare a local variable
    int fcn1_local_var;

    // print addresses of arguments and local variable
    printf("&fcn1_arg1          %018p\n", &arg1);
    printf("&fcn1_arg2          %018p\n", &arg2);
    printf("&fcn1_local_var     %018p\n", &fcn1_local_var);
}

/*
 * fcn2 calls fcn1 (non-leaf function)
 */
void fcn2 (int arg1, int arg2)
{
    // declare a local variable
    int fcn2_local_var;

    // print addresses of arguments and local variable
    printf("&fcn2_arg1          %018p\n", &arg1);
    printf("&fcn2_arg2          %018p\n", &arg2);
    printf("&fcn2_local_var     %018p\n", &fcn2_local_var);

    // call fcn1 (which also prints addresses)
    fcn1(arg1, arg2);
}

/*
 * main function
 */
int main(void)
{
    // declare some local variables
    int local_a;
    int local_b;
    int local_c;

    // dynamically allocate some memory blocks
    int *malloc_ptr_a = (int *) malloc(16 * sizeof(int));
    int *malloc_ptr_b = (int *) malloc(16 * sizeof(int));

    // print addresses of global variables
    printf("&global_a           %018p\n", &global_a);
    printf("&global_b           %018p\n", &global_b);
    printf("&global_c           %018p\n", &global_c);
    printf("&global_init_a      %018p\n", &global_init_a);
    printf("&global_init_b      %018p\n", &global_init_b);
    printf("&global_init_c      %018p\n", &global_init_c);
    printf("global_array        %018p\n", global_array);
    printf("global_init_array   %018p\n", global_init_array);

    // print addresses of local variables
    printf("&local_a            %018p\n", &local_a);
    printf("&local_b            %018p\n", &local_b);
    printf("&local_c            %018p\n", &local_c);

    // print addresses of dynamically allocated memory blocks
    printf("malloc_ptr_a        %018p\n", malloc_ptr_a);
    printf("malloc_ptr_b        %018p\n", malloc_ptr_b);

    // call fcn1 (leaf function)
    fcn1(local_a, local_b);

    // call fcn2 (non-leaf, calls fcn1)
    fcn2(local_a, local_b);

    // print addresses of functions (function pointers)
    printf("fcn1                %018p\n", fcn1);
    printf("fcn2                %018p\n", fcn2);
    printf("main                %018p\n", main);
}
