#include "Algebra_I.h"
using namespace Algebra_I;
using namespace std;

// Class Z_i:

Z_i::Z_i() {}

Z_i::Z_i(int a) : a(a), b(0) {}

Z_i::Z_i(int a, int b) : a(a), b(b) {}

int Z_i::roundedQuotient(int dividend, int divisor)
{
	// 1 / 2 = 0.5 -> 0
	// 3 / 5 = 0.6 -> 1
	int quotient = dividend / divisor; // Truncated integer division
	int incremented = quotient + 1;

	return (incremented * divisor - dividend < dividend - quotient * divisor)
		? incremented
		: quotient;
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

// Conjugate
Z_i Z_i::operator ! ()
{
	//  ______
	// (a + bi) = (a - bi)
	return Z_i(a, -b);
}

// Negative
Z_i Z_i::operator - ()
{
	return Z_i(-a, -b);
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
	{
		if (b) result = "(" + to_string(a) + " " + ((b > 0)
			? "+ " + factorToString(b) :
			"- " + factorToString(abs(b))) + "i)";
		else result = (a > 0)
			? to_string(a)
			: "(" + to_string(a) + ")";
	}
	else if (b) result = (b > 0)
		? factorToString(b) + "i"
		: "(" + factorToString(b) + "i)";
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