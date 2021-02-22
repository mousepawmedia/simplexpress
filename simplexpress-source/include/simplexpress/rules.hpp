/** Rules [SIMPLEXpress]
 * Version: 0.1
 *
 * Author: Anna R. Dunster, Ben D. Lovy, Graham Mix, Jarek Thomas
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

#ifndef SIMPLEXPRESS_RULES_HPP
#define SIMPLEXPRESS_RULES_HPP

#include <iostream>
#include <string>
#include <vector>

#include "onestring/onechar.hpp"

using std::vector;

/**The Rule class specifies what each rule we want is suppose to do. As the
 * rules expand or change it is easy to go in and change or add one rule at a
 * time.
 */
class Rule
{
public:
	/**Case types used throughout the parser*/
	enum class LetterCase {
		Any,
		Lower = 'l',
		Upper = 'u',
	};

	static LetterCase to_letter_case(onechar);

	Rule() = default;
	/**Below are all the rules for each specifier. These are called from other
	 * functions and classes, based off the user entered model. */

	/**Specifier for alphanumeric.
	 * \param ch onechar to check for a match
	 * \param letterCase LetterCase (optional) to check for upper or lower */
	bool static rule_a(onechar, LetterCase = LetterCase::Any);

	/**Specifier for Classification. Will be able to run different
	 * language supports through unicode. Will be implemented later */
	bool static rule_c();

	/**Specifier for a digit. Matches 0-9 as possible digits.
	 * Can expand later to include hex and larger numbers.
	 * \param ch onechar to check for a match */
	bool static rule_d(onechar);

	/**Specifier for digits outside of base 10.
	 * // NOT IMPLEMENTED //
	 * \param ch onechar to check for a match
	 * \param radix int for base system being used */
	bool static rule_d(onechar, int);

	/**Specifier for extended Latin.
	 * \param ch onechar to check for a match
	 * \param letterCase LetterCase (optional) to check for upper or lower */
	bool static rule_e(onechar, LetterCase = LetterCase::Any);

	/**Specifier for Greek.
	 * \param ch onechar to check for a match
	 * \param letterCase LetterCase (optional) to check for upper or lower */
	bool static rule_g(onechar, LetterCase = LetterCase::Any);

	/**Specifier for IPA.
	 * \param ch onechar to check for a match */
	bool static rule_i(onechar);

	/**Specifier for Latin.
	 * \param ch onechar to check for a match
	 * \param letterCase LetterCase (optional) to check for upper or lower */
	bool static rule_l(onechar, LetterCase = LetterCase::Any);

	/**Specifier for new line
	 * \param ch onechar to check for a match */
	bool static rule_n(onechar);

	/**Specifier for math operators.
	 * \param ch onechar to check for a match */
	bool static rule_o(onechar);

	/**Specifier for punctuation.
	 * \param ch onechar to check for a match */
	bool static rule_p(onechar);

	/**Specifier for carriage return.
	 * \param ch onechar to check for a match */
	bool static rule_r(onechar);

	/**Specifier for a literal space.
	 * \param ch onechar to check for a match */
	bool static rule_s(onechar);

	/**Specifier for tab.
	 * \param ch onechar to check for a match */
	bool static rule_t(onechar);

	/**Specifier for Unicode. This is full unicode support.
	 * \param ch onechar to check for a match */
	bool static rule_u(onechar);

	/**Specifier for whitespace.
	 * \param ch onechar to check for a match */
	bool static rule_w(onechar);

	/**Specifier for Any: fails newline and return.
	 * \param ch onechar to check for a match */
	bool static rule_z(onechar);
};
#endif
