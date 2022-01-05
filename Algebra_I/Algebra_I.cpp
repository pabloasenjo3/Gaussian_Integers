#include "Algebra_I.h"
using namespace Algebra_I;
using namespace std;

// Class Z_i:

Z_i::Z_i() {}

Z_i::Z_i(int a) : a(a), b(0) {}

Z_i::Z_i(int a, int b) : a(a), b(b) {}

int Z_i::abs(int n)
{
	return (n < 0) ? -n : n;
}
 
// Calculates the rounded quotient of an integer division
int Z_i::roundedQuotient(int dividend, int divisor)
{
	// It works by finding the quotient that implies the lowest remainder in 
	// absolute value, preferring positive remainders over negative ones:
	
	// -8 / 5 = -1.6  -> roundedQuotient(-8, 5)  = -2 
		// -8 = 5 * (-1) [- 3] = 5 * (-2) [+ 2]
		// abs(-3) >= abs(+2) --------^
	// -3 / -5 = -0.6 -> roundedQuotient(-3, -5) = -1
	// 1 / 2 = +0.5   -> roundedQuotient(1, 2)   = +0 (Positive remainder preferred)
	// 3 / 5 = +0.6   -> roundedQuotient(3, 5)   = +1

	int quot = dividend / divisor; // Truncated quotient of integer division
	// Can't just check quotient's sign as it might be 0
	int next_quot = quot + ((dividend * divisor < 0) ? -1 : 1); 
	// The closest integer that is either too great, or too low if division is negative
	
	return (abs(dividend - divisor * quot) <= abs(dividend - divisor * next_quot))
		? quot : next_quot;
}

string Z_i::factorToString(int number)
{
	// "1x"  -> "x"
	// "-1x" -> "-x"
	// "nx"  -> "nx"
	switch (number)
	{
	case -1: return "-";
	case 1: return "";
	default: return to_string(number);
	}
}

// Calculates the GCD of two numbers (Greatest Common Divisor)
Z_i Z_i::GCD(Z_i other)
{
	return isZero() ? other : other.isZero() ? *this : other.GCD(*this % other);
}

// Calculates the LCM of two numbers (Least Common Multiple)
Z_i Z_i::LCM(Z_i other)
{
	return (*this * other) / GCD(other);
}

unsigned int Z_i::getNorm()
{
	return a * a + b * b;
}

bool Z_i::isZero()
{
	return !a && !b;
}

// Operators overloading for Z_i class:

Z_i Z_i::operator + (Z_i other)
{
	// (a + bi) + (c + di) = ( (a + c) + (b + d)i )
	return Z_i(a + other.a, b + other.b);
}

Z_i Z_i::operator - (Z_i other)
{
	// (a + bi) + (c + di) = ( (a - c) + (b - d)i )
	return Z_i(a - other.a, b - other.b);
}

Z_i Z_i::operator * (Z_i other)
{
	// (a + bi) * (c + di) = ( (ac - bd) + (ad + bc)i )
	return Z_i(a * other.a - b * other.b, a * other.b + b * other.a);
}

// Negative
Z_i Z_i::operator - ()
{
	return Z_i(-a, -b);
}

// Conjugate
Z_i Z_i::operator ! ()
{
	//  ______
	// (a + bi) = (a - bi)
	return Z_i(a, -b);
}

// Returns a rounded division by an integer
Z_i Z_i::operator / (int other)
{
	// (6 + 5i) / 10 = (0.6 + 0.5i) = (1 + 0i)
	return Z_i(roundedQuotient(a, other), roundedQuotient(b, other));
}

// Returns the least remainder quotient
Z_i Z_i::operator / (Z_i other)
{
	// (46 + 17i) / (20 - 10i) = (1.5 + 1.6i) -> (1 + 2i)
	return (!other * *this) / other.getNorm();
}

// Returns the least remainder
Z_i Z_i::operator % (Z_i other)
{
	return *this - (*this / other) * other;
}

string Z_i::toString()
{
	string result;

	if (a)
		if (b) result = "(" + to_string(a) + " " + 
			((b > 0) ? "+ " + factorToString(b) : "- " + factorToString(abs(b))) + "i)";
		else result = (a > 0) ? to_string(a) : "(" + to_string(a) + ")";
	else if (b) result = (b > 0) ? factorToString(b) + "i" : "(" + factorToString(b) + "i)";
	else result = "0";

	return result;
}

// Class Div_Z_i:

Div_Z_i::Div_Z_i(Z_i dividend, Z_i divisor) : dividend(dividend), divisor(divisor)
{
	// Calculates the least remainder division
	
	quotient = dividend / divisor;
	remainder = dividend - quotient * divisor;
	// remainder = dividend % divisor; 
	// (Division would be done twice)
}

string Div_Z_i::toString()
{
	string result = dividend.toString() + " = " +
		divisor.toString() + " * " + quotient.toString();

	if (!remainder.isZero())
		result += " + " + remainder.toString();

	return result;
}