#include "Algebra_I.h"
using namespace Algebra_I;
using namespace std;

// Z_i:

Z_i::Z_i() {}

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

Z_i Z_i::plus(Z_i addend)
{
	// (a + bi) + (c + di) = ( (a + c) + (b + d)i )
	return Z_i(a + addend.a, b + addend.b);
}

Z_i Z_i::minus(Z_i subtrahend)
{
	// (a + bi) + (c + di) = ( (a - c) + (b - d)i )
	return Z_i(a - subtrahend.a, b - subtrahend.b);
}

Z_i Z_i::times(Z_i factor)
{
	// (a + bi) * (c + di) = ( (ac - bd) + (ad + bc)i )
	return Z_i(a * factor.a - b * factor.b, a * factor.b + b * factor.a);
}

Z_i Z_i::dividedBy(int divisor)
{
	// (a + bi) / n = ( a/n, (b/n)i )
	return Z_i(roundedQuotient(a, divisor), roundedQuotient(b, divisor));
}

Z_i Z_i::conjugate()
{
	//  ______
	// (a + bi) = (a - bi)
	return Z_i(a, -b);
}

unsigned int Z_i::getNorm()
{
	return a * a + b * b;
}

bool Z_i::isZero()
{
	return !a && !b;
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

	quotient = dividend.times(divisor.conjugate())
		.dividedBy(divisor.getNorm());
	remainder = dividend.minus(quotient.times(divisor));
}

string Div_Z_i::toString()
{
	string result = dividend.toString() + " = " +
		divisor.toString() + " * " + quotient.toString();

	if (!remainder.isZero())
		result += " + " + remainder.toString();

	return result;
}