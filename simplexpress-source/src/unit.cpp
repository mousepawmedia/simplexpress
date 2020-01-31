#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"
#include "simplexpress/simplex.hpp"
/*for now these just return false till a later time*/
bool Unit::specifiers(onechar ch)
{
    Spec_Case sCase = CASE_ANY;
    //Variable that we return
    bool return_var = false;
    /*Switch statement to determine what case we are
    going to be looking for.*/
    switch(usCheck.at(2).c_str()[0])
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
    switch(usCheck.at(1).c_str()[0])
    {
    case 'a':
        {
            return_var = rule.rule_a(ch, sCase);
            break;
        }
    //FIXME: T1278 v2.0-v3.0 For now does nothing and just returns false
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
            // FIXME: T1278
            //return_var = rule.rule_e(ch, sCase);
            return_var = false;
            break;
        }
    case 'g':
        {
            // FIXME: T1278
            //return_var = rule.rule_g(ch, sCase);
            return_var = false;
            break;
        }
    case 'i':
        {
            // FIXME: T1278
            //return_var = rule.rule_i(ch);
            return_var = false;
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
            // FIXME: T1278
            //return_var = rule.rule_u(ch);
            return_var = false;
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

bool Unit::literals(onestring ch)
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

bool Unit::literal_sets(onechar ch)
{
    // FIXME: Temporarily ignore unused parameter.
    (void)ch;
    bool return_var = false;
    return return_var;
}

bool Unit::type_choice(onechar ch)
{
    bool return_var = false;
    if(usCheck[0] == '^')
    {
        // NOTE: This does not feel like the recommended way to switch on a onechar
        switch(usCheck.at(1).c_str()[0])
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

bool Unit::check_model(onechar ch)
{
    return type_choice(ch);
}

//Unit::Unit(onestring uString) : usCheck { uString } {}