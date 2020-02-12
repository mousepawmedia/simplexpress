/** Rules [SIMPLEXpress]
  * Version: 1.0
  *
  * Last Updated: 21 January 2020
  * Author: Jarek Thomas
  */

/* LICENSE
 * Copyright (c) 2020 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers/contributing for information
 * on how to contribute to our projects.
 */

#ifndef Rules_hpp_
#define Rules_hpp_

#include <iostream>
#include <string>
#include <vector>

#include "pawlib/onechar.hpp"

using std::vector;

enum Spec_Case{
    CASE_ANY,
    CASE_LOWER,
    CASE_UPPER
};
/*The Rule class specifies what each rule we want is suppose to do. As the rules expand or
change it is easy to go in and change one rule or add one without having to change
much code at all*/
class Rule
{
public:
    Rule() = default;
    /*Below are all the rules for each specifier. Theses are called from
    Unit::rule_choice based off what the user enters for a model in a switch statement*/
    /**Specifier for alphanumeric.
    \param pass in a onechar so it know what to search for
    \param optional bool if case must be lower
    \param optional bool if case must be upper*/
    bool rule_a(onechar, Spec_Case = CASE_ANY);
    /** Specifier for Classification. Will be able to run different
    language supports through unicode. Will be implemented later*/
    bool rule_c();
    /**Specifier for a digit. For now only takes 0-9 as possible digits
    will expand later to include hex and larger numbers.
    \param Pass in a onechar so it knows what it is searching for
    \param Required int to check if truly number*/
    bool rule_d(onechar);
    /**Specifier for extended Latin.
    \param pass in a onechar so it know what to search for
    \param optional bool if case must be lower
    \param optional bool if case must be upper*/
    bool rule_e(onechar, Spec_Case = CASE_ANY);
    /**Specifier for Greek.
    \param pass in onechar so knows what to look for
    \param optional bool  if case must be lower
    \param optional bool if case must be upper*/
    bool rule_g(onechar, Spec_Case = CASE_ANY);
    /**Specifier for ipa
    \param Pass in onechar so knows wha to search for*/
    bool rule_i(onechar);
    /**Specifier for Latin
    \param Pass in onechar so knows what to search for
    \param optional bool if case must be upper
    \param optional bool if case must be lower*/
    bool rule_l(onechar, Spec_Case = CASE_ANY);
    /**Specifier for math. Will provide means to do any kind of math
    from basic algebra to calculus. Will be implemented later.*/
    bool rule_m();
    /**Specifier for new line
    \param pass in a onechar so knows what to look for*/
    bool rule_n(onechar);
    /**Specifier for math operators
    \param pass in onechar so knows what to search for*/
    bool rule_o(onechar);
    /**Specifier for punctuation
    \param pass in onechar so knows what to search for*/
    bool rule_p(onechar);
    /**Specifier for carriage return
    \param pass in onechar so knows what to search for*/
    bool rule_r(onechar);
    /**Specifier for a literal space
    \param pass in a onechar so knows what to look for*/
    bool rule_s(onechar);
    /**Specifier for tab
    \param pass in a onechar so knows what to search for*/
    bool rule_t(onechar);
    /**Specifier for Unicode. This is full unicode support
    \param pass in onechar so knows what to look for*/
    bool rule_u(onechar);
    /**Specifier for whitespace
    \param pass in onechar so knows what to look for*/
    bool rule_w(onechar);
};
#endif
