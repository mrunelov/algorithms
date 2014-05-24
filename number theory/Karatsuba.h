//
// @authors:
// Martin Runelöv
// Philip Sköld
//
// https://kth.kattis.com/problems/polymul2
//

#ifndef KARATSUBA_KTH_H
#define KARATSUBA_KTH_H

#include "common.h"

/**
 * (Slow version. Lots of vector copying. See below)
 * Calculates the product of the polynomials p1 and p2 using Karatsuba's algorithm
 *
 * @return The coefficients of the polynomial, a0,a1,…,an.
 */
// vector<int> karatsuba(vector<int> &p1, vector<int> &p2)

/**
 * (EXPERIMENTAL, NON-WORKING VERSION. Trouble with R01-recursion in res-array)
 * Calculates the product of the polynomials p1 and p2 using Karatsuba's algorithm
 *
 * The coefficients of the product, a0,a1,…,an, are stored in the array <res>
 */ 
void karatsuba(int *a, int *b, int *res, int N);


#endif // end header guard
