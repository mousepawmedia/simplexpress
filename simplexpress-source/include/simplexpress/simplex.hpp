/** Simplex [SIMPLEXpress]
  * Version: 0.1
  *
  * Last Updated: 18 November 2020
  * Author: Ben D. Lovy, Jarek Thomas, Anna R. Dunster, Wilfrantz Dede 
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

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"

#include "simplexpress/unit.hpp"
#include "simplexpress/unit_parser.hpp"


/**The simplex class is the overall model of Simplexpress. A simplex contains 
 * a vector (for now) of Units. Everything entered outside a Unit is taken as a 
 * literal and must be matched exactly.*/
class Simplex
{
	/**Parser for a whole simplex - consists of zero or more Units*/
	static ParseResult simplex_parser(onestring);

protected:
	/**The model itself, an array of Unit objects.*/
	std::vector<Unit*> model;

	/**To keep track of where we are in the model.*/
	unsigned int model_index = 0;

	/**Enumeration to roughly determine how we are interpreting as we 
	 * parse through the model.*/
	enum parse_status
	{
		NORMAL = 0,
		IN_UNIT = 1,
		ESCAPED = 2,
		SPACE_CONVERT = 3
	};

	/**Used to keep track of whether we are in a unit or not. If we encounter 
	 * a `^` then we add 1 and if we encounter a `/` then we subtract 1. If 
	 * we try to go below 0 then an error is thrown as there is nothing 
	 * to escape.*/
	uint16_t unit_counter = 0;

	/**Parses through the user defined model.
	 * Uses enumeration to pull out each type of model we can have.
	 * \param user_model onestring user definition of model*/
	void parse_model(const onestring&);

	/**Moves to the next unit or literal in the model.*/
	bool next();

public:
	/**Constructor, When a Simplex is created, parse_input is called to parse 
	 * through the user defined model. Then it will call match to check 
	 * everything against the model.
	 * \param user_model onestring user definition of model*/
	explicit Simplex(const onestring&);

	/**Takes the user defined model and matches user input to parse against 
	 * the model.
	 * \param model_check onestring user input to check*/
	bool match(onestring);

	/**Convert to string for testing*/
	onestring to_string() const;
	friend std::ostream& operator<<(std::ostream&, const Simplex&);
};
#endif
