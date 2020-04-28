/** UTF Tools [SIMPLEXpress]
  * Version: 0.1
  *
  * Last Updated: 04 April 2020
  * Author: Ben D. Lovy, Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Media.
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

#ifndef SIMPLEXPRESS_UTF_TOOLS_H
#define SIMPLEXPRESS_UTF_TOOLS_H

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"
#include "simplexpress/specifier.hpp"

// FIXME: T1278
/*The utf_utils class extends specifier to support Unicode .*/
class utf_tools : public Specifier
{
public:
	utf_tools() = default;

	static bool s_digit(onechar, int=10);
	static bool s_greek(onechar, Rule::LetterCase=Rule::LetterCase::Any);
	static bool s_ipa(onechar);
	static bool s_latin_ext(onechar, Rule::LetterCase=Rule::LetterCase::Any);
};
// FIXME: T1278
//class utf_utils
//{
//public:
//    utf_utils(){}
//    // TODO virtual?
//    static int ch_to_hex(onechar);
//    static int str_to_hex(onestring, bool=false);
//    static int ch_to_int(onechar);
//    static int str_to_int(onestring, bool=false);
//protected:
//private:
//};

#endif // UTF_TOOLS_H
