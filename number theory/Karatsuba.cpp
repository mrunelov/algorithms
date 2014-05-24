#include <math.h>
#include "Karatsuba.h" 

void karatsuba(int *a, int *b, int *res, int N) 
{
    if (N == 1) 
    { 
        res[1] = 0; // reset higher part of result array (semi-cure for side effect of populating res recursively)
        res[0] = a[0]*b[0];
        return;
    }

    int half_N = N/2;
    int rounding = N%2 == 0 ? 0 : 1; // unevenly sized arrays gets a bigger upper half

    int *a_l = &a[0]; // lower half of a
    int *b_l = &b[0]; // lower half of b
    int *a_u = &a[half_N]; // upper half of a
    int *b_u = &b[half_N]; // upper half of b
    int *a_lu = &res[N*6]; // lower a + upper a
    int *b_lu = &res[N*6+half_N]; // lower b + upper b
    int *R0 = &res[0]; // result of Karatsuba(lower)
    int *R1 = &res[N]; // result of Karatsuba(upper)
    int *R01 = &res[N*2]; // result of Karatsuba(lower + upper)


    for (int i = 0; i < half_N; ++i) // calculate lower + upper
    { 
        a_lu[i] = a_l[i] + a_u[i];
        b_lu[i] = b_l[i] + b_u[i];
    }
    if (N%2 != 0) // add the extra int from the upper halves when uneven
    { 
        a_lu[half_N] += a_u[half_N];
        b_lu[half_N] += b_u[half_N];
    }

    karatsuba(a_l,b_l,R0,half_N);
    karatsuba(a_u,b_u,R1,half_N+rounding);
    karatsuba(a_lu, b_lu,R01,half_N+rounding);

    for (int i = 0; i < N; ++i) // (R01 - R0 - R1)*x^(N/2)
    { 
        R01[i] = R01[i] - R0[i] - R1[i];
    }
    for (int i = 0; i < N; ++i) 
    {
        res[i+half_N] += R01[i];
    }
}



