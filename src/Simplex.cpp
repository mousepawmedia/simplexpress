#include "Simplex.hpp"
#include "Rules.hpp"

namespace simplexpress
{
Simplex::Simplex(string user_input, string the_model)
{
    parseInput(the_model);
    UnicodeString buffer = UnicodeString::fromUTF8(StringPiece(user_input));
    user_input_model = buffer;
    match(buffer);
}
/*should we keep like this or make multiple functions for each thing we are pulling out?*/

/*vector of units, parse the units that the user enters into Unit class.*/
/*in constructor specify condition statements*/

void Simplex::parseInput(string the_model)
{
    UnicodeString buffer;
    int location_in_model = 0;
    string model_to_check;

    /*Loop that pulls out all units and specifiers. Spaces are converted into separate
    units, except for the spaces that lie within sets and literal sets*/
    while(location_in_model < the_model.length())
    {
        for(int i = 0; i < the_model.length()-1; ++i)
        {
            if(the_model[location_in_model+i] == '^')
            {
                if(the_model[location_in_model+i+1] == '[' || the_model[location_in_model+i+1] == '<')
                {
                    do
                    {
                        model_to_check.push_back(the_model[location_in_model+i]);
                        ++location_in_model;
                    }
                    while(the_model[location_in_model+i] != ']' && the_model[location_in_model+i] != '>');
                }
                do
                {
                    if(the_model[i+location_in_model] == ' ')
                    {
                        model_to_check.push_back('/');
                        model_to_check.push_back('^');
                    }
                    else
                    {
                        model_to_check.push_back(the_model[location_in_model]);
                    }
                    location_in_model++;
                }
                while(the_model[location_in_model] != '/');
                model_to_check.push_back('/');
            }
            else
            {
                ++location_in_model;
                break;
            }
        }
        if(the_model[location_in_model+1] != '^')
        {
            while(the_model[location_in_model] != '^' && location_in_model == the_model.length())
            {
                ++location_in_model;
            }
        }
    }

    location_in_model = 0;

    /*loop that is for the purpose of sets, every set is pulled out in its entirety.*/
    while(location_in_model < model_to_check.size())
    {
        string model_we_push_back = "";
        if(model_to_check[location_in_model] == '^')
        {
            if(model_to_check[location_in_model+1] == '[' || model_to_check[location_in_model+1] == '<')
            {
                do
                {
                    model_we_push_back.push_back(model_to_check[location_in_model]);
                    ++location_in_model;
                }
                while(model_to_check[location_in_model] != ']' && model_to_check[location_in_model] != '>');
                /*pushing these back to keep the location
                in the model where we want it. and so the units stay consistent*/
                if(model_to_check[location_in_model] == ']')
                {
                    model_we_push_back.push_back(']');
                    ++location_in_model;
                    model_we_push_back.push_back('/');
                    ++location_in_model;
                }
                else if(model_to_check[location_in_model] == '>')
                {
                    model_we_push_back.push_back('>');
                    ++location_in_model;
                    model_we_push_back.push_back('/');
                    ++location_in_model;
                }

                /*----------------------------*/
            }
            else
            {
                do
                {
                   model_we_push_back.push_back(model_to_check[location_in_model]);
                   ++location_in_model;
                }
                while(model_to_check[location_in_model] != '/');
                if(model_to_check[location_in_model] == '/')
                {
                    model_we_push_back.push_back('/');
                    ++location_in_model;
                }
            }
        }
        else
        {
            ++location_in_model;
        }
        if(model_we_push_back != "")
        {
            buffer = UnicodeString::fromUTF8(StringPiece(model_we_push_back));
            model.push_back(buffer);
        }
    }
}

void Simplex::parseRange(UnicodeString input, int* lower, int* upper, int startAt)
{
    bool dash;
    UnicodeString buffer = "";

    //Loop through the remaining characters in unit, and...
    for(int i = startAt; i < input.length(); ++i)
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

bool Simplex::next()
{
    bool r = false;
    if(model_index < (model.size() - 1))
    {
        ++model_index;
        r = true;
    }
    return r;
}

/*problem with literal sets lies here.
I am not keeping track of what I have already checked.*/
bool Simplex::nextInput()
{
    bool r = false;
    if(user_input < user_input_model.length()-1)
    {
        ++user_input;
        r = true;
    }
    return r;
}

bool Simplex::match(UnicodeString check)
{
    bool r = false;

    for(int i = 0; i < check.length(); ++i)
    {
        if(model[model_index][1] == '[')
        {
            r = Set(check[i]);
        }
        else
        {
            r = rule_choice(check[i], 0);
        }

        /*for testing purposes, remove when we are done*/
        std::cout << "Unit " << model_index << std::endl;
        std::string str;
        model[model_index].toUTF8String(str);
        std::cout << str << std::endl;

        if(r == true)
        {
            std::cout << "it worked" << std::endl;
        }
        else
        {
            std::cout << "it didn't work" << std::endl;
        }
        /*-----------------------------------------------*/
    }
    return r;
}

/*will be moved up*/

bool Simplex::rule_choice(UChar ch, int index)
{
    Rule rule;

    /*variable that we return*/
    bool is_matched = false;

    //Checks to make sure that the model that we are checking starts with what we want it to start with.
    if(model[model_index][0] == '^')
    {
        //The switch statement. Takes the model and checks against the user entry.
        switch(model[model_index][index + 1])
        {
        case 'a':
        {
            if(model[model_index][index + 2] == 'l')
            {
                is_matched = rule.rule_a(ch, simplexpress::CASE_LOWER);
                break;
            }
            else if(model[model_index][index + 2] == 'u')
            {
                is_matched = rule.rule_a(ch,simplexpress::CASE_UPPER);
                break;
            }
            else
            {
                is_matched = rule.rule_a(ch,simplexpress::CASE_ANY);
                break;
            }
        }
        case 'c':
        {
            is_matched = rule.rule_c();
            break;
        }
        case 'd':
        {
            is_matched = rule.rule_d(ch);
            break;
        }
        case 'e':
        {
            if(Simplex::model[model_index][index + 2] == 'l')
            {
                is_matched = rule.rule_e(ch, simplexpress::CASE_LOWER);
                break;
            }
            else if(Simplex::model[model_index][index + 2] == 'u')
            {
                is_matched = rule.rule_e(ch,simplexpress::CASE_UPPER);
                break;
            }
            else
            {
                is_matched = rule.rule_e(ch,simplexpress::CASE_ANY);
                break;
            }
        }
        case 'g':
        {
            if(Simplex::model[model_index][index + 2] == 'l')
            {
                is_matched = rule.rule_g(ch,simplexpress::CASE_LOWER);
                break;
            }
            else if(Simplex::model[model_index][index + 2] == 'u')
            {
                is_matched = rule.rule_g(ch, simplexpress::CASE_UPPER);
                break;
            }
            else
            {
                is_matched = rule.rule_g(ch,simplexpress::CASE_UPPER);
                break;
            }
        }
        case 'i':
        {
            is_matched = rule.rule_i(ch);
            break;
        }
        case 'l':
        {
            if(Simplex::model[model_index][index + 2] == 'l')
            {
                is_matched = rule.rule_l(ch,simplexpress::CASE_LOWER);
                break;
            }
            else if(Simplex::model[model_index][index + 2] == 'u')
            {
                is_matched = rule.rule_l(ch,simplexpress::CASE_UPPER);
                break;
            }
            else
            {
                is_matched = rule.rule_l(ch,simplexpress::CASE_ANY);
                break;
            }
        }

        /*Case for math operations. This returns false so is not to be used.
        It will be implemented at a later time*/
        case 'm':
        {
            is_matched = rule.rule_m();
            break;
        }
        case 'n':
        {
            is_matched = rule.rule_n(ch);
            break;
        }
        case 'o':
        {
            is_matched = rule.rule_o(ch);
            break;
        }
        case 'p':
        {
            is_matched = rule.rule_o(ch);
            break;
        }
        case 'r':
        {
            is_matched = rule.rule_r(ch);
            break;
        }
        case 's':
        {
            is_matched = rule.rule_s(ch);
            break;
        }
        case 't':
        {
            is_matched = rule.rule_t(ch);
            break;
        }
        case 'u':
        {
            int lower, upper = 10000;
            parseRange(Simplex::model[model_index], &lower, &upper);
            //If in inclusive range, true, else false.
            is_matched = (ch >= lower && ch <= upper ? true : false);
            break;
        }
        case 'w':
        {
            is_matched = rule.rule_w(ch);
            break;
        }
        case '<':
        {
            for(int i = 0; i < model[model_index].length(); ++i)
            {
                if(ch == model[model_index][index + 2 + i])
                {
                    is_matched = true;
                }
                else if(ch == model[model_index][index + 2 + i])
                {
                    is_matched = false;
                    break;
                }
                nextInput();
            }
            break;
        }

        default:
        {
            cout << "No specifier was found.\n";
        }
        }
    }
    /*if no unit found then go to the next unit. We should never get here so is this necessary?*/
    else
    {
        next();
    }

    /*checks next model whether true or false*/
    next();
    nextInput();

    return is_matched;
}

/*as of right now sets only work if no other unit is entered with then. Eg. `^[al d]/` will work
but `^[al d]/ ^al/` will not work.*/

/*will also be moved into units*/
/*unit needs to store its state*/

bool Simplex::Set(UChar ch)
{
    int i = 0;
    bool is_match = false;
    do
    {
        if(model[model_index][i+2-1]!= ' '||model[model_index][i+2-1]!='[')
        {
            ++i;
        }
        is_match = rule_choice(ch, i+1);
        if(is_match == true)
        {
            break;
        }
        ++i;
    }
    while(i != model.size());
    /*------------------------------------------------------------------*/
    return is_match;
}
}
