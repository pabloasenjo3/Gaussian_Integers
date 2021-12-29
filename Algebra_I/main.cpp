#include "Algebra_I.h"
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

	Algebra_I::Z_i dividend(temp, reader.readInteger());
	cout << "--> " << dividend.toString() << endl << endl;

	Algebra_I::Z_i divisor;
	do
	{
		cout << "Divisor: " << endl;
		reader.setTitle("(a <-- + bi)");
		temp = reader.readInteger();
		reader.setTitle("(a + b <-- i)");

		divisor = Algebra_I::Z_i(temp, reader.readInteger());
		cout << "--> " << divisor.toString() << endl << endl;
	} while (divisor.isZero());

	cout << "Division: " << endl;
	Algebra_I::Div_Z_i division(dividend, divisor);

	cout << division.toString() << endl;

	return 0;
}