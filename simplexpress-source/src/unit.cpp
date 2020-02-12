#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"
#include "simplexpress/simplex.hpp"

Unit::Unit(onestring s) : model(s)
{
    // FIXME: This will break on sets - beginning is not a fixed length
    if (model.length() >= 3)
    {
        switch (*model.at(3).c_str())
        {
            case '+':
            {
                multiple = true;
                break;
            }
            case '?':
            {
                optional = true;
                break;
            }
            case '*':
            {
                multiple = true;
                optional = true;
                break;
            }
            default:
                break;
        }
    }
}

/*for now these just return false till a later time*/
bool Unit::specifiers(onechar ch)
{
    Spec_Case sCase = CASE_ANY;
    //Variable that we return
    bool return_var = false;
    /*Switch statement to determine what case we are
    going to be looking for.*/
    switch(model.at(2).c_str()[0])
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
        switch(model.at(1).c_str()[0])
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
        case '.':
        {
            return_var = true;
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

bool Unit::literals(onechar ch)
{
    /*has to match Unicode character exactly
    otherwise its false*/
    return ch == model[0];
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
    if(model[0] == '^')
    {
        // NOTE: This does not feel like the recommended way to switch on a onechar
        // FIXME: handle error of not having something after it
        switch(model.at(1).c_str()[0])
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

int Unit::check_model(onestring s)
{
    // Optional handler
    if (optional)
    {
        if (s.empty())
            return 0;
        else
            return -1;
    }

    if (multiple)
    {
            // iterate until failure
            int ret = 0;

            for (size_t i = 0; i < s.length(); i++)
            {
                if (type_choice(s.at(i)))
                    ret += 1;
                else
                    break;
            }

            return ret;
    }
    else
    {
        bool result = type_choice(s.at(0));
        if (result > 0)
            return 1;
        else
            return -1;
    }
    return -1;
}

std::ostream& operator<<(std::ostream& s, const Unit& u)
{
    s << "Unit::(" << u.model << "), idx: "<< u.model_index;
    return s;
}