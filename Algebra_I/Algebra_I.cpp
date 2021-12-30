#include "Algebra_I.h"
using namespace Algebra_I;
using namespace std;

// Z_i:

Z_i::Z_i() {}

Z_i::Z_i(int a) : a(a), b(0) {}

Z_i::Z_i(int a, int b) : a(a), b(b) {}

int Z_i::roundedQuotient(int dividend, int divisor)
{
	// 12 / 8 = 1
	// 13 / 8 = 2
	div_t division = div(dividend, divisor);
	// dividend = divisor * division.quot + division.rem

	int incremented_quot = division.quot + 1;

	// Q = X.1 -> Q = X
	// Q = X.5 -> Q = X
	// Q = X.6 -> Q = X + 1

	return (incremented_quot * divisor - dividend < dividend - division.quot * divisor)
		? incremented_quot
		: division.quot;
}

string Z_i::factor(int number)
{
	switch (number)
	{
	case -1: return "-";
	case 1: return "";
	default: return to_string(number);
	}
}

// Calculates the GCD of two numbers (Great Common Divisor)

Z_i Z_i::GCD(Z_i other)
{
	return isZero() ? other : other.isZero() ? *this : other.GCD(*this % other);
}

//  Calculates the LCM of two numbers (Least Common Multiple)
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

// Operators overloading for Z_i class

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

Z_i Z_i::operator / (Z_i other)
{
	return (!other * *this) / other.getNorm();
}

Z_i Z_i::operator % (Z_i other)
{
	Z_i quotient = *this / other;
	return *this - quotient * other;
}

Z_i Z_i::operator / (int other)
{
	// (a + bi) / n = ( a/n, (b/n)i )
	return Z_i(roundedQuotient(a, other), roundedQuotient(b, other));
}

//	 Conjugate
Z_i Z_i::operator ! ()
{
	//  ______
	// (a + bi) = (a - bi)
	return Z_i(a, -b);
}

Z_i Z_i::operator - ()
{
	return Z_i(-a, -b);
}




string Z_i::toString()
{
	string result;

	if (a)
	{
		if (b) result = "(" + to_string(a) + " " + ((b > 0)
			? "+ " + factor(b) :
			"- " + factor(abs(b))) + "i)";
		else result = (a > 0)
			? to_string(a)
			: "(" + to_string(a) + ")";
	}
	else if (b) result = (b > 0)
		? factor(b) + "i"
		: "(" + factor(b) + "i)";
	else result = "0";

	return result;
}

// Div_Z_i:

Div_Z_i::Div_Z_i(Z_i dividend, Z_i divisor) : dividend(dividend), divisor(divisor)
{
	/*
	a + bi    (a + bi) * (c + di)
	------ =  -------------------
	c + di         N(c + di)
	*/

	//quotient = (dividend * !divisor) / divisor.getNorm();
	//remainder = dividend - quotient * divisor;
	quotient = dividend / divisor;
	remainder = dividend % divisor;
}

string Div_Z_i::toString()
{
	string result = dividend.toString() + " = " +
		divisor.toString() + " * " + quotient.toString();

	if (!remainder.isZero())
		result += " + " + remainder.toString();

	return result;
}
