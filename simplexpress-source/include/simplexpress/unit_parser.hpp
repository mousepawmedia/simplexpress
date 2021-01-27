/** Unit parser [SIMPLEXpress]
 * Version: 0.1
 *
 * Author: Wilfrantz Dede, Anna R. Dunster, Ben D. Lovy
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
#include "pawlib/flex_array.hpp"
#include "pawlib/onestring.hpp"
#include "simplexpress/specifier.hpp"
#include "simplexpress/unit.hpp"


/**Each parser returns a Parse Result.
 * To use this struct, define a parser function that returns a ParseResult.
 * Call `ParseResult::parse(myString, myParser)` and use the resulting object
 * to dispatch logic. Returns match and remainder of string.
 */
class ParseResult
{
	/** Explicit constructor.
	 * Consumers need to use either make_success or make_error
	 * \param tril: either true or false
	 * \param onestring: the matched portion, or the error message if none
	 * \param onestring: unparsed remainder
	 */
	ParseResult(tril, const onestring&, const onestring&);

	/**The default constructor returns an Error with an empty message*/
	ParseResult();

public:
	/**This is the ultimate result of the parse operation*/
	tril result = maybe;

	/**For a success, this the matched part of the input.
	 * For an Error, this is an error message. If empty, unknown.
	 */
	onestring parsedstring = "";

	/**This is the unparsed remainder, set in constructor.*/
	onestring remainder;

	/** Construct a successful match result
	 * \param onestring: the successfully matched portion
	 * \param onestring: the unparsed remainder, or "" if complete
	 */
	static ParseResult make_success(const onestring&, const onestring&);

	/** Construct an error result.
	 * e.g.: ParseResult::make_error("Out of input!", "");
	 * \param onestring: the error message
	 * \param onestring: the unparsed remainder, or "" if complete
	 */
	static ParseResult make_error(const onestring&, const onestring&);

	/** Perform a parse on an input.
	 * \param onestring: reference to input string
	 * \param Parser to use. Must be a function from onestring to ParseResult
	 */
	template<typename F> static ParseResult parse(const onestring&, F);

	/**Get the string representation of the result */
	onestring to_string() const;

	friend std::ostream& operator<<(std::ostream& s, const ParseResult& r);
};

/** Return type for UnitParser's parse() function.
 * Contains the UnitAttributes for Unit construction, and the length of parsed
 * input in onechars to progress within parse_model(). */
struct ParsedAttributes
{
	UnitAttributes attr;
	size_t size;
	ParsedAttributes(UnitAttributes, size_t);
};

/** UnitParser encapsulates the logic for converting a PawLIB::onestring to a
 * single Unit of a simplexpress::Simplex model*/
class UnitParser
{
public:
	/** Constructor stores passed onestring for parsing.
	 * \param onestring: unit to parse*/
	explicit UnitParser(onestring&);

	// Specific characters
	enum class ReservedCharacter : char {
		Multiple = '+',
		Negator = '!',
		Optional = '?',
		OptionalMultiple = '*',
		UnitMarker = '^',
		UnitSnag = '~',
		UnitEnd = '/',
		Escape = '%',
		Unrecognized
	};

	static ReservedCharacter to_reserved_character(onechar);

	/**Get parsed unit attributes.
	 * Returns the attributes and the size of the unit in onechars*/
	ParsedAttributes parse() const;

	/** Parses through the user defined model to generate Unit array. Used by
	 * the Simplex class's constructor.
	 * \param user_model onestring user definition of model
	 * \param model_array array to contain the Units.*/
	void static parse_model(const onestring&, FlexArray<Unit*>&);

private:
	/**Input string being parsed*/
	onestring parsedstring;

	/**Success base message*/
	inline static const onestring success_base = "Matched ";

	/** Match a specific character at beginning of string
	 * \param rc ReservedCharacter to check for
	 * \param in onestring to check */
	static ParseResult character(ReservedCharacter rc, onestring in);

	/** Parser to check if initial character signals beginning of a unit.
	 * \param in onestring to check */
	static ParseResult unit_marker(const onestring& in);

	/** Parser to check if initial character signals beginning of a snag unit.
	 * \param in onestring to check */
	static ParseResult unit_snag(const onestring& in);

	/** Parser to check if initial character signals end of a unit.
	 * \param in onestring to check */
	static ParseResult unit_end(const onestring& in);

	/** Parser to check if escape character to signal next character as a
	 * literal.
	 * \param in onestring to check */
	static ParseResult escape(const onestring& in);

	/** Parser to check if initial character signals negation specifier.
	 * \param in onestring to check */
	static ParseResult negator(const onestring& in);

	/** Parser to check if initial character signals multiple specifier.
	 * \param in onestring to check */
	static ParseResult multiple(const onestring& in);

	/** Parser to check if initial character signals optional specifier.
	 * \param in onestring to check */
	static ParseResult optional(const onestring& in);

	/** Parser to check if initial character signals optional multiple
	 * specifier.
	 * \param in onestring to check */
	static ParseResult optional_multiple(const onestring& in);

	/** Literal parser ensures onestring only contains a single onechar.
	 * \param in onestring to check */
	static ParseResult literal(const onestring& in);

	/** Specifier parser ensures first character is a valid specifier.
	 * \param in onestring to check */
	static ParseResult specifier_parser(const onestring& in);

	/** Modifiers returns the modifiers matched, if any.
	 * Returns success if end of string found, and none matched.
	 * \param in onestring to check */
	static ParseResult modifier(const onestring& in);

	/** Digit parser returns digits matched, if any.
	 * \param in onestring to check */
	static ParseResult digit_parser(const onestring& in);

	/** Operator parser returns math operators matched, if any.
	 * \param in onestring to check */
	static ParseResult operator_parser(const onestring& in);

	/** Alphanumeric parser returns alphanumeric characters matched, if any.
	 * \param in onestring to check */
	static ParseResult alphanumeric_parser(const onestring& in);

	/**High-level parser for Unit parsing*/
	static ParseResult unit(const onestring&);

	/** Helper function to safely chop head off a onestring in place.
	 * \param onestring to remove first character from
	 */
	static void chop(onestring&);

	/** Friend classes for testing purposes only*/
	friend class TestCharacterParser;
	friend class TestLiteralParser;
	friend class TestSpecifierParser;
	friend class TestModifierParser;
	friend class TestDigitsParser;
	friend class TestOperatorParser;
	friend class TestAlphanumericParser;
	friend class TestEscapeParser;
	friend class TestMultiCharacterSpecifier;
};

std::ostream& operator<<(std::ostream& s, const UnitType& r);

#endif  // !SIMPLEXPRESS_UNITPARSER_HPP