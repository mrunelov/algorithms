//
// @authors:
// Martin Runelöv
// Philip Sköld
//
// https://kth.kattis.scrool.se/problems/modulararithmetic
//

#ifndef MODULARARITHMETIC_H
#define MODULARARITHMETIC_H

#include <math.h>

/*
 * returns: i mod m
 */
template<typename T>
T mod(T i, T m) 
{
    if (i%m < 0)
        return (i%m + m);
    return (i%m);
}

/*
 * Calculates the Greatest common Divisor of a and b
 */
template<typename T>
T GCD(T a, T b)
{
	T c;
	while (a != 0)
	{
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

/*
 * Calculates Least Common Multiple
 */
template<typename T>
long long LCM(T a, T b)
{
	long long gc = gcd(a, b);
	return a * b / gcd;
}




/*
 * Integer division
 * if a â‰¥ 0 : (a div b) = âŒŠ a/b âŒ‹
 * if a < 0 : (a div b) = âŒˆ a/b âŒ‰
 *
 * @return: a/b
 */
 template<typename T>
T int_div(T numer, T denom) {
    if (numer >= 0)
        return (T)floor(numer/denom); // superfluous
    return (T)ceil((double)numer/denom);
} 

/*
 * Finds x,y such that x*a + y*b = gcd(a,b)
 * @return (x,y)
 */
template<typename T>
pair<T,T> euclidean(T a, T b) 
{
    if (a == 0) return make_pair(0,1);
    else if (b == 0) return make_pair(1,0);

    pair<T,T> yx = euclidean(b, mod(a,b));
    T x = yx.second;
    T y = yx.first;
    return make_pair(x, y - int_div(a,b)*x);
}

/*
 * @return: (a+b) mod m
 */
template<typename T>
T mod_add(T a, T b, T m) 
{
    T c = a + b;
    if (c >= m)
        c = c - m;
    return c;
}


/*
 * @return: (a-b) mod m
 */
template<typename T>
T mod_sub(T a, T b, T m)
{
    T c;
    if (b > a)
        c = m + a - b;
    else 
        c = a - b;
    return c;
}

/*
 * Multiples modulo m using iterative addition that makes use of the fact that:
 * x Â· y = x Â· (y mod 2) + x Â· (2 Â· âŒŠ y âŒ‹)
 *
 * @return: a*b mod m
 */
template<typename T>
T mod_mult(T a, T b, T m)
{
    T c = 0;
    while (b != 0) {
        if (mod(b,static_cast<T>(2)) != 0) {
            c = mod_add(c,a,m);
        }
        a = mod_add(a,a,m);
        b = (T)floor((double)b/2); // superfluous
    }
    return c;
}
 
/*
 * Divides modulo m, which is defined as the inverse of multiplication:
 * a/b mod m = a*(b^-1) mod m, where the inverse is found using the euclidean algorithm for GCD.
 * If no inverse exists, -1 is returned.
 * 
 * @return: a/b mod m
 */
template<typename T>
T mod_div(T a, T b, T m) {
    pair<T, T> xy = euclidean(b,m); // find b^-1
    T x = xy.first;
    T y = xy.second;
    if ((x*b + y*m) != 1) {
        return -1;
    }
    x = mod(x,m);
    return mod_mult(a,x,m);
}



/*
 * calculates (a^b) mod c
 */
template<typename T>
T mod_pow(T a, T b, T c)
{
    T res = 1;
    rep(i, 0, b)
        res = (res * a) % c;
    return res % c;
}

/* Multiplicative Inverse Modular
	a^(phi(m)) = 1 (mod m)
	a^(-1) = a^(m-2) (mod m) */
long long InverseEuler(int n, int m)
{
	return mod_pow(n, m-2, m);
}

#endif// MODULARARITHMETIC_H
