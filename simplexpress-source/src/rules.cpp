#include  "simplexpress/rules.hpp"

namespace simplexpress
{

        specifier::LetterCase letrCase = specifier::CASE_ANY;

            //Alphanumeric
            bool Rule::rule_a(UChar ch, Spec_Case letterCase){
                //determines whether or not should be upper or lower case. If unspecified then will be either case
                switch(letterCase){
                    case CASE_ANY:{
                        letrCase = specifier::CASE_ANY;
                        return (specifier::s_alphanumeric(ch, letrCase)?true:false);
                    }
                    case CASE_LOWER:{
                        letrCase = specifier::CASE_LOWER;
                        return (specifier::s_alphanumeric(ch, letrCase)?true:false);
                    }
                    case CASE_UPPER:{
                        letrCase = specifier::CASE_UPPER;
                        return (specifier::s_alphanumeric(ch, letrCase)?true:false);
                    }
                }

            }

            /*Classification, allows for more languages to be used and implemented.
            This will be implemented at a future time.*/
            bool Rule::rule_c(){return false;}

            //Digit, Right now only allows for single number (0-9) to be entered
            bool Rule::rule_d(UChar ch){

                int radix = 10;
                return (specifier::s_digit(ch, radix) ? true : false);
            }

            //Extended Latin
            bool Rule::rule_e(UChar ch, Spec_Case letterCase){
                /*Determines whether the user entered character needs to be upper or lower case
                if neither is set or specified then character can be any case*/
                switch(letterCase){
                    case CASE_ANY:{
                        letrCase = specifier::CASE_ANY;
                        return (specifier::s_alphanumeric(ch, letrCase) ? true : false);
                    }
                    case CASE_LOWER:{
                        letrCase = specifier::CASE_LOWER;
                        return (specifier::s_alphanumeric(ch, letrCase) ? true : false);
                    }
                    case CASE_UPPER:{
                        letrCase = specifier::CASE_UPPER;
                        return (specifier::s_alphanumeric(ch, letrCase) ? true : false);
                    }
                }
            }

            //Greek
            bool Rule::rule_g(UChar ch, Spec_Case letterCase){
                /*Determines whether the user entered character needs to be upper or lower case
                if neither is set or specified then character can be any case*/
                switch(letterCase){
                    case CASE_ANY:{
                        letrCase = specifier::CASE_ANY;
                        return (specifier::s_greek(ch, letrCase) ? true : false);
                    }
                    case CASE_LOWER:{
                        letrCase = specifier::CASE_LOWER;
                        return (specifier::s_greek(ch, letrCase) ? true : false);
                    }
                    case CASE_UPPER:{
                        letrCase = specifier::CASE_UPPER;
                        return (specifier::s_greek(ch, letrCase) ? true : false);
                    }
                }

            }

            //IPA
            bool Rule::rule_i(UChar ch){
                return (specifier::s_ipa(ch) ? true : false);
            }

            //Latin
            bool Rule::rule_l(UChar ch, Spec_Case letterCase){
                /*Determines whether the user entered character needs to be upper or lower case
                if neither is set or specified then character can be any case*/
                switch(letterCase){
                    case CASE_ANY:{
                        letrCase = specifier::CASE_ANY;
                        return (specifier::s_latin(ch, letrCase) ? true : false);
                    }
                    case CASE_LOWER:{
                        letrCase = specifier::CASE_LOWER;
                        return (specifier::s_latin(ch, letrCase) ? true : false);
                    }
                    case CASE_UPPER:{
                        letrCase = specifier::CASE_UPPER;
                        return (specifier::s_latin(ch, letrCase) ? true : false);
                    }
                }

            }

            /*Math. This allows for math operations, will be implemented at a future time
            for now returns false.*/
            bool Rule::rule_m(){return false;}

            //New Line
            bool Rule::rule_n(UChar ch){ return (ch == '\n' ? true : false);}

            //Math Operators
            bool Rule::rule_o(UChar ch){
                //This will be set to true if what user enters is an operator
                bool is_operator = false;

                /*switch statement to determine what to return. This allows for user addition
                of more operators*/
                switch (ch){
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
            bool Rule::rule_p(UChar ch){
                bool punctuation = false;
                /*switch statement to determine what to return. This allows for user addition
                of more punctuations*/
                switch(ch){
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
            bool Rule::rule_r(UChar ch){return (ch == '\r' ? true : false);}

            //Literal Space
            bool Rule::rule_s(UChar ch){return (ch == ' ' ? true : false);}

            //Tab
            bool Rule::rule_t(UChar ch){return (ch == '\t' ? true : false);}

            /*Unicode(accepts u78 or u57-78). For now unimplemented.*/
            bool Rule::rule_u(UChar ch){
                return false;
            }

            //Whitespace
            bool Rule::rule_w(UChar ch){return (specifier::s_whitespace(ch) ? true : false);}

}
