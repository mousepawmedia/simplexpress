/** Specifier [SIMPLEXpress]
  * Version: 0.1
  *
  * Author: Ben D. Lovy, Jarek Thomas, Anna R. Dunster
  * Last Updated: 04 April 2020
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

#ifndef SIMPLEXPRESS_SPECIFIER_HPP
#define SIMPLEXPRESS_SPECIFIER_HPP

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"
#include "simplexpress/char_sets.hpp"
#include "simplexpress/rules.hpp"

/*The specifier class provides an interface over stored character sets*/
class Specifier : protected char_sets
{
public:
	Specifier() = default;

	/* All the supported variants of specifier */
	enum class SpecifierType : char
	{
		Any = '.',
		Alphanumeric = 'a',
		Classification = 'c',
		Digit = 'd',
		// ExtendedLatin = 'e', // FIXME: T1278
		// Greek = 'g', // FIXME: T1278
		// IPA = 'i', // FIXME: T1278
		LatinLetter = 'l',
		Math = 'm',
		Newline = 'n',
		MathOperator = 'o',
		Punctuation = 'p',
		CarriageReturn = 'r',
		Space = 's',
		Tab = 't',
		// Unicode = 'u', // FIXME: T1278
		Whitespace = 'w',
		Unsupported,
	};

	static SpecifierType to_specifier_type(onechar);

	static bool s_alphanumeric(onechar, Rule::LetterCase = Rule::LetterCase::Any);

	static bool s_digit(onechar, int=10);

	static bool s_latin(onechar, Rule::LetterCase = Rule::LetterCase::Any);

	static bool s_whitespace(onechar);
};

class str_utils
{
public:
	str_utils() = default;

	static int ch_to_hex(onechar);

	static int str_to_hex(onestring, bool=false);

	static int ch_to_int(onechar);

	static int str_to_int(onestring, bool=false);
};

#endif
