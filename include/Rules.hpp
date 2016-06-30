#ifndef Rules_hpp_
#define Rules_hpp_

#include <iostream>
#include <string>
#include <vector>
#include <unicode/unistr.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>//want to get rid of these and get rid of uchar and use pawchar
#include "utf_tools.hpp"

using std::vector;

namespace simplexpress{
    enum Spec_Case{
        CASE_ANY,
        CASE_LOWER,
        CASE_UPPER
    };
    /*The Rule class specifies what each rule we want is suppose to do. As the rules expand or
    change it is easy to go in and change one rule or add one without having to change
    much code at all*/
    class Rule{

        public:
            Rule(){};
            /*Below are all the rules for each specifier. Theses are called from
            Unit::rule_choice based off what the user enters for a model in a switch statement*/

            /**Specifier for alphanumeric.
            \param pass in a UChar so it know what to search for
            \param optional bool if case must be lower
            \param optional bool if case must be upper*/
            bool rule_a(UChar, Spec_Case = CASE_ANY);

            /** Specifier for Classification. Will be able to run different
            language supports through unicode. Will be implemented later*/
            bool rule_c();


            /**Specifier for a digit. For now only takes 0-9 as possible digits
            will expand later to include hex and larger numbers.
            \param Pass in a UChar so it knows what it is searching for
            \param Required int to check if truly number*/
            bool rule_d(UChar);

            /**Specifier for extended Latin.
            \param pass in a UChar so it know what to search for
            \param optional bool if case must be lower
            \param optional bool if case must be upper*/
            bool rule_e(UChar, Spec_Case = CASE_ANY);

            /**Specifier for Greek.
            \param pass in UChar so knows what to look for
            \param optional bool  if case must be lower
            \param optional bool if case must be upper*/
            bool rule_g(UChar, Spec_Case = CASE_ANY);

            /**Specifier for ipa
            \param Pass in UChar so knows wha to search for*/
            bool rule_i(UChar);

            /**Specifier for Latin
            \param Pass in UChar so knows what to search for
            \param optional bool if case must be upper
            \param optional bool if case must be lower*/
            bool rule_l(UChar, Spec_Case = CASE_ANY);

            /**Specifier for math. Will provide means to do any kind of math
            from basic algebra to calculus. Will be implemeted later.*/
            bool rule_m();

            /**Specifier for new line
            \param pass in a UChar so knows what to look for*/
            bool rule_n(UChar);

            /**Specifier for math operators
            \param pass in Uchar so knows what to search for*/
            bool rule_o(UChar);

            /**Specifier for punctuation
            \param pass in UChar so knows what to search for*/
            bool rule_p(UChar);

            /**Specifier for carriage return
            \param pass in UChar so knows what to search for*/
            bool rule_r(UChar);

            /**Specifier for a literal space
            \param pass in a UChar so knows what to look for*/
            bool rule_s(UChar);

            /**Specifier for tab
            \param pass in a UChar so knows what to search for*/
            bool rule_t(UChar);

            /**Specifier for Unicode. This is full unicode support
            \param pass in UChar so knows what to look for*/
            bool rule_u(UChar);

            /**Specifier for whitespace
            \param pass in UChar so knows what to look for*/
            bool rule_w(UChar);

    };
}
#endif
