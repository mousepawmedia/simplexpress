/** Unit [SIMPLEXpress]
 * Version: 0.1
 *
 * Author: Anna R. Dunster, Ben D. Lovy, Jarek Thomas
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

#ifndef SIMPLEXPRESS_UNIT_HPP
#define SIMPLEXPRESS_UNIT_HPP

#include <iostream>

#include "iosqueak/channel.hpp"
#include "onestring/onechar.hpp"
#include "onestring/onestring.hpp"
#include "simplexpress/rules.hpp"
#include "simplexpress/specifier.hpp"

/** The various categories of unit currently implemented. */
// TODO: Set, Group
enum class UnitType { Literal, Specifier };

/** The set of attributes and modifiers that can apply to a Unit. */
class UnitAttributes
{
public:
	/** Check flags:
	 * ? for optional
	 * + for multiple
	 * * for both optional and multiple*/
	bool optional;
	bool multiple;

	/** ~ for snag group*/
	bool snag;

	/** Is ! flag set*/
	bool negated;

	/** Which specifier is being matched, or which literal*/
	onestring matcher;

	/** Type of unit*/
	UnitType type;

	/** Default constructor*/
	UnitAttributes();

	/** Full constructor
	 * \param optional bool flag
	 * \param multiple bool flag
	 * \param snag bool flag
	 * \param negator bool flag
	 * \param match onestring for either the specifier or the literal
	 * \param type UnitType
	 */
	UnitAttributes(bool optional,
				   bool multiple,
				   bool snag,
				   bool negator,
				   onestring matcher,
				   UnitType type);

	/** Copy constructor
	 * \param Struct to copy
	 */
	UnitAttributes(const UnitAttributes&);

	/** Move constructor
	 * \param Struct to move
	 */
	UnitAttributes(UnitAttributes&&);

	/** Assignment overload*/
	UnitAttributes& operator=(const UnitAttributes&);
};

/** The Unit class is where we check against the model. Depending on what is
 * put in to check against, the model determines what function is called. It is
 * possible to have all types within one model.*/
class Unit
{
public:
	/** Attributes created in Unit construction by the Unit Parser class. These
	 * are the actual model information used by Simplex to check input. */
	UnitAttributes attr;

	/** Explicit constructor*/
	explicit Unit(UnitAttributes);

	/** Default constructor for empty Unit */
	Unit();

	/** Copy constructor */
	Unit(const Unit& unit);

	/** Copy assignment */
	Unit& operator=(const Unit& unit);

	/** Enum used by check model to indicate match status.
	 * Also used by parser and generosity in Simplex.
	 * Number values greater than 1 indicate a multi character match on a Unit
	 * with the multiple attribute. */
	enum match_status {
		no_required_match = -1,
		no_optional_match = 0,
		single_character_match = 1
	};

	/** Checks current onechar against model for match.
	 * \param onechar that is being checked */
	bool model_matches(onechar) const;

	/** Checks matcher and current onechar against specifier list, returns true
	 * if match exists
	 * \param onechar: the actual unicode to check against the specifiers.*/
	bool specifiers(onechar) const;

	/** Simplex set calls specifiers func, but returns true on the first
	 * specifier found to be true within the set.
	 * \param onechar: the unicode we are checking in the set.*/
	bool sets(onechar ch);

	/** Literal sets, Input against the model has to match exactly what is
	 * inside the literal set.
	 * \param onestring: the onestring we are checking for a literal match */
	bool literal_sets(onechar ch);

	/** Literals, Everything entered outside a unit. These are taken as they
	 * are and what user is checking against them has to match literal exactly.
	 * \param onechar that we are checking for a literal match exactly.*/
	bool literals(onechar ch) const;

	/** Used by Simplex class to generate match boolean.
	 * \param onestring that we are checking against the model.
	 * \return number of characters that match the current Unit in the model,
	 *         0 for no matches on an optional Unit, or -1 for no matches on a
	 *         non-optional Unit*/
	[[nodiscard]] int check_model(onestring) const;

	/** Convert to string for testing*/
	onestring to_string() const;
	friend std::ostream& operator<<(std::ostream&, const Unit&);
};

#endif  // Unit_H_
