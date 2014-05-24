//
// @authors:
// Martin Runelöv
// Philip Sköld
//
// https://kth.kattis.scrool.se/problems/rationalarithmetic
//

#ifndef RATIONAL_KTH_H
#define RATIONAL_KTH_H

#include "common.h"
#include "modular.h"
#include <iostream>

/**
 * A class that handles rational numbers of the form (x/y)
 * 
 * Supported operations:
 * +, -, *, /, reduction, comparison, printing (ostream)
 */

const bool SHOW_DIV_BY_1 = true;


template<typename T>
class Rational;

template<typename T>
std::ostream& operator<<(std::ostream&, const Rational<T>&); // make printable with cout

template<typename T>
class Rational
{
private:
	bool reduced;
	T numerator;
	T denominator;

	void reduce()
	{
		T gcd = GCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;

		if (sgn(denominator) == -1)
		{
			numerator *= -1;
			denominator *= -1;
		}

		reduced = true;
	}

public: 

	Rational(T numerator, T denominator, bool doreduce = true)
		: numerator(numerator), denominator(denominator), reduced(false)
	{
		if (doreduce)
			reduce();
	}

	Rational(T numerator)
		: numerator(numerator), denominator(1), reduced(true)
	{ }

	Rational()
		: numerator(0), denominator(0), reduced(true)
	{ }

	friend std::ostream& operator<< <>(std::ostream& o, const Rational<T>& r); // printable with cout


	Rational inverse() const
	{
		return Rational(denominator, numerator);
	}

	Rational& operator=(const Rational& other)
	{
		numerator = other.numerator;
		denominator = other.denominator;
		reduced = other.reduced;
		return *this;
	}

	Rational operator*(const Rational& other) const
	{
		return Rational(
			numerator*other.numerator,
			denominator*other.denominator); //reduced in constructor
	}

	Rational operator+(const Rational& other) const
	{
		Rational a(numerator*other.denominator, denominator*other.denominator, false);
		Rational b(other.numerator*denominator, other.denominator*denominator, false);
		return Rational(a.numerator + b.numerator, a.denominator);
	}

	Rational operator-(const Rational& other) const
	{
		Rational a(numerator*other.denominator, denominator*other.denominator, false);
		Rational b(other.numerator*denominator, other.denominator*denominator, false);
		return Rational(a.numerator - b.numerator, a.denominator);
	}

	Rational operator/(const Rational& other) const
	{
		// (x/y)/(a/b) = (x/y)*(b/a)
		return (*this) * other.inverse();
	}

	const bool operator==(const Rational& other) const
	{
		if (reduced && other.reduced) //often the case
			return numerator == other.numerator && denominator == other.denominator;

		return Rational(*this) == Rational(other); //reduce and compare
	}

	const bool operator!=(const Rational& other) const
	{
		return !(*this == other);
	}

	const bool operator<=(const Rational& other) const
	{
		return numerator*other.denominator <= other.numerator*denominator;
	}

	const bool operator>=(const Rational& other) const
	{
		numerator*other.denominator >= other.numerator*denominator;
	}

	const bool operator<(const Rational& other) const
	{
		return numerator*other.denominator < other.numerator*denominator;
	}

	const bool operator>(const Rational& other) const
	{
		return numerator*other.denominator > other.numerator*denominator;
	}

   
};

template<typename T>
ostream& operator<< (ostream& out, const Rational<T>& r)
{
	if (!SHOW_DIV_BY_1 && r.denominator == 1)
		return out << r.numerator;
	else
		return out << r.numerator << " / " << r.denominator;    
}




#endif // RATIONAL_KTH_H