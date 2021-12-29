#pragma once
#include <string>
#include <cstdlib>

namespace Algebra_I {
	using namespace std;

	class Z_i {
	private:
		// FIELDS:
		int a, b; // (a + bi)

		int roundedQuotient(int dividend, int divisor);

		string factor(int number);

	public:
		// CONSTRUCTORS:
		Z_i();

		Z_i(int, int);

		Z_i plus(Z_i);

		Z_i minus(Z_i);

		Z_i times(Z_i);

		Z_i dividedBy(int);

		Z_i conjugate();

		unsigned int getNorm();

		bool isZero();

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

		string toString();
	};
}