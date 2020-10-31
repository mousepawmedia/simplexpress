/** Unit parser[SIMPLEXpress]
  * Version: 0.1
  *
  * Last Updated: 04 April 2020
  * Author: Ben D. Lovy, Anna R. Dunster, Wilfrantz Dede
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

#ifndef SIMPLEXPRESS_UNITPARSER_HPP
#define SIMPLEXPRESS_UNITPARSER_HPP

#include <sstream>

#include "pawlib/core_types.hpp"
#include "pawlib/onestring.hpp"

#include "simplexpress/specifier.hpp"
#include "simplexpress/unit.hpp"

// NOTE: (to self) I'm starting to feel like using some of this for parsing in
// Simplex, too.  Take care to keep general parts separate.

std::ostream& operator<<(std::ostream& s, const UnitType& r);

/**Each parser returns a Parse Result.
 * To use this struct, define a parser function that returns a ParseResult
 * Call `ParseResult::parse(myString, myParser)` and use the resulting object to dispatch logic.
 * This will modify `input` in place on a match.
*/
class ParseResult
{
	/**Explicit constructor.
	 * Consumers need to use either make_success or make_error
	 * \param either true or false
	 * \param If matched, the matched portion.  If not, an error message
	 * \param the unparsed remainder
	*/
	ParseResult(tril, const onestring&, const onestring&);

public:
	/**This is the ultimate result of the parse operation*/
	tril result = maybe;

	/**For a success, this the successful match.
	 * For an Error, this is an error message. If empty, unknown.
	*/
	onestring s = "";

	/**This is the unparsed remainder, set in constructor.*/
	onestring remainder;

	/**The default constructor returns an Error with an empty message*/
	ParseResult();

	   /**Construct a successful match result
	 * \param The successfully matched portion
	 * \param The unparsed remainder.  "" signals completion of the match.
	*/
	static ParseResult make_success(const onestring&, const onestring&);

	/**Construct an error result.
	 * e.g.: ParseResult::make_error("Out of input!", "");
	 * \param The error message
	 * \param The unparsed remainder.  "" signals completion of the match.
	*/
	static ParseResult make_error(const onestring&, const onestring&);

	/**Perform a parse on an input
	 * \param const reference to input string
	 * \param Parser to use.  Must be a function from onestring to ParseResult
	*/
	template <typename F>
	static ParseResult parse(const onestring&, F);

	/**Get the string representation of the result
	*/
	onestring to_string() const;

	friend std::ostream& operator<<(std::ostream& s, const ParseResult& r);
};

/** UnitParser encapsulates the logic for converting a PawLIB::onestring to a
 * single Unit of a simplexpress::Simplex*/
class UnitParser
{
public:
	/**Constructor stores passed onestring for parsing
	 * \param onestring - unit to parse*/
	explicit UnitParser(onestring&);

	// Specific characters
	enum class ReservedCharacter : char
	{
		Multiple = '+',
		Negator = '!',
		Optional = '?',
		OptionalMultiple = '*',
		UnitMarker = '^',
		UnitEnd = '/',
		Unrecognized
	};

	static ReservedCharacter to_reserved_character(onechar);

	/** Holds the final parsed attributes as well as length of parsed input*/
	class ParsedAttributes
	{
	public:
		UnitAttributes attr;
		size_t size;
		ParsedAttributes(UnitAttributes, size_t);
	};

	/**Get parsed unit attributes.
	 * Returns the attributes and the size of the unit in onechars*/
	ParsedAttributes parse() const;

private:
	/**Input string being parsed*/
	onestring s;

	/**Success base message*/
	inline static const onestring success_base = "Matched ";

	/**Match a specific character at beginning of string
	 * \param reserved character to check for
	 * \param string to check against
	*/
	static ParseResult character(ReservedCharacter, onestring);

	/**Parser for '^'
	 * \param string to check against
	*/
	static ParseResult unit_marker(const onestring&);

	/**Parser for '/'
	 * \param string to check against
	*/

	static ParseResult unit_end(const onestring&);

	/**Parser for '!'
	 * \param string to check against
	*/
	static ParseResult negator(const onestring&);

	/**Parser for '+'
	 * \param string to check against
	*/
	static ParseResult multiple(const onestring&);

	/**Parser for '?'
	 * \param string to check against
	*/
	static ParseResult optional(const onestring&);

	/**Parser for '*'
	 * \param string to check against
	*/
	static ParseResult optional_multiple(const onestring&);

	/**Literal parser ensures string only contains a single onechar
	 * \param string to check against
	*/
	static ParseResult literal(const onestring&);

	/**Specifier parser ensures first character is a valid specifier
	 * \param string to check against
	*/
	static ParseResult specifier_parser(const onestring&);

	/**Modifiers returns the modifiers matched, if any.
	* Returns success if end of string found, and none matched
	* \param string to check against
	*/
	static ParseResult modifier(const onestring&);

	/**Digit parser returns digits matched, if any.
	* \param string to check against 
	*/
	static ParseResult digit_parser(const onestring&);

	/**Operator parser returns math operators matched, if any.
	* \param string to check against
	*/
	static ParseResult operator_parser(const onestring&);

	/**Alphanumeric parser returns alphanumeric characters matched, if any.
	* \param string to check against
	*/

	static ParseResult alphanumeric_parser(const onestring&);

	/**High-level parser for Unit parsing
	* */
	static ParseResult unit(const onestring&);

	/**High-level parser for Literal parsing
	* */

	/**Safely chop head off a string in place - helper function
	 * \param String to remove first character from
	*/
	static void chop(onestring&);

	friend class TestCharacterParser;
	friend class TestLiteralParser;
	friend class TestSpecifierParser;
	friend class TestModifierParser;
	friend class TestDigitsParser;
	friend class TestOperatorParser;
	friend class TestAlphanumericParser;

};

#endif // !SIMPLEXPRESS_UNITPARSER_HPP