/** Specifier [SIMPLEXpress]
  * Version: 1.0
  *
  * Last Updated: 21 January 2020
  * Author: Ben D. Lovy, Jarek Thomas
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

#ifndef SPECIFIER_H
#define SPECIFIER_H

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"
#include "simplexpress/char_sets.hpp"

using std::cout;
using std::endl;

namespace simplexpress
{
    /*The specifier class provides an interface over stored character sets*/
    class specifier : protected char_sets
    {
        public:
            specifier(){};

            enum LetterCase
            {
                CASE_ANY = 0,
                CASE_LOWER = 1,
                CASE_UPPER = 2,
            };

            static bool s_alphanumeric(onechar, LetterCase=CASE_ANY);
            static bool s_digit(onechar, int=10);
            static bool s_latin(onechar, LetterCase=CASE_ANY);
            static bool s_whitespace(onechar);
    };

    class str_utils
    {
        public:
            str_utils(){}
            static int ch_to_hex(onechar);
            static int str_to_hex(onestring, bool=false);
            static int ch_to_int(onechar);
            static int str_to_int(onestring, bool=false);
        protected:
        private:
    };
}

#endif // UTF_TOOLS_H
