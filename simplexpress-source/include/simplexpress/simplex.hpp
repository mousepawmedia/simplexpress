/** Simplex [SIMPLEXpress]
 * Version: 0.1
 *
 * Authors: Wilfrantz Dede, Anna R. Dunster, Muhammad Adeel Hussain,
 *          Ben D. Lovy, Jarek Thomas
 *
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

#ifndef SIMPLEXPRESS_SIMPLEX_HPP
#define SIMPLEXPRESS_SIMPLEX_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "pawlib/flex_array.hpp"
#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"
#include "simplexpress/unit.hpp"
#include "simplexpress/unit_parser.hpp"

/** Holds parser results for use by match and snag functions
 */
struct SimplexResult {
	// Default initialization to true, parser will set false as needed.
	SimplexResult(): match(true) {}
	bool match;
	FlexArray<onestring> snag_array;
};

/**The simplex class is the overall model of Simplexpress. A simplex contains an
 * array of Units. Everything entered outside a Unit is taken as a literal and
 * must be matched exactly.*/
class Simplex
{
protected:
	/**The model itself, an array of Unit objects.*/
	FlexArray<Unit*> model;

	/**Used to keep track of whether we are in a unit or not. If we encounter
	 * a `^` then we add 1 and if we encounter a `/` then we subtract 1. If
	 * we try to go below 0 then an error is thrown as there is nothing
	 * to escape.*/
	uint16_t unit_counter = 0;

public:
	/** Constructor, When a Simplex is created, parse_input is called to parse
	 * through the user defined model. Then it will call match to check
	 * everything against the model.
	 * \param user_model onestring user definition of model*/
	explicit Simplex(const onestring& user_model);

	/** Overload of constructor to take a string of chars to build a model
	 * instead of a onestring variable.
	 * \param user_model char* model_check */
	explicit Simplex(const char* user_model);

	/** Internal static function to generate matches and snag results from input
	 * model using variables passed from match and snag functions
	 * \param model_check onestring user input to check
	 * \param model_array FlexArray of Units that is the model to check
	 * \return result SimplexResult including a boolean "match" for match
	 *         function and FlexArray "snag_array" of onestring matches in order
	 *         of snag units, or empty array if match is false.*/
	SimplexResult static simplex_parser(const onestring& model_check,
										FlexArray<Unit*>& model_array);

	/** Takes the model defined when creating the Simplex, and matches user
	 * input against it.
	 * \param model_check user input to check
	 * \return true if input is an exact match for expression in object model*/
	bool match(const onestring& model_check);

	/** Overload of member match function, matches char* user input instead of
	 * onestring.
	 * \param model_check user input to check
	 * \return true if input is an exact match for expression in object model*/
	bool match(const char* model_check);

	/** Static version to use with an input model rather than repeat use object.
	 * This is the final call of all two parameter overloads of match.
	 * \param model_check onestring user input to check
	 * \param input_model onestring model to check against
	 * \return true if input is an exact match for expression in input model*/
	bool static match(const onestring& model_check,
					  const onestring& input_model);

	/** Static match conversion overloads from various string literals.
	 * \param model_check user input to check
	 * \param input_model model to check against
	 * \return true if input is an exact match for expression in input model*/
	bool static match(const char* model_check, const onestring& input_model);
	bool static match(const onestring& model_check, const char* input_model);
	bool static match(const char* model_check, const char* input_model);

	/** Takes the model defined when creating the Simplex, and runs user input
	 * to snag against it.
	 * \param snag_check onestring user input to check
	 * \return FlexArray of onestring matches in order of snag units, or empty
	 *         array if match is false.*/
	FlexArray<onestring> snag(const onestring& snag_check);

	/** Overload of member snag function, runs char* user input instead of
	 * onestring.
	 * \param snag_check onestring user input to check
	 * \return FlexArray of onestring matches in order of snag units, or empty
	 *         array if match is false.*/
	FlexArray<onestring> snag(const char* snag_check);

	/** Static version of snag to use with an input model rather than repeat use
	 * object.
	 * This is the final call of all two parameter overloads of snag.
	 * \param snag_check onestring user input to check
	 * \param input_model onestring model to check against
	 * \return FlexArray of onestring matches in order of snag units, or empty
	 *         array if input does not entirely match model.*/
	FlexArray<onestring> static snag(const onestring& snag_check,
									 const onestring& input_model);

	/** Static snag conversion overloads from various string literals.
	 * \param snag_check user input to check
	 * \param input_model model to check against
	 * \return FlexArray of onestring matches in order of snag units, or empty
	 *         array if input does not entirely match model.*/
	FlexArray<onestring> static snag(const char* model_check,
									 const onestring& input_model);
	FlexArray<onestring> static snag(const onestring& model_check,
									 const char* input_model);
	FlexArray<onestring> static snag(const char* model_check,
									 const char* input_model);

	/**Convert to string for testing*/
	onestring to_string() const;
	friend std::ostream& operator<<(std::ostream&, const Simplex&);
};

// Helper functions

/** Parses through the user defined model to generate Unit array.
 * Uses enumeration to pull out each type of model we can have.
 * \param user_model onestring user definition of model
 * \param model_array array to contain the Units.*/
void parse_model(const onestring&, FlexArray<Unit*>&);

/** Checks whether there are additional Units in the model.
 * \param model_index int the current index
 * \param model_array the Unit array
 * \return true if additional Units present, false if last Unit in model*/
bool next(const unsigned int& model_index, const FlexArray<Unit*>& model_array);

/** Checks if all additional Units in model are optional, in case no matches
 * are present for optional Units on the end of a model.
 * \param model_index int the current index
 * \param model_array the Unit array
 * \return false if any non-optional Units exist in remainder of model*/
bool check_optional(const unsigned int& model_index,
					const FlexArray<Unit*>& model_array);

/** Used by match() and snag() to not be too greedy
 * \param buffer onestring to digest
 * \param total_matched int of possible matches
 * \param starting_index int of starting index in model
 * \param model_array array of Units, the working model
 * \return number of matches to consume without invalidating later Units*/
int generosity(const onestring buffer,
			   const int total_matched,
			   const int starting_index,
			   const FlexArray<Unit*>& model_array);

#endif
