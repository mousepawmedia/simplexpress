#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"
#include "simplexpress/simplex.hpp"

namespace simplexpress
{
    /*for now these just return false till a later time*/
    bool Unit::specifiers(UChar ch)
    {
        Spec_Case sCase = CASE_ANY;
        //Variable that we return
        bool return_var = false;

        /*Switch statement to determine what case we are
        going to be looking for.*/
        switch(usCheck[2])
        {
        case 'l':
            {
                sCase = CASE_LOWER;
                break;
            }
        case 'u':
            {
                sCase = CASE_UPPER;
                break;
            }
        default:
            {
                sCase = CASE_ANY;
                break;
            }
        }

        switch(usCheck[1])
        {
        case 'a':
            {
                return_var = rule.rule_a(ch, sCase);
                break;
            }
        //For now does nothing and just returns false
        case 'c':
            {
                return_var = false;
                break;
            }
        case 'd':
            {
                return_var = rule.rule_d(ch);
                break;
            }
        case 'e':
            {
                return_var = rule.rule_e(ch, sCase);
                break;
            }
        case 'g':
            {
                return_var = rule.rule_g(ch, sCase);
                break;
            }
        case 'i':
            {
                return_var = rule.rule_i(ch);
                break;
            }
        case 'l':
            {
                return_var = rule.rule_l(ch, sCase);
                break;
            }
        case 'm':
            {
                return_var = false;
                break;
            }
        case 'n':
            {
                return_var = rule.rule_n(ch);
                break;
            }
        case 'o':
            {
                return_var = rule.rule_o(ch);
                break;
            }
        case 'p':
            {
                return_var = rule.rule_p(ch);
                break;
            }
        case 'r':
            {
                return_var = rule.rule_r(ch);
                break;
            }
        case 's':
            {
                return_var = rule.rule_s(ch);
                break;
            }
        case 't':
            {
                return_var = rule.rule_t(ch);
                break;
            }
        case 'u':
            {
                return_var = rule.rule_u(ch);
                break;
            }
        case 'w':
            {
                return_var = rule.rule_w(ch);
                break;
            }
        default:
            {
                std::cout << "Invalid specifier.\n";
                break;
            }
        }

        return return_var;
    }

    bool Unit::literals(UnicodeString ch)
    {
        bool return_var = false;
        /*has to match Unicode character exactly
        otherwise its false*/
        if(ch == usCheck[0])
        {
            return_var = true;
        }
        return return_var;
    }

    bool Unit::literal_sets(UChar ch)
    {
        bool return_var = false;
        return return_var;
    }

    bool Unit::type_choice(UChar ch)
    {
        bool return_var = false;
        if(usCheck[0] == '^')
        {
            switch(usCheck[1])
            {
            case '<':
                {
                    //literal_sets(ch);
                    break;
                }
            case '[':
                {
                    //sets(ch);
                    break;
                }
            default:
                {
                    return_var = specifiers(ch);
                    break;
                }
            }
        }
        else
        {
            return_var = literals(ch);
        }
        return return_var;
    }

    bool Unit::check_model(UChar ch)
    {
        return type_choice(ch);
    }

    Unit::Unit(UnicodeString uString)
    {
        usCheck = uString;
    }

}
