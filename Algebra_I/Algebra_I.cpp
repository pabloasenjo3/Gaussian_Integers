#include <string>
#include <cstdlib>

class Z_i {
private:

	int a, b; // (a + bi)

	int roundedQuotient(int dividend, int divisor)
	{
		// 12 / 8 = 1
		// 13 / 8 = 2

		std::div_t division = div(dividend, divisor);
		// dividend = divisor * division.quot + division.rem

		int incremented_quot = division.quot + 1;

		// Q = X.1 -> Q = X
		// Q = X.5 -> Q = X
		// Q = X.6 -> Q = X + 1

		return (incremented_quot * divisor - dividend <
			dividend - division.quot * divisor)
			? incremented_quot
			: division.quot;
	}

	std::string factor(int number)
	{
		switch (number)
		{
		case -1:
			return "-";
		case 1:
			return "";
		default:
			return std::to_string(number);
		}
	}

public:

	Z_i() {}

	Z_i(int a, int b) : a(a), b(b) {}

	Z_i plus(Z_i addend)
	{
		// (a + bi) + (c + di) = ( (a + c) + (b + d)i )
		return Z_i(a + addend.a, b + addend.b);
	}

	Z_i minus(Z_i subtrahend)
	{
		// (a + bi) + (c + di) = ( (a - c) + (b - d)i )
		return Z_i(a - subtrahend.a, b - subtrahend.b);
	}

	Z_i times(Z_i factor)
	{
		// (a + bi) * (c + di) = ( (ac - bd) + (ad + bc)i )
		return Z_i(a * factor.a - b * factor.b, a * factor.b + b * factor.a);
	}

	Z_i dividedBy(int divisor)
	{
		// (a + bi) / n = ( a/n, (b/n)i )
		return Z_i(roundedQuotient(a, divisor), roundedQuotient(b, divisor));
	}

	Z_i conjugate()
	{
		//  ______
		// (a + bi) = (a - bi)
		return Z_i(a, -b);
	}

	unsigned int getNorm()
	{
		return a * a + b * b;
	}

	bool isZero()
	{
		return !a && !b;
	}

	std::string toString()
	{
		std::string result;

		if (a)
		{
			if (b) result = "(" + std::to_string(a) + " " + ((b > 0)
				? "+ " + factor(b) :
				"- " + factor(abs(b))) + "i)";
			else result = (a > 0)
				? std::to_string(a)
				: "(" + std::to_string(a) + ")";
		}
		else if (b) result = (b > 0)
			? factor(b) + "i"
			: "(" + factor(b) + "i)";
		else result = "0";

		return result;
	}
};

class Div_Z_i {
public:
	// FIELDS:

	Z_i dividend, divisor, quotient, remainder;
	// dividend = divisor * quotient + remainder

	// divisor =/= 0	
	// Let N(a + bi) = a^2 + b^2 : N(remainder) < N(divisor)

	// CONSTRUCTOR:

	Div_Z_i(Z_i dividend, Z_i divisor) : dividend(dividend), divisor(divisor)
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

	std::string toString()
	{
		std::string result = dividend.toString() + " = " +
			divisor.toString() + " * " + quotient.toString();

		if (!remainder.isZero())
			result += " + " + remainder.toString();

		return result;
	}
};

#include <iostream>

using namespace std;

class Reader {
private:
	// FIELDS:

	string title;
	char graphic_separator; // As in 102'344'001.23

	// READING METHODS:

	string readLine(string prompt)
	{
		cout << prompt;
		string read;
		getline(cin, read);
		return read;
	}

	// EVALUATORS:

	bool isNotDigit(char c)
	{
		return c != graphic_separator && (c < '0' || c > '9');
	}

	// PRE -> text = noWhitespaces(text)
	bool isInteger(string text)
	{
		// Graphic separators and signs are admitted.

		unsigned short length = text.length();

		bool is_integer;
		if (length) // To avoid out-of-range.
		{
			is_integer = true;
			// Iterates text:
			char c;
			for (unsigned short i = text.at(0) == '+' || text.at(0) == '-';
				i < length && is_integer; i++)
			{
				c = text.at(i);
				if (isNotDigit(c))
					is_integer = false;
			}
		}
		else is_integer = false;

		return is_integer;
	}

	bool isDecimalSeparator(char c)
	{
		return c != graphic_separator && (c == ',' || c == '.');
	}

	// MODIFIERS:

	string noWhitespaces(string text)
	{
		string no_whitespaces;

		unsigned short length = text.length();
		// Iterates text:
		char c;
		for (unsigned short i = 0; i < length; i++)
		{
			c = text.at(i);
			if (!isspace(c))
				no_whitespaces.push_back(c);
		}

		return no_whitespaces;
	}

	// PRE: isInteger(integer) = true
			// sub-PRE: integer = noWhitespaces(integer)
	int stringToInteger(string integer)
	{
		// Graphic separators are removed.

		unsigned short length = integer.length();

		string prepared;
		// Iterates text:
		char c;
		for (unsigned i = 0; i < length; i++)
		{
			c = integer.at(i);
			if (c != graphic_separator)
				prepared.push_back(c);
		}

		return stoi(prepared); // Sí lo estoy
	}

public:
	// CONSTRUCTORS:

	Reader() :
		title(""), graphic_separator('\'')
	{
	}

	Reader(string title) :
		title(title), graphic_separator('\'')
	{
	}

	// MODIFIERS:

	void setTitle(string n_title)
	{
		title = n_title;
	}

	void setGraphicSeparator(char n_graphic_separator)
	{
		graphic_separator = n_graphic_separator;
	}

	// READING METHODS:

	int readInteger()
	{
		string prompt = "Type " + title + " (integer value): ";

		string read;
		do
		{
			read = noWhitespaces(readLine(prompt));
		} while (!isInteger(read));

		return stringToInteger(read);
	}

	int readIntegerGreaterThanOrEqual(int min)
	{
		int result;
		do
		{
			result = readInteger();
		} while (result < min);

		return result;
	}

	int readRangedInteger(int min, int max)
	{
		int result;
		do
		{
			result = readIntegerGreaterThanOrEqual(min);
		} while (result > max);

		return result;
	}
};

int main()
{
	cout << "Dividend: " << endl;
	Reader reader("(a <-- + bi)");
	int temp = reader.readInteger();
	reader.setTitle("(a + b <-- i)");

	Z_i dividend(temp, reader.readInteger());
	cout << "--> " << dividend.toString() << endl << endl;

	Z_i divisor;
	do
	{
		cout << "Divisor: " << endl;
		reader.setTitle("(a <-- + bi)");
		temp = reader.readInteger();
		reader.setTitle("(a + b <-- i)");

		divisor = Z_i(temp, reader.readInteger());
		cout << "--> " << divisor.toString() << endl << endl;
	} while (divisor.isZero());

	cout << "Division: " << endl;
	Div_Z_i division(dividend, divisor);

	cout << division.toString() << endl;

	return 0;
}