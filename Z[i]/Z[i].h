#pragma once
#include <string>

namespace Algebra_I {
	using namespace std;

	class Z_i {
	private:
		// FIELDS:

		int a, b; // (a + bi)

		int abs(int);

		int roundedQuotient(int, int);

		string factorToString(int);

	public:
		// CONSTRUCTORS:

		Z_i();

		Z_i(int);

		Z_i(int, int);

		// CALCULATORS:

		Z_i GCD(Z_i);

		Z_i LCM(Z_i);

		unsigned int getNorm();

		bool isZero();

		Z_i operator + (Z_i);

		Z_i operator - (Z_i);

		Z_i operator * (Z_i);

		Z_i operator / (Z_i);

		Z_i operator % (Z_i);

		Z_i operator / (int);

		Z_i operator ! ();

		Z_i operator - ();

		// WRITER:

		string toString();
	};

	class Div_Z_i {
	public:
		// FIELDS:

		Z_i dividend, divisor, quotient, remainder; // dividend = divisor * quotient + remainder

		// divisor =/= 0	
		// Let N(a + bi) = a^2 + b^2 => N(remainder) < N(divisor)

		// CONSTRUCTOR:

		Div_Z_i(Z_i, Z_i);

		// WRITERS:

		string toString();
	};
}
