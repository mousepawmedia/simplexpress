#include "simplexpress.h"

namespace simplexpress
{
    Simplex::simplex(string modelString)
    {
        parseModel(modelString);
    }

    void Simplex::flush()
    {
        //Reset all temporary data variables.
        ciBuffer = "";
        clBuffer = "";
        modelIndex = 0;

        //Note that we leave models and option flags alone.
    }

    bool Simplex::match(string check)
    {
        //NOTE: Perhaps match should subtly call lex()?
    }

    void Simplex::parseModel(string input)
    {
        /*SIMPLEXpress' syntax is space-delimited, which makes parsing quite
        easy - just split by spaces.*/

        //If model is not empty, get out of Dodge!
        if(model.size() != 0)
        {
            return;
        }

        //The buffer for the current unit.
        string unit;

        //For each index in the input string...
        for(int i = 0; i < input.length(); i++)
        {
            //If the character is a space and unit is not empty.
            if(input[i] == ' ' && unit != "")
            {
                //Push the unit to the model vector.
                model.push_back(unit);
            }
            else
            {
                //Add the current character to unit.
                unit += input[i];
            }
        }
    }

    Simplex::~Simplex()
    {
        //dtor
    }
}
