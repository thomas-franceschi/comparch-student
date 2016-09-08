#include <stdio.h>

int main()
{
    int x = 3;
    int y = 2;
    int cond;

    printf("x = %d    y = %d\n", x, y);

    // if (x < y)
    // if (y > x)
    cond = x < y;
    if (!cond) goto else_clause1;
    printf("x < y\n");
    printf("y > x\n");
    goto follow1;

    else_clause1:
    printf("x >= y\n");
    printf("y <= x\n");
    goto follow1;

    follow1:
    printf ("follow1\n");


    // if (x >= y)
    // if (y <= x)
    cond = x < y;
    if (cond) goto else_clause2;
    printf("x >= y\n");
    printf("y <= x\n");
    goto follow2;

    else_clause2:
    printf("x < y\n");
    printf("y > x\n");
    goto follow2;

    follow2:
    printf ("follow2\n");


    // if (y < x)
    // if (x > y)
    cond = y < x;
    if (!cond) goto else_clause3;
    printf("y > x\n");
    printf("x < y\n");
    goto follow3;

    else_clause3:
    printf("y >= x\n");
    printf("x <= y\n");
    goto follow3;

    follow3:
    printf ("follow3\n");


    // if (y >= x)
    // if (x <= y)
    cond = y < x;
    if (cond) goto else_clause4;
    printf("y >= x\n");
    printf("x <= y\n");
    goto follow4;

    else_clause4:
    printf("y < x\n");
    printf("x > y\n");
    goto follow4;

    follow4:
    printf ("follow4\n");
}
