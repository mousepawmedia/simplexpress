#ifndef SIMPLEXPRESS_H
#define SIMPLEXPRESS_H

#include <iostream>
#include <string>
#include <vector>

#include <unicode/unistr.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>

#include "utf_tools.hpp"

using std::string;
using std::vector;

using simplexpress::specifier;

namespace simplexpress
{
    class BaseSimplex
    {
        public:
            enum Trilean
            {
                TRI_FALSE = 0,
                TRI_MAYBE = 1,
                TRI_TRUE = 2,
            };

            ///Constructor
            BaseSimplex(){}

            ///Destructor
            ~BaseSimplex(){}
        protected:

            /**Parse the model, separating it into the array.
            \param the model string to parse.*/
            void parseModel(UnicodeString);

            /**Extract lower and possible upper hex values in range from
            a string.
            \param the string to extract range from.
            \param a pointer to an integer for storing lower range
            \param an optional pointer to an integer for storing upper range
            \param the index to start at for parsing. Default 2 (i.e. after
            the modifier `\C` or `\U`*/
            void parseRange(UnicodeString, int*, int* = 0, int = 2);

            /**Lex the given character using the model.
            \param the character to lex
            \return true if still matching, else false*/
            bool base_lex(UChar);

            ///Option flag to ignore the case of the letters.
            bool ignoreCase = false;

            ///Flush the system, restoring temporary variables to defaults.
            virtual void flush();

            ///Option flag that the string must fully match the model.
            bool fullMatch = true;

            ///The model itself.
            vector<UnicodeString> model;

            ///Move to the previous unit.
            bool prev();
            ///Move to the next unit.
            bool next();
            ///Move to the previous character in the unit.
            bool unitPrev();
            ///Move to the next character in the unit.
            bool unitNext();

            static specifier specifier_tests;
        protected:
            ///The model index (current unit).
            short int modelIndex = 0;
            ///The unit index, usually used for literal units.
            short int unitIndex = 0;

        private:
            //The temporary return for certain tests.
            bool temp_r = false;
            //Whether we're testing in a group.
            bool flag_group = false;
    };

    /**A normal Simplex, which accepts strings.*/
    class Simplex : public BaseSimplex
    {
        public:
            /**Constructor
            \param the SIMPLEXpress model
            \param the flags*/
            Simplex(UnicodeString);

            /**Return the number of matches within the string.
            \param the string to check
            \return the number of matches*/
            int count(UnicodeString);

            /**Check if the string matches the model.
            \param the string to check
            \return TRUE (1) if match, FALSE (0) otherwise.*/
            bool match(UnicodeString);

            /**Returns only the part of the input string that matches.
            \param the string to trim.
            \return the part of the string that matches; empty string if no match
            */
            UnicodeString trim(UnicodeString);

            ~Simplex();
        protected:
        private:
    };

    /**A Simplex-based parser, which accepts single characters instead of
    strings, and remembers its state.*/
    class CharSimplex : public BaseSimplex
    {
        public:
            CharSimplex(UnicodeString);

            /**Add the character to the buffer and check it against the model.
            \param the character to lex
            \return TRUE (2) if match, MAYBE (1) if partial match, else FALSE (0).
            */
            Trilean lex(char);

            /**Restores the simplex to its initialized state.*/
            void flush();

            ~CharSimplex();
        protected:
            ///If currently lexing characters, flag as ALIVE.
            bool alive = false;

            ///The pointer to the buffer to be used.
            UnicodeString* buffer;

            ///Case insensitive buffer.
            UnicodeString ciBuffer = "";

            ///Case sensitive buffer.
            UnicodeString clBuffer = "";
        private:
    };

}
#endif // SIMPLEXPRESS_H
