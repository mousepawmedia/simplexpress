#include <iostream>
#include <string>
#include "simplexpress.hpp"
#include "utf_tools.hpp"
#include <unicode/unistr.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>

//REMEMBER TO SET COMPILER: --cflags --libs icu-uc icu-io

using std::string;
using simplexpress::Simplex;
using simplexpress::char_sets;
using simplexpress::utf_utils;

int main()
{
    simplexpress::char_sets chars;
    std::cout << "SIMPLEXpress v1.0\n"
              << "Copyright (C) 2015 MousePaw Games. All Rights Reserved.\n"
              << "'#exit' to quit.\n"
              << "-----\n" << std::endl;

    UnicodeString buffer;
    string std_buffer;
    std::cout << "Enter a model: ";
    if(std_buffer == "#EXIT" && std_buffer == "#exit")
    {
        return 0;
    }
    getline(std::cin, std_buffer);
    buffer = UnicodeString::fromUTF8(StringPiece(std_buffer));
    Simplex simplex(buffer);

    //Do while command is not the pseudocommand #EXIT (or #exit)...
    do
    {
        //Get the user input.
        getline(std::cin, std_buffer);
        buffer = UnicodeString::fromUTF8(StringPiece(std_buffer));
        bool r = simplex.match(buffer);
        std::cout << r << std::endl;
    }
    while(std_buffer != "#EXIT" && std_buffer != "#exit");

    return 0;
}
