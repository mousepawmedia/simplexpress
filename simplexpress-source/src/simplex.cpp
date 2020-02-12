#include "simplexpress/simplex.hpp"
#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"

// NOTE: I think I want to take model_check out of the constructor
Simplex::Simplex(onestring user_model)
{
    parse_model(user_model);
}

bool Simplex::next()
{
    if(model_index+1 >= model.size())
    {
        return false;
    }
    else
    {
        ++model_index;
        return true;
    }
}

void Simplex::parse_model(onestring user_model)
{
    //used to hold the different types
    onestring buffer, literals, in_unit;
    int unit_counter = 0;
    parse_status Status = NORMAL;
    /*The loop that checks character by character and parses
    it into the type based off user entry.*/
    for(uint16_t i = 0; i < user_model.length(); ++i)
    {
        /*The switch that is used to determine what
        we are doing. e.g. whether we are in a unit or
        a set or just passing in as normal*/
        switch(*user_model[i].c_str())
        {
        case '^':
            {
                Status = IN_UNIT;
                ++unit_counter;
                break;
            }
        case '/':
            {
                Status = ESCAPED;
                --unit_counter;
                if(unit_counter < 0)
                {
                    std::cout << "Invalid. Trying to escape when not in a unit.\n";
                }
                break;
            }
        case ' ':
            {
                Status = SPACE_CONVERT;
                break;
            }
        }
        /*Switch that is used to determine how we are parsing
        based off the status that is set from the first switch.*/
        switch(Status)
        {
        case NORMAL:
            {
                literals.push_back(user_model[i]);
                // NOTE: It was passed through in intermediatry ICU StringPieces
                buffer = literals;
                Unit *unit = new Unit(buffer);
                model.push_back(unit);
                literals.clear();
                break;
            }
        case IN_UNIT:
            {
                if(user_model[i] == ' ')
                {
                    Status = SPACE_CONVERT;
                }
                else
                {
                    in_unit.push_back(user_model[i]);
                }
                break;
            }
        case ESCAPED:
            {
                in_unit.push_back('/');
                // FIXME: see line 78
                buffer = in_unit;
                Unit* unit = new Unit(buffer);
                model.push_back(unit);
                in_unit.clear();
                Status = NORMAL;
                break;
            }
        case SPACE_CONVERT:
            {
                in_unit.push_back('/');
                // FIXME: see line 78
                buffer = in_unit;
                Unit *unit = new Unit(buffer);
                model.push_back(unit);
                in_unit.clear();
                std::cout << user_model[i] << "\n";
                in_unit.push_back('^');
                Status = IN_UNIT;
            }
        }
    }
}

bool Simplex::match(onestring model_check)
{
    onestring buffer = model_check;
    while(!buffer.empty())
    {
        int matched = model[model_index]->check_model(buffer);
        std::cout << "Matching " << buffer;
        std::cout << " against " << *model[model_index] << "... ";
        std::cout << (matched > -1 ? "true" : "false") << "\n";

        // Only advance if we're matching
        if (matched > -1)
        {
            // On a match, remove the matched amount from the front
            if (static_cast<int>(buffer.length()) > matched)
            {
                onestring new_buffer = buffer.substr(matched);
                buffer = new_buffer;
            }
            else
            {
                // We consumed the whole string, exit the loop
                break;
            }
            if (!next())
                break; // we're done
        }
        else
            return false;  // failed a match
    }
    // Reset simplex counter for future matches
    // NOTE: I think model_index should be a local var, and this method static
    model_index = 0;
    return true;
}
