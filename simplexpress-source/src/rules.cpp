#include  "simplexpress/rules.hpp"
#include "simplexpress/specifier.hpp"

specifier::LetterCase letrCase = specifier::CASE_ANY;
//Alphanumeric
bool Rule::rule_a(onechar ch, Spec_Case letterCase)
{
    //determines whether or not should be upper or lower case. If unspecified then will be either case
    switch(letterCase)
    {
        case CASE_ANY:
        {
            letrCase = specifier::CASE_ANY;
            return specifier::s_alphanumeric(ch, letrCase);
        }
        case CASE_LOWER:
        {
            letrCase = specifier::CASE_LOWER;
            return specifier::s_alphanumeric(ch, letrCase);
        }
        case CASE_UPPER:
        {
            letrCase = specifier::CASE_UPPER;
            return specifier::s_alphanumeric(ch, letrCase);
        }
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
    return specifier::s_digit(ch, radix);
}

//Extended Latin
// FIXME: T1278
bool Rule::rule_e(onechar ch, Spec_Case letterCase)
{
    /*Determines whether the user entered character needs to be upper or lower case
    if neither is set or specified then character can be any case*/
    switch(letterCase)
    {
        case CASE_ANY:{
            letrCase = specifier::CASE_ANY;
            return specifier::s_alphanumeric(ch, letrCase);
        }
        case CASE_LOWER:{
            letrCase = specifier::CASE_LOWER;
            return specifier::s_alphanumeric(ch, letrCase);
        }
        case CASE_UPPER:{
            letrCase = specifier::CASE_UPPER;
            return specifier::s_alphanumeric(ch, letrCase);
        }
    }
}

//Greek FIXME: T1278
//bool Rule::rule_g(onechar ch, Spec_Case letterCase)
//{
//    /*Determines whether the user entered character needs to be upper or lower case
//    if neither is set or specified then character can be any case*/
//    switch(letterCase)
//    {
//        case Rule::LetterCase::Upper:
//        {
//            letrCase = Rule::LetterCase::Any;
//            return specifier::s_greek(ch, letrCase);
//        }
//        case Rule::LetterCase::Lower:
//        {
//            letrCase = Rule::LetterCase::Lower;
//            return specifier::s_greek(ch, letrCase);
//        }
//        case Rule::LetterCase::Upper:
//        {
//            letrCase = Rule::LetterCase::Upper;
//            return specifier::s_greek(ch, letrCase);
//        }
//    }
//}
//
//IPA FIXME: T1278
//bool Rule::rule_i(onechar ch)
//{
//    return specifier::s_ipa(ch);
//}

//Latin
bool Rule::rule_l(onechar ch, Spec_Case letterCase)
{
    /*Determines whether the user entered character needs to be upper or lower case
    if neither is set or specified then character can be any case*/
    switch(letterCase){
        case CASE_ANY:{
            letrCase = specifier::CASE_ANY;
            return specifier::s_latin(ch, letrCase);
        }
        case CASE_LOWER:{
            letrCase = specifier::CASE_LOWER;
            return specifier::s_latin(ch, letrCase);
        }
        case CASE_UPPER:{
            letrCase = specifier::CASE_UPPER;
            return specifier::s_latin(ch, letrCase);
        }
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
        case '!':{
            is_operator = true;
            break;
        }
        default:{
            is_operator = false;
            break;
        }
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
        case ':':{
            punctuation = true;
            break;
        }
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
    return specifier::s_whitespace(ch);
}