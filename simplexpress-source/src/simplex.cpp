#include "simplexpress/simplex.hpp"
#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"

namespace simplexpress
{
    Simplex::Simplex(string user_model, string model_check)
    {
        parse_model(user_model);
        match(model_check);
    }

    bool Simplex::next()
    {
        bool return_var = false;
        if(model_index+1 > model.size())
        {
            return_var = false;
        }

        else
        {
            ++model_index;
            return_var = true;
        }
        return return_var;
    }

    void Simplex::parse_model(string user_model)
    {
        //used to hold the different types
        std::string literals, in_unit;

        int unit_counter = 0;
        onestring buffer;

        parse_status Status = NORMAL;

        /*The loop that checks character by character and parses
        it into the type based off user entry.*/
        for(uint16_t i = 0; i < user_model.length(); ++i)
        {
            /*The switch that is used to determine what
            we are doing. e.g. whether we are in a unit or
            a set or just passing in as normal*/
            switch(user_model[i])
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
                        std::cout << "Invalid. Trying to escape when not in anything.\n";
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
                    std::cout << user_model[i] << std::endl; // NOTE: I've always used "\n", is endl preferred?
                    in_unit.push_back('^');
                    Status = IN_UNIT;
                }
            }
        }
    }

    bool Simplex::match(string model_check)
    {
        bool return_var = false;
        // FIXME: see line 78
        onestring buffer = onestring(model_check);
        for(uint16_t i = 0; i < buffer.length(); ++i)
        {
            return_var = model[model_index]->check_model(buffer[i]);
            std::cout << "1 it matched, 0 it didn't.\n";
            std::cout << return_var << std::endl;

            next();
        }

        return return_var;
    }
}
