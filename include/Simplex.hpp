#ifndef Unit_H_
#define Unit_H_

#include <vector>
#include <iostream>
#include "Rules.hpp"
#include <string>
#include <unicode/unistr.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>//want to get rid of these and get rid of uchar and use pawchar

using std::vector;
using std::string;

namespace simplexpress{
    /*The Unit class is the over all model that we will be checking.
    Upon creation it checks all the Units that the user has enter that
    are either split by `^/`, ` /` or `  `. When being put into the
    model all spaces are converted to be separate units for purposes of
    reading through them.*/
class Simplex
{
    public:
        /**The model itself.*/
        vector<UnicodeString> model;

        /**what we are checking against the model.*/
        UnicodeString user_input_model;

        /**Keeps track of where we are in the model*/
        int model_index = 0;

        /**Keeps track of where we are in the input
        checking against the model*/
        int user_input = 0;

        /**takes the user string input and parses through it to
        pull out the units and then place them inside a vector(will be changed
        to new data structure when those are done).
        \param user input string for the model*/
        void parseInput(string);

        /**When object is created takes units out of user input and puts then in the vector.
        \param takes a UnicodeString input to check against unicode characters*/
        Simplex(string, string);

        /**destructor not used*/
        ~Simplex(){}

        /**Extract lower and possible upper hex values in range from
        a string.
        \param the string to extract range from.
        \param a pointer to an integer for storing lower range
        \param an optional pointer to an integer for storing upper range
        \param the index to start at for parsing. Default 2 (i.e. after
        the modifier `\C` or `\U`*/
        void parseRange(UnicodeString, int*, int* = 0, int = 2);

        /**Goes to the next Unit in the model
        still need to implement*/
        bool next();

        /**Goes to the next UChar of what we are checking against the model.*/
        bool nextInput();

        /** The function that takes what the user entered and matches it to the
        model that they entered previously. Calls rule_choice.
        \param The UnicodeString that user entered and is used to match to the model*/
        bool match(UnicodeString check);

        /**Checks the model to the user input. Right now can only check one character to one
        model. In future will be able to check more characters to one model if user specifies so.
        \param UChar that is passed in by match().*/
        bool rule_choice(UChar, int);

        /**Checks through all specifiers in a set. Calls rule_choice to check specifiers.
        \param UChar of user input*/
        bool Set(UChar);

        bool literalSet(UChar);
};
}

#endif
