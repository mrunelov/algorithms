//
// @authors:
// Martin Runelöv
// Philip Sköld
//
// https://kth.kattis.scrool.se/problems/primesieve
//

#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

#include "common.h"
#include "modular.h"


/*
* Miller Rabins Primality-Test.
* source: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=primalityTesting
*
* @return: A boolean indicating wheter p is prime or not
*/
template<typename T>
bool isprobabprime(T p, int iters)
{
	if (p < 2)
		return false;

	if (p != 2 && p % 2 == 0)
		return false;

	T s = p - 1;
	while (s % 2 == 0){
		s /= 2;
	}

	T a, m, ss;
	rep(i, 0, iters)
	{
		a = rand() % (p - 1) + 1;
		ss = s;
		m = powmod(a, ss, p);
		while (ss != p - 1 && m != 1 && m != p - 1){
			m = mod_mult(m, m, p);
			ss *= 2;
		}
		if (m != p - 1 && ss % 2 == 0){
			return false;
		}
	}

	return true;
}

/*
 * Finds all primes up to N, storing boolean values in <res>
 * indicating whether that number is prime.
 *
 * @return The number of primes between 1 and N
 */
int primesieve(vector<bool>& res, int N, int iterations)
{	
	int primecount = N-1; // assume all ints except 1
	int sqrtN = (int)std::sqrt(N);

	res[0] = false;
	res[1] = false;

	rep(i, 2, sqrtN)
		if (res[i])
			for (int j = i*i; j <= N; j += i)
			{
				if (res[j])
					primecount--;
				res[j] = false;
			}

	return primecount;
}





#endif // PRIMESIEVE_H