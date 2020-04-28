#include "simplexpress/specifier.hpp"

Specifier::SpecifierType Specifier::to_specifier_type(onechar ch)
{
	if (ch == 'a')
	{
		return SpecifierType::Alphanumeric;
	}
	else if (ch == 'c')
	{
		return SpecifierType::Classification;
	}
	else if (ch == 'd')
	{
		return SpecifierType::Digit;
	}
	else if (ch == 'l')
	{
		return SpecifierType::LatinLetter;
	}
	else if (ch == 'm')
	{
		return SpecifierType::Math;
	}
	else if (ch == 'n')
	{
		return SpecifierType::Newline;
	}
	else if (ch == 'o')
	{
		return SpecifierType::MathOperator;
	}
	else if (ch == 'p')
	{
		return SpecifierType::Punctuation;
	}
	else if (ch == 'r')
	{
		return SpecifierType::CarriageReturn;
	}
	else if (ch == 's')
	{
		return SpecifierType::Space;
	}
	else if (ch == 't')
	{
		return SpecifierType::Tab;
	}
	else if (ch == 'w')
	{
		return SpecifierType::Whitespace;
	}
	else
	{
		return SpecifierType::Unsupported;
	}
}

bool Specifier::s_alphanumeric(onechar ch, Rule::LetterCase ltrCase)
{
	//If it's a digit or underscore, we're good.
	if(digit(ch) || ch == '_')
	{
		return true;
	}
	switch(ltrCase)
	{
		case Rule::LetterCase::Any:
			return latin(ch);
		case Rule::LetterCase::Lower:
			return latin_lower(ch);
		case Rule::LetterCase::Upper:
			return latin_upper(ch);
	}
	//If it gets this far, just return false.
	return false;
}

bool Specifier::s_digit(onechar ch, int radix)
{
	return digit(ch, radix);
}

bool Specifier::s_latin(onechar ch, Rule::LetterCase ltrCase)
{
	switch(ltrCase)
	{
		case Rule::LetterCase::Any:
			return latin(ch);
		case Rule::LetterCase::Lower:
			return latin_lower(ch);
		case Rule::LetterCase::Upper:
			return latin_upper(ch);
	}
	//If it gets this far, just return false.
	return false;
}

bool Specifier::s_whitespace(onechar ch)
{
	return whitespace(ch);
}

int str_utils::ch_to_hex(onechar ch)
{
	// FIXME: Not Unicode compatible.  See fixme: 138
	int c = static_cast<int>(toupper(*ch.c_str()));
	int i;
	//48 [0] - 57 [9] (-48)
	if(c >= 48 && c <= 57)
	{
		i = (c-48);
	}
	else if(c >= 65 && c <= 70)
	{
		//65 [A] - 70 [F] (-55)
		i = (c-55);
	}
	else
	{
		throw std::out_of_range("The character could not be converted.");
	}
	return i;
}

int str_utils::str_to_hex(onestring str, bool failsafe)
{
	//Initialize our return integer.
	int r = 0,
	//The integerized character.
		ci = 0;
	const int AL = str.length() - 1;
	for(int i = 0; i <= AL; i++)
	{
		try
		{
			ci = ch_to_hex(str[i]);
		}
		catch(const std::out_of_range& oor)
		{
			if(failsafe)
			{
				return -1;
			}
			else
			{
				throw std::out_of_range("The string cannot be converted.");
			}
		}
		r += pow(16, (AL-i)) * ci;
	}
	return r;
}

int str_utils::ch_to_int(onechar ch)
{
	//48 [0] - 57 [9]
	// FIXME: line 138 again, but may be okay?
	int i = static_cast<int>(*ch.c_str()) - 48;
	if(i < 0 || i > 9)
	{
		throw std::out_of_range("The character could not be converted.");
	}
	return i;
}

int str_utils::str_to_int(onestring str, bool failsafe)
{
	//If we start with 0x, it's hex.
	if(str[0] == '0' && str[1] == 'x')
	{
		return str_utils::str_to_hex(str, failsafe);
	}
	//Otherwise, proceed with interpreting in binary.
	//Initialize our return integer.
	int r = 0,
	//The integerized character.
		ci = 0,
	//The incrementer.
		i = 0;
	const int AL = str.length() - 1;
	/*ALGORITHM:
	let ci = the integerized character
		 i = the index of the character
		al = the length, minus 1 so the algorithm works
	   str = the initial string
		 r = the final return integer
	for each i in str:
		r += [10^(al-i)] * ci
	EXAMPLE:
	string: 957
	al = [length] - 1 = 3 - 1 = 2
	ci=9, i=0
	[10^(2-0)] * 9 = [10^2] * 9 = 100 * 9 = 900
	r = 0 + 900
	ci=5, i=1
	[10^(2-1)] * 5 = [10^1] * 5 = 10 * 5 = 50
	r = 900 + 50 = 950
	ci=7, i=2
	[10^(2-2)] * 7 = [10^2] * 7 = 1 * 7 = 7
	r = 950 + 7 = 957
	*/
	//If we hit a negative sign at i=0...
	if(str[0] == '-')
	{
		//Skip i=0 and invert r's sign later.
		i = 1;
	}
	for(int ii = i; ii <= AL; ii++)
	{
		try
		{
			ci = ch_to_int(str[ii]);
		}
		catch(const std::out_of_range& oor)
		{
			if(failsafe)
			{
				return -1;
			}
			else
			{
				throw std::out_of_range("The string cannot be converted.");
			}
		}
		r += pow(10, (AL-i)) * ci;
		i = ii;
	}
	//If we found a negative sign at i=0 earlier...
	if(str[0] == '-')
	{
		//Make r negative.
		r *= -1;
	}
	return r;
}