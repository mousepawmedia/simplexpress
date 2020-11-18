/** Unit [SIMPLEXpress]
  * Version: 0.1
  *
  * Last Updated: 06 November 2020
  * Author: Ben D. Lovy, Jarek Thomas, Anna R. Dunster
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

#ifndef SIMPLEXPRESS_UNIT_HPP
#define SIMPLEXPRESS_UNIT_HPP

#include <iostream>

#include "pawlib/onechar.hpp"
#include "pawlib/onestring.hpp"

#include "simplexpress/rules.hpp"
#include "simplexpress/specifier.hpp"

/**The various categories of unit currently implemented. */
// TODO: Set, Group
enum class UnitType
{
	Literal,
	Specifier
};

/**The set of attributes and modifiers that can apply to a Unit. */
class UnitAttributes
{
public:
	/**Check flags:
	 * ? for optional
	 * + for multiple
	 * * for both optional and multiple*/
	bool optional;
	bool multiple;

	/**Is ! flag set*/
	bool negated;

	/**Which specifier is being matched, or which literal*/
	onechar matcher;

	/**Type of unit*/
	UnitType type;

	/**Default constructor*/
	UnitAttributes();

	/**Full constructor
	 * \param optional flag
	 * \param multiple flag
	 * \param negator flag
	 * \param onechar for either the specifier or the literal
	 */
	UnitAttributes(bool, bool, bool, onechar, UnitType);

	/**Copy constructor
	 * \param Struct to copy
	 */
	UnitAttributes(const UnitAttributes&);

	/**Move constructor\
	 * \param Struct to move
	 */
	UnitAttributes(UnitAttributes&&);

	/**Assignment overload*/
	UnitAttributes& operator=(const UnitAttributes&);
};

/**The Unit class is where we check against the model. Depending on what is 
 * put in to check against, the model determines what function is called. It is 
 * possible to have all types within one model.*/
class Unit
{
protected:
	UnitAttributes attr;
public:
	/**Used for the purpose of parsing through the model. Is set in 
	 * constructor. Includes an identifier if present, followed by a case 
	 * if present. */
	onestring model;

	/**Explicit constructor*/
	explicit Unit(UnitAttributes);

	/**Keep track of where we are in the model. */
	int model_index = 0;

	/**Checks current onechar against model for match.
	 * \param onechar that is being checked */
	bool model_matches(onechar);

	/**Checks matcher and current onechar against specifier list, returns true 
	 * if match exists
	 * \param onechar: the actual unicode to check against the specifiers.*/
	bool specifiers(onechar);

	/**Simplex set calls specifiers func, but returns true on the first 
	 * specifier found to be true within the set.
	 * \param onechar: the unicode we are checking in the set.*/
	bool sets(onechar ch);

	/**Literal sets, Input against the model has to match exactly what is 
	 * inside the literal set.
	 * \param onestring: the onestring we are checking for a literal match */
	bool literal_sets(onechar ch);

	/**Literals, Everything entered outside a unit. These are taken as they 
	 * are and what user is checking against them has to match literal exactly.
	 * \param onechar that we are checking for a literal match exactly.*/
	bool literals(onechar ch);

	/**Used by Simplex class to generate match boolean.
	 * Checks and returns number of characters matched or -1.
	 * \param onestring that we are checking against the model.*/
	int check_model(onestring);

	/**Convert to string for testing*/
	onestring to_string() const;
	friend std::ostream& operator<<(std::ostream&, const Unit&);
};

#endif // Unit_H_
