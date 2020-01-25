#include <iostream>
#include <string>
#include <vector>

#include "simplexpress/simplex.hpp"

#include "pawlib/onestring.hpp"
#include "pawlib/onechar.hpp"

using std::vector;
using std::string;

/**change unit class to be named `Simplex`*/
using simplexpress::Simplex;

// NOTE: here's an ASCII test model: ^l+/-^a+/^d/.png^(24)?/
// TODO: Make a bunch more

int main()
{

    std::cout << "SIMPLEXpress v0.2\n"
              << "Copyright (C) 2015-2020 MousePaw Media. All Rights Reserved.\n"
              << "'#exit' or #EXIT to quit.\n"
              << "-----\n" << std::endl;
    string input, model;
    do{
        std::cout << "Please enter a model: ";
        getline(std::cin, model);
        if(model == "#exit" || model == "#EXIT")
            break;
        std::cout << "Enter what you want checked against model: ";
        getline(std::cin, input);

        Simplex simplex(model, input);
    }while(model!="#exit"||model!="#EXIT");
}
