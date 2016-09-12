#ifndef Simplex_H_
#define Simplex_H_

#include <vector>
#include <iostream>
#include "Rules.hpp"
#include <string>
#include <unicode/unistr.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>//want to get rid of these and get rid of uchar and use pawchar
#include "Unit.hpp"

using std::vector;
using std::string;

namespace simplexpress{
    /*The simplex class is the overall model of Simplexpress.
    A simplex contains a vector(for now) of Units Everything
    entered outside a unit is taken as a literal and must be
    matched exactly.*/
    class Simplex
    {
        public:
            /**The model itself*/
            std::vector<Unit*> model;

            /**To keep track of where we are in the model.*/
            int model_index = 0;

            /**enumeration to roughly determine how we are
            interpreting as we parse through the model.*/
            enum parse_status
            {
                NORMAL = 0,
                IN_UNIT = 1,
                ESCAPED = 2,
                SPACE_CONVERT = 3
            };

            /**Used to keep track of whether we are in a unit
            or not. If we encounter a `^` then we add 1 and
            if we encounter a `/` then we subtract 1. If
            we try to go below 0 then an error is thrown as
            there is nothing to escape.*/
            uint16_t unit_counter = 0;

            /**Constructor, When a Simplex is created
            parse_input is called to parse through what
            the user has defined their model to be.
            Then it will call match to check everything
            against the model.
            \param string, First string is for the user
            defined model.
            \param string, Second string is what we are
            checking against the model.*/
            Simplex(string,string);

            /**Parses through what the user has defined
            what they want their model to be.
            Uses enumeration to pull out each type of
            model we can have.
            \param string, What the user has defined
            their model to be.*/
            void parse_model(string);

            /**Takes the user defined model and matches
            everything that the user wants against the model.
            \param string, What is being checked against
            the model.*/
            bool match(string);

            /**Moves to the next unit or literal in the model.*/
            bool next();
    };
}

#endif
