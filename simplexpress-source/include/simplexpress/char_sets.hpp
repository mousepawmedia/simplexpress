/** char_sets [SIMPLEXpress]
  * Version: 0.1
  *
  * Last Updated: 04 April 2020
  * Authors: Ben D. Lovy, Jarek Thomas
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

#ifndef SIMPLEXPRESS_CHAR_SETS_H
#define SIMPLEXPRESS_CHAR_SETS_H

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"

using std::cout;
using std::endl;

/** The char_sets class holds categories of characters to match against*/
class char_sets
{
public:
	char_sets() = default;

	// Atomic Sets

	/**Checks to see if the character is a digit.
	\param the character to check
	\param the radix for the digit, default 10.
	\return true if in set, else false*/
	static bool digit(onechar, int=10);

	/**Checks to see if the character is a lowercase
	letter (Latin alphabet.)
	\param the character to check
	\return true if in set, else false*/
	static bool latin_lower(onechar);

	/**Checks to see if the character is a lowercase
	extended Latin letter.
	\param the character to check
	\param whether to include standard Latin letters
	\return true if in set, else false*/
	static bool latin_ext_lower(onechar, bool = true);

	/**Checks to see if the character is an uppercase
	Latin alphabet letter.
	\param the character to check
	\return true if in set, else false*/
	static bool latin_upper(onechar);

	/**Checks to see if the character is an uppercase
	extended Latin letter.
	\param the character to check
	\param whether to include standard Latin letters
	\return true if in set, else false*/
	static bool latin_ext_upper(onechar, bool = true);

	/**Checks to see if the character is in Greek/Coptic
	block. We cannot simply use _upper and _lower, as
	there are several valid characters not included in
	either of those subsets due to ambiguity.
	\param the character to check
	\return true if in set, else false*/
	static bool greek(onechar);

	/**Checks to see if the character is a lowercase
	Greek letter.
	\param the character to check
	\return true if in set, else false*/
	static bool greek_lower(onechar);

	/**Checks to see if the character is an uppercase
	Greek letter.
	\param the character to check
	\return true if in set, else false*/
	static bool greek_upper(onechar);

	// Combined Language Sets
	/**Alias for latin(onechar).
	\param the character to check
	\return true if in set, else false*/
	static bool alpha(onechar);

	//See "greek" under atomic sets.
	/**Checks to see if the character is a Latin alphabet
	letter, either uppercase or lowercase.
	\param the character to check
	\return true if in set, else false*/
	static bool latin(onechar);

	/**Checks to see if the character is a Latin extended
	character of any sort.
	\param the character to check
	\param whether to including standard Latin letters
	\return true if in set, else false*/
	static bool latin_ext(onechar, bool = true);

	/**Checks to see if the character is a Latin extended
	letter, either uppercase or lowercase.
	\param the character to check
	\param whether to including standard Latin letters
	\return true if in set, else false*/
	static bool latin_ext_letter(onechar, bool = true);

	// Utility Sets

	/**Checks to see if the character is part of the IPA. This
	is primarily used for recognizing dictionary pronunciations.
	Follows "http://www.phon.ucl.ac.uk/home/wells/ipa-unicode.htm".
	Also includes underscore, for separation reasons.
	\param the character to check
	\return true if in set, else false*/
	static bool ipa(onechar);

	/**Checks to see if the character is non-breaking whitespace.
	\param the character to check
	\param whether to include visible space characters
	\return true if in set, else false*/
	//TODO: Change the default on includeVisible based on email responses.
	// NOTE: what email responses?  True sounds like a good default to me - BDL
	static bool whitespace(onechar, bool = true);

protected:
	static int char_bin_search(const int[], const int, int);

	static const int LATIN_EXT_LOWER_CNT = 189;
	static const int arr_latin_ext_lower[LATIN_EXT_LOWER_CNT];

	static const int GREEK_LOWER_CNT = 54;
	static const int arr_greek_lower[GREEK_LOWER_CNT];

	static const int GREEK_UPPER_CNT = 57;
	static const int arr_greek_upper[GREEK_UPPER_CNT];

	static const int IPA_VARIOUS_CNT = 32;
	static const int arr_ipa_various[IPA_VARIOUS_CNT];

	static const int WHITESPACE_CNT = 25;
	static const int arr_whitespace[WHITESPACE_CNT];

	static const int WHITESPACE_BRK_CNT = 7;
	static const int arr_whitespace_brk[WHITESPACE_BRK_CNT];

	static const int WHITESPACE_SYMB_CNT = 6;
	static const int arr_whitespace_symb[WHITESPACE_SYMB_CNT];

	static const int SPECIAL_DUODECIMAL_CNT = 9;
	static const int arr_special_duodecimal[SPECIAL_DUODECIMAL_CNT];
};

#endif // CHAR_SETS_H