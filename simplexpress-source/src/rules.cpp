#include  "simplexpress/rules.hpp"
#include "simplexpress/specifier.hpp"

Rule::LetterCase Rule::to_letter_case(onechar ch)
{
    if (ch == 'l')
    {
        return LetterCase::Lower;
    }
    else if (ch == 'u')
    {
        return LetterCase::Upper;
    }
    else
    {
        return LetterCase::Any;
    }
}

Rule::LetterCase letrCase = Rule::LetterCase::Any;
//Alphanumeric
bool Rule::rule_a(onechar ch, LetterCase letterCase)
{
	//determines whether or not should be upper or lower case. If unspecified then will be either case
	switch (letterCase)
	{
		case LetterCase::Lower:
			letrCase = LetterCase::Lower;
			return Specifier::s_alphanumeric(ch, letrCase);
		case LetterCase::Upper:
			letrCase = LetterCase::Upper;
			return Specifier::s_alphanumeric(ch, letrCase);
        case LetterCase::Any:
        default:
			letrCase = LetterCase::Any;
			return Specifier::s_alphanumeric(ch, letrCase);
	}
}

/*Classification, allows for more languages to be used and implemented.
This will be implemented at a future time.*/
bool Rule::rule_c()
{
	return false;
}

//Digit, Right now only allows for single number (0-9) to be entered
bool Rule::rule_d(onechar ch)
{
	int radix = 10;
	return Specifier::s_digit(ch, radix);
}

//Extended Latin
// FIXME: T1278
bool Rule::rule_e(onechar ch, Rule::LetterCase letterCase)
{
	/*Determines whether the user entered character needs to be upper or lower case
	if neither is set or specified then character can be any case*/
	switch(letterCase)
	{
        case LetterCase::Any:
			letrCase = LetterCase::Any;
			return Specifier::s_alphanumeric(ch, letrCase);
		case LetterCase::Lower:
			letrCase = LetterCase::Lower;
			return Specifier::s_alphanumeric(ch, letrCase);
		case LetterCase::Upper:
			letrCase = LetterCase::Upper;
			return Specifier::s_alphanumeric(ch, letrCase);
	}
}

//Greek FIXME: T1278
//bool Rule::rule_g(onechar ch, Rule::LetterCase letterCase)
//{
//    /*Determines whether the user entered character needs to be upper or lower case
//    if neither is set or specified then character can be any case*/
//    switch(letterCase)
//    {
//        case Rule::LetterCase::Upper:
//            letrCase = Rule::LetterCase::Any;
//            return Specifier::s_greek(ch, letrCase);
//        case Rule::LetterCase::Lower:
//            letrCase = Rule::LetterCase::Lower;
//            return Specifier::s_greek(ch, letrCase);
//        case Rule::LetterCase::Upper:
//            letrCase = Rule::LetterCase::Upper;
//            return Specifier::s_greek(ch, letrCase);
//    }
//}
//
//IPA FIXME: T1278
//bool Rule::rule_i(onechar ch)
//{
//    return (Specifier::s_ipa(ch));
//}

//Latin
bool Rule::rule_l(onechar ch, Rule::LetterCase letterCase)
{
	/*Determines whether the user entered character needs to be upper or lower case
	if neither is set or specified then character can be any case*/
	switch (letterCase)
	{
		case LetterCase::Any:
			letrCase = LetterCase::Any;
			return Specifier::s_latin(ch, letrCase);
		case LetterCase::Lower:
			letrCase = LetterCase::Lower;
			return Specifier::s_latin(ch, letrCase);
		case LetterCase::Upper:
			letrCase = LetterCase::Upper;
			return Specifier::s_latin(ch, letrCase);
	}
}

/*Math. This allows for math operations, will be implemented at a future time
for now returns false.*/
bool Rule::rule_m()
{
	return false;
}

//New Line
bool Rule::rule_n(onechar ch)
{
	return (ch == '\n');
}

//Math Operators
bool Rule::rule_o(onechar ch)
{
	//This will be set to true if what user enters is an operator
	bool is_operator = false;
	/*switch statement to determine what to return. This allows for user addition
	of more operators*/
	switch (*ch.c_str()){
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '^':
		case '=':
		case '!':
			is_operator = true;
			break;
		default:
			is_operator = false;
			break;
		/* will add more as they come up or as needed*/
	}
	return is_operator;
}

//Punctuation
bool Rule::rule_p(onechar ch)
{
	bool punctuation = false;
	/*switch statement to determine what to return. This allows for user addition
	of more punctuations*/
	switch(*ch.c_str()){
		case '!':
		case '.':
		case ',':
		case ';':
		case '"':
		case '-':
		case '?':
		case ':':
			punctuation = true;
			break;
		/*Will add more as they come up*/
	}
	return punctuation;
}

//Carriage Return
bool Rule::rule_r(onechar ch)
{
	return ch == '\r';
}

//Literal Space
bool Rule::rule_s(onechar ch)
{
	return ch == ' ';
}

//Tab
bool Rule::rule_t(onechar ch)
{
	return ch == '\t';

}
/*Unicode(accepts u78 or u57-78). For now unimplemented.*/
bool Rule::rule_u(onechar ch)
{
	// FIXME: Temporarily ignore unused parameter.
	(void)ch;
	return false;
}

//Whitespace
bool Rule::rule_w(onechar ch)
{
	return Specifier::s_whitespace(ch);
}

bool Rule::rule_z(onechar ch)
{
	bool any = true;
	/*switch statement to determine what to fail.*/
	switch(*ch.c_str()){
		case '\n':
		case '\r':
			any = false;
			break;
	}
	return any;
}