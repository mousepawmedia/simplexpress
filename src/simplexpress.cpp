#include "simplexpress.hpp"

namespace simplexpress
{
    /*--------------------BaseSimplex--------------------*/
    void BaseSimplex::parseModel(UnicodeString input)
    {
        /*SIMPLEXpress' syntax is space-delimited, which makes parsing quite
        easy - just split by spaces (mostly).*/

        //If model is not empty, get out of Dodge!
        if(model.size() != 0)
        {
            return;
        }

        //The buffer for the current unit.
        UnicodeString unit;

        //String escape flag.
        bool escape = false;

        //For each index in the input string...
        for(int i = 0; i < input.length(); i++)
        {
            /*If the character is a space, unit is not empty, and
            string isn't escaped...*/
            if(input[i] == ' ' && unit != "" && !escape)
            {
                //Push the unit to the model vector.
                model.push_back(unit);
                unit = "";
            }
            else if(input[i] == '\\' && !escape)
            {
                //Flag the escape.
                escape = true;
            }
            //If escape is flagged (previous character was a backslash)...
            else if(escape)
            {
                switch(input[i])
                {
                    case ' ':
                    case '\\':
                        //Character escaped. Push it in as a literal.
                        unit += input[i];
                        break;
                    default:
                    {
                        //We weren't really escaping anything. Push both chars in.
                        unit += '\\';
                        unit += input[i];
                    }
                }
                //Turn off escape flag.
                escape = false;
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
            std::cerr << "ERROR: Empty Simplex model." << std::endl;
        }
    }

    bool BaseSimplex::base_lex(UChar ch)
    {
        //Return variable.
        bool r = false;

        //NOTE: Remove this when we're done. -->
        std::cout << "Unit " << modelIndex << std::endl;
        string str;
        model[modelIndex].toUTF8String(str);
        std::cout << str << std::endl;
        // <--

        //If Specifier...
        if(model[modelIndex][0] == '^')
        {
            specifier::LetterCase letrCase = specifier::CASE_ANY;

            switch(model[modelIndex][1])
            {
                //Alphanumeric
                case 'A':
                {
                    //If we have more than 2 characters in the model...
                    if(model[modelIndex].length() > 2)
                    {
                        //If the third character is an L...
                        if(model[modelIndex][2] == 'L')
                        {
                            //We want lowercase.
                            letrCase = specifier::CASE_LOWER;
                        }
                        //If the third character is an U...
                        else if(model[modelIndex][2] == 'U')
                        {
                            //We want uppercase.
                            letrCase = specifier::CASE_UPPER;
                        }
                    }
                    r = (specifier::s_alphanumeric(ch, letrCase) ? true : false);
                    break;
                }
                //Digit
                case 'D':
                {
                    int radix = 10;
                    if(model[modelIndex].length() > 2)
                    {
                        radix = utf_utils::str_to_int(model[modelIndex].tempSubStringBetween(2));
                        //TODO: Try/Catch for non-numbers!
                    }
                    r = (specifier::s_digit(ch, radix) ? true : false);
                    break;
                }
                //Extended Latin.
                case 'E':
                {
                    //If we have more than 2 characters in the model...
                    if(model[modelIndex].length() > 2)
                    {
                        //If the third character is an L...
                        if(model[modelIndex][2] == 'L')
                        {
                            //We want lowercase.
                            letrCase = specifier::CASE_LOWER;
                        }
                        //If the third character is an U...
                        else if(model[modelIndex][2] == 'U')
                        {
                            //We want uppercase.
                            letrCase = specifier::CASE_UPPER;
                        }
                    }
                    r = (specifier::s_latin_ext(ch, letrCase) ? true : false);
                    break;
                }
                //Letter
                case 'L':
                {
                    //If we have more than 2 characters in the model...
                    if(model[modelIndex].length() > 2)
                    {
                        //If the third character is an L...
                        if(model[modelIndex][2] == 'L')
                        {
                            //We want lowercase.
                            letrCase = specifier::CASE_LOWER;
                        }
                        //If the third character is an U...
                        else if(model[modelIndex][2] == 'U')
                        {
                            //We want uppercase.
                            letrCase = specifier::CASE_UPPER;
                        }
                    }
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
                    parseRange(model[modelIndex], &lower, &upper);
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
                    break;
                }
            }

            //Finished with model. Move on.
            next();
        }
        //Else if Modifier...
        else if(model[modelIndex][0] == '\\')
        {
            //TODO: I think this needs to be checked for at n+1 always.
            //At position n, it would be an error.

            switch(model[modelIndex][1])
            {
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
                    if(isdigit(model[modelIndex][1]))
                    {
                        //TODO: That many matches.
                        break;
                    }
                }
            }
        }
        //Else (if) literal character or string...
        else
        {
            //If we have a match...
            if(ch == model[modelIndex][unitIndex])
            {
                //Move to the next character (or next model if we're done.)
                unitNext() ? true : next();
                //Set return value to true.
                r = true;
            }
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
                *lower = utf_utils::str_to_hex(buffer, true);
                buffer = "";
                dash = true;
            }
            else if(!dash && specifier::s_digit(ch, 16))
            {
                buffer += ch;
            }
            else if(dash && specifier::s_digit(ch, 16))
            {
                buffer += ch;
            }
            else
            {
                std::cerr << "Error parsing numerical range!" << std::endl;
            }
        }

        if(buffer != "")
        {
            if(dash)
            {
                *upper = utf_utils::str_to_hex(buffer, true);
            }
            else if(!dash)
            {
                *lower = utf_utils::str_to_hex(buffer, true);
            }
        }

        //Validate that upper and lower aren't swapped.
        if(dash && (*upper < *lower))
        {
            //Hold the upper value temporarily.
            int temp = *upper;
            //Assign the lower value to the upper value.
            *upper = *lower;
            //Assign the former upper value (temp) to lower.
            *lower = temp;
            //NOTE: This isn't the best solution, but it works for now.
            std::cerr << "Invalid range. Swapping lower and upper values."
                      << std::endl;
        }

        return;

    }

    bool BaseSimplex::prev()
    {
        bool r = false;
        if(modelIndex > 0)
        {
            modelIndex--;
            r = true;
        }
        return r;
    }

    bool BaseSimplex::next()
    {
        bool r = false;
        if(modelIndex < (model.size() - 1))
        {
            modelIndex++;
            r = true;
        }
        return r;
    }

    bool BaseSimplex::unitPrev()
    {
        bool r = false;
        if(unitIndex > 0)
        {
            unitIndex--;
            r = true;
        }
        return r;
    }

    bool BaseSimplex::unitNext()
    {
        bool r;

        //If the unit index is less than the maximum possible...
        if(unitIndex < (model[modelIndex].length() - 1))
        {
            //Increase the unit index.
            unitIndex++;
            //Return true (we were able to increase the index.)
            r = true;
        }
        //Otherwise...
        else
        {
            //Reset the index.
            unitIndex = 0;
            //And return false (no more data.)
            r = false;
        }
        return r;
    }

    void BaseSimplex::flush()
    {
        modelIndex = 0;
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
