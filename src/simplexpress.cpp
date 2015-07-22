#include "simplexpress.hpp"

namespace simplexpress
{
    /*--------------------BaseSimplex--------------------*/
    void BaseSimplex::parseModel(UnicodeString input)
    {
        /*SIMPLEXpress' syntax is space-delimited, which makes parsing quite
        easy - just split by spaces.*/

        //If model is not empty, get out of Dodge!
        if(model.size() != 0)
        {
            return;
        }

        //The buffer for the current unit.
        UnicodeString unit;

        //For each index in the input string...
        for(int i = 0; i < input.length(); i++)
        {
            //If the character is a space and unit is not empty...
            if(input[i] == ' ' && unit != "")
            {
                //Push the unit to the model vector.
                model.push_back(unit);
                unit = "";
            }
            else
            {
                //Add the current character to unit.
                unit += input[i];
            }
        }

        //If we have an un-pushed unit...
        if(unit != "")
        {
            //Push the unit to the model.
            model.push_back(unit);
        }

        if(model.size() == 0)
        {
            //TODO: Throw a snit (that is, an error).
            std::cout << "ERROR: Empty Simplex model." << std::endl;
        }
    }

    bool BaseSimplex::base_lex(UChar ch)
    {
        //Return variable.
        bool r = false;

        //NOTE: Remove this when we're done. -->
        std::cout << "Unit " << n << std::endl;
        string str;
        model[n].toUTF8String(str);
        std::cout << str << std::endl;
        // <--

        //If Specifier...
        if(model[n][0] == '^')
        {
            specifier::LetterCase letrCase = specifier::CASE_ANY;
            if(model[n].length() > 2)
            {
                if(model[n][2] == 'L')
                {
                    letrCase = specifier::CASE_LOWER;
                }
                else if(model[n][2] == 'U')
                {
                    letrCase = specifier::CASE_UPPER;
                }
            }

            switch(model[n][1])
            {
                //Alphanumeric
                case 'A':
                {
                    r = (specifier::s_alphanumeric(ch, letrCase) ? true : false);
                    break;
                }
                //Digit
                case 'D':
                {
                    r = (specifier::s_digit(ch) ? true : false);
                    break;
                }
                //Extended Latin.
                case 'E':
                {
                    r = (specifier::s_latin_ext(ch, letrCase) ? true : false);
                    break;
                }
                //Letter
                case 'L':
                {
                    r = (specifier::s_latin(ch, letrCase) ? true : false);
                    break;
                }
                //IPA
                case 'I':
                {
                    r = (specifier::s_ipa(ch) ? true : false);
                }
                //Math
                case 'M':
                {
                    //TODO: Write me!
                    r = true;
                    break;
                }
                //Newline
                case 'N':
                {
                    r = (ch == '\n' ? true : false);
                    break;
                }
                //[Math] Operator
                case 'O':
                {
                    //TODO: Write me!
                    r = true;
                    break;
                }
                //Punctuation
                case 'P':
                {
                    //TODO: Write me!
                    r = true;
                    break;
                }
                //[Carriage] Return
                case 'R':
                {
                    r = (ch == '\r' ? true : false);
                    break;
                }
                //[Literal] Space
                case 'S':
                {
                    r = (ch == ' ' ? true : false);
                    break;
                }
                //Tab
                case 'T':
                {
                    r = (ch == '\t' ? true : false);
                    break;
                }
                //Unicode
                case 'U':
                {
                    //Get the lower and upper ranges for the Unicode code.
                    int lower, upper = 10000;
                    parseRange(model[n], &lower, &upper);

                    //If in inclusive range, true, else false.
                    r = (ch >= lower && ch <= upper ? true : false);
                    break;
                }
                //Whitespace
                case 'W':
                {
                    r = (specifier::s_whitespace(ch) ? true : false);
                    break;
                }
                //Any character. (Just give up and say TRUE.)
                case '.':
                {
                    r = true;
                    /*NOTE: Because of how greedy this is, the multi-modifiers
                    should check the NEXT model before the current.*/
                    break;
                }
                //Literal ^
                case '^':
                {
                    r = (ch == '^' ? true : false);
                    break;
                }
                //Literal "\"
                case '\\':
                {
                    r = (ch == '\\' ? true : false);
                }
            }
        }
        //Else if Modifier...
        else if(model[n][0] == '\\')
        {
            //TODO: I think this needs to be checked for at n+1 always.
            //At position n, it would be an error.

            switch(model[n][1])
            {
                //Lowercase only.
                case 'L':
                {
                    //TODO: This is going to have to force the LOWER equivalents of
                    //any tests contained therein. Easier said than done?
                    //Most non-case tests could have an override - 0 for normal,
                    //1 for lower and 2 for upper.
                    break;
                }
                //Uppercase only.
                case 'U':
                {
                    //TODO: This is going to have to force the UPPER equivalents of
                    //any tests contained therein. Easier said than done?
                    break;
                }
                //Start of set.
                case '[':
                {
                    //TODO: How is this supposed to actually work?
                    break;
                }
                case ']':
                {
                    //See ']'
                    break;
                }
                //Multiple.
                case '+':
                {
                    //TODO: Check last again, if fail, check next.
                    break;
                }
                //NOT preceding - invert test result.
                case '!':
                {
                    //TODO: Simply invert test results (I hope?)
                    break;
                }
                //Optional.
                case '?':
                {
                    //TODO: If last fail, reset maybe and check next.
                    break;
                }
                default:
                {
                    if(isdigit(model[n][1]))
                    {
                        //TODO: That many matches.
                        break;
                    }
                }
            }
        }
        //Else (if) literal character...
        else
        {

        }

        return r;
    }

    void BaseSimplex::parseRange(UnicodeString input, int* lower, int* upper, int startAt)
    {
        bool dash;
        UnicodeString buffer = "";

        //Loop through the remaining characters in unit, and...
        for(int i = startAt; i < input.length(); i++)
        {
            UChar ch = input[i];
            if(!dash && ch == '-')
            {
                *lower = utf_utils::str_to_int(buffer, true);
                buffer = "";
                dash = true;
            }
            else if(!dash && specifier::s_digit(ch))
            {
                buffer += ch;
            }
            else if(dash && specifier::s_digit(ch))
            {
                buffer += ch;
            }
            else
            {
                std::cout << "Error parsing numerical range!" << std::endl;
            }
        }

        if(buffer != "")
        {
            if(dash)
            {
                *upper = utf_utils::str_to_int(buffer, true);
            }
            else if(!dash)
            {
                *lower = utf_utils::str_to_int(buffer, true);
            }
        }

        return;

    }

    void BaseSimplex::prev()
    {
        if(n > 0)
        {
            n--;
        }
    }

    void BaseSimplex::next()
    {
        if(n < model.size())
        {
            n++;
        }
    }

    void BaseSimplex::flush()
    {
        n = 0;
    }

    /*--------------------Simplex--------------------*/
    Simplex::Simplex(UnicodeString modelString)
    {
        parseModel(modelString);
    }

    int Simplex::count(UnicodeString check)
    {
        //Return number of matching strings within.

        //NOTE: Temporary only.
        return 0;
    }

    bool Simplex::match(UnicodeString check)
    {
        bool r = false;

        /* TODO: Overrunning the model fails nicely as a side-effect via
         * prev() and next(). BUT, should we check for this/throw error?*/

        for(int i = 0; i < check.length(); i++)
        {
            r = base_lex(check[i]);
            next();
            if(!r)
            {
                break;
            }
        }

        flush();
        return r;
    }

    UnicodeString trim(UnicodeString check)
    {
        //Return first matching string.

        //NOTE: Temporary only.
        return "";
    }

    Simplex::~Simplex()
    {
        //dtor
    }

    /*--------------------CharSimplex--------------------*/
    CharSimplex::CharSimplex(UnicodeString modelString)
    {
        parseModel(modelString);
        *buffer = "";
    }

    CharSimplex::Trilean lex(char ch)
    {
        //Evaluate current character.

        //NOTE: Temporary only.
        return CharSimplex::TRI_FALSE;
    }

    void CharSimplex::flush()
    {
        //Reset all temporary data variables.
        ciBuffer = "";
        clBuffer = "";
        modelIndex = 0;

        //Note that we leave models and option flags alone.
    }
}
