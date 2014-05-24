//
// @authors:
// Martin Runelöv
// Philip Sköld
//
// https://kth.kattis.scrool.se/problems/chineseremainder
//

#ifndef CHINESEREMAINDER_H
#define CHINESEREMAINDER_H

#include "modular.h"

template<typename T>
T CRT(T a, T n, T b, T m)
{
	// s*n + t*m = gcd(n,m) = 1
	pair<T, T> st = euclidean(n, m);
	T s = mod(st.first, m);
	T t = mod(st.second, n);

	// s*n = 1 - t*m =>
	//      s*n mod n = 0 
	//      s*n mod m = 1

	//  (a*t*m + b*s*n) mod n 
	// = a*t*m mod n 
	// = a * (1-s*n) mod n          = a

	//  (a*t*m + b*s*n) mod m 
	// = b*s*n mod m 
	// = b* (1-t*m) mod m           = b,

	// => x = a*t*m + b*s*n 
	// => n*m mod m = n*m mod n = 0)
	T x = mod_add(mod_mult(mod_mult(a, t, n*m), m, n*m), mod_mult(mod_mult(b, s, n*m), n, n*m), n*m);
	return x;
}

#endif // header guard