
#include "simplexpress/unit_parser.hpp"

// ParseResult

ParseResult::ParseResult(tril res, const onestring& str, const onestring& r)
: result(res), parsedstring(str), remainder(r)
{
}

ParseResult::ParseResult() : result(false), parsedstring(""), remainder("") {}

ParseResult ParseResult::make_success(const onestring& match,
									  const onestring& rem)
{
	return ParseResult(true, match, rem);
}

ParseResult ParseResult::make_error(const onestring& err, const onestring& rem)
{
	return ParseResult(false, err, rem);
}

template<typename F>
ParseResult ParseResult::parse(const onestring& rem, F parser)
{
	ParseResult ret = parser(rem);
	return ret;
}

onestring ParseResult::to_string() const
{
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

// ParsedAttributes
ParsedAttributes::ParsedAttributes(UnitAttributes attr, size_t size)
: attr(attr), size(size)
{
}

// UnitParser
UnitParser::UnitParser(onestring& in) : parsedstring(in) {}

UnitParser::ReservedCharacter UnitParser::to_reserved_character(onechar ch)
{
	if (ch == '+') {
		return ReservedCharacter::Multiple;
	} else if (ch == '!') {
		return ReservedCharacter::Negator;
	} else if (ch == '?') {
		return ReservedCharacter::Optional;
	} else if (ch == '*') {
		return ReservedCharacter::OptionalMultiple;
	} else if (ch == '^') {
		return ReservedCharacter::UnitMarker;
	} else if (ch == '~') {
		return ReservedCharacter::UnitSnag;
	} else if (ch == '/') {
		return ReservedCharacter::UnitEnd;
	} else if (ch == '%') {
		return ReservedCharacter::Escape;
	} else {
		return ReservedCharacter::Unrecognized;
	}
}

ParsedAttributes UnitParser::parse() const
{
	// Initialize attributes
	UnitAttributes ret = UnitAttributes();
	size_t ret_len = 0;
	onestring remainder = parsedstring;

	/** Before entering the loop, first check if character is escaped, and if
	 * not, then check if we are opening a unit or snag unit */
	bool escaped = (ParseResult::parse(remainder, escape).result);
	bool unit = false;

	if (escaped) {
		remainder = ParseResult::parse(remainder, escape).remainder;
		++ret_len;
	} else {
		ParseResult check_unit_open =
			ParseResult::parse(remainder, unit_marker);
		ParseResult check_unit_snag = ParseResult::parse(remainder, unit_snag);

		unit = (check_unit_open.result || check_unit_snag.result);
		if (check_unit_open.result) {
			remainder = check_unit_open.remainder;
		} else if (check_unit_snag.result) {
			remainder = check_unit_snag.remainder;
			ret.snag = true;
		}
	}

	if (unit && !escaped) {
		// We found a Unit
		// Add the open unit character to the matched count
		++ret_len;

		// First - is it negated?
		ParseResult check_negated = ParseResult::parse(remainder, negator);
		remainder = check_negated.remainder;
		if (check_negated.result) {
			ret.negated = true;
			++ret_len;
		}

		// Check whether it's escaped to a literal Unit.
		ParseResult check_escape = ParseResult::parse(remainder, escape);
		remainder = check_escape.remainder;
		if (check_escape.result) {
			ret.type = UnitType::Literal;
			++ret_len;
			// Capture and store literal for model matcher.
			ParseResult lit = ParseResult::parse(remainder, literal);
			remainder = lit.remainder;
			if (lit.result) {
				ret.matcher = lit.parsedstring;
				// A literal matcher is always one character long.
				++ret_len;
			}
		}

		// Is it a group?
		// TODO not yet implemented

		// Is it a set?
		// TODO not yet implemented. See T940, T941

		// If it's not literal, verify that it's a valid specifier.
		if (!check_escape.result) {
			ret.type = UnitType::Specifier;
			ParseResult check_specifier =
				ParseResult::parse(remainder, specifier_parser);
			remainder = check_specifier.remainder;
			if (!check_specifier.result) {
				// FIXME: parse error!! - this whole thing should return a
				// ParseResult<T>!!
			}
			// Store the specifier
			ret.matcher = check_specifier.parsedstring;
			ret_len += check_specifier.parsedstring.length();
		}

		// Check for modifier and store result, if any.
		ParseResult check_modifier = ParseResult::parse(remainder, modifier);
		remainder = check_modifier.remainder;

		if (!check_modifier.parsedstring.empty()) {
			onechar mod = check_modifier.parsedstring.at(0);
			if (mod == '+') {
				ret.multiple = true;
				++ret_len;
			} else if (mod == '?') {
				ret.optional = true;
				++ret_len;
			} else if (mod == '*') {
				ret.optional = true;
				ret.multiple = true;
				++ret_len;
			}
		}

		// Verify end of unit
		ParseResult check_end = ParseResult::parse(remainder, unit_end);
		remainder = check_end.remainder;
		if (!check_end.result) {
			// FIXME parse error!!
		}
		++ret_len;
	} else {
		// If it isn't a Unit, match as a literal.
		ret.type = UnitType::Literal;

		// Store literal
		ParseResult lit = ParseResult::parse(remainder, literal);
		remainder = lit.remainder;
		if (lit.result) {
			ret.matcher = lit.parsedstring;
			// A literal matcher is always one character long.
			++ret_len;
		}
	}
	return ParsedAttributes(ret, ret_len);
}

void UnitParser::parse_model(const onestring& user_model,
							 FlexArray<Unit*>& model_array)
{
	onestring remainder = user_model;
	// Loop through model input calling the unit parser, removing processed
	// characters with each iteration
	while (!remainder.empty()) {
		ParsedAttributes parsedattr = UnitParser(remainder).parse();
		model_array.push_back(new Unit(parsedattr.attr));
		if (remainder.length() - parsedattr.size <= 0) {
			return;
		}
		onestring new_rem =
			remainder.substr(parsedattr.size, remainder.length());
		remainder = new_rem;
	}
	// If user model was empty, to begin with, do nothing - empty simplex
}

// Parser: Reserved Character
ParseResult UnitParser::character(ReservedCharacter rc, onestring in)
{
	// if empty, no match
	if (in.empty()) {
		return ParseResult::make_error("Out of input", "");
	} else {
		onechar char_to_match = in.at(0);
		ReservedCharacter parsed = to_reserved_character(char_to_match);
		if (parsed == rc) {
			// Success!
			onestring rem = (in.length() > 1) ? in.substr(1, in.length()) : "";
			return ParseResult::make_success(onestring(char_to_match), rem);
		} else {
			// No match
			onestring msg = onestring("Invalid Reserved Character");
			return ParseResult::make_error(msg, in);
		}
	}
}

// Parser: Open unit
ParseResult UnitParser::unit_marker(const onestring& in)
{
	return character(ReservedCharacter::UnitMarker, in);
}

// Parser: Open snag unit
ParseResult UnitParser::unit_snag(const onestring& in)
{
	return character(ReservedCharacter::UnitSnag, in);
}

// Parser: Close unit
ParseResult UnitParser::unit_end(const onestring& in)
{
	return character(ReservedCharacter::UnitEnd, in);
}

// Parser: Escape
ParseResult UnitParser::escape(const onestring& in)
{
	return character(ReservedCharacter::Escape, in);
}

// Parser: Negator
ParseResult UnitParser::negator(const onestring& in)
{
	return character(ReservedCharacter::Negator, in);
}

// Parser: Multiple
ParseResult UnitParser::multiple(const onestring& in)
{
	return character(ReservedCharacter::Multiple, in);
}

// Parser: Optional
ParseResult UnitParser::optional(const onestring& in)
{
	return character(ReservedCharacter::Multiple, in);
}

// Parser: Optional Multiple
ParseResult UnitParser::optional_multiple(const onestring& in)
{
	return character(ReservedCharacter::OptionalMultiple, in);
}

// Parser: Literal
ParseResult UnitParser::literal(const onestring& in)
{
	// Matches the first character, whatever it is.  Fails if no input present
	if (in.length() == 0)
		return ParseResult::make_error("Out of input!", "");
	else {
		// Success
		onestring rem = (in.length() > 1) ? in.substr(1, in.length()) : "";
		return ParseResult::make_success(in.at(0), rem);
	}
}

// Parser: Specifier
ParseResult UnitParser::specifier_parser(const onestring& in)
{
	onestring remainder = in;
	if (remainder.length() < 1) {
		return ParseResult::make_error("Out of input", "");
	}

	// Init return value
	onestring lhs = "";
	// Is it a real specifier?
	// first char of input
	Specifier::SpecifierType lead =
		Specifier::to_specifier_type(remainder.at(0));

	if (lead != Specifier::SpecifierType::Unsupported) {
		chop(remainder);
		lhs.append(static_cast<char>(lead));
	} else {
		onestring msg = "Unknown specifier!";
		return ParseResult::make_error(msg, remainder);
	}
	// If it is, does it then have a case following?  Upper/lower?
	if (remainder.length() > 0) {
		Rule::LetterCase case_modifier = Rule::to_letter_case(remainder.at(0));
		if (case_modifier != Rule::LetterCase::Any) {
			chop(remainder);
			lhs.append(static_cast<char>(case_modifier));
		} else {
			// If it's neither, ignore it as not part of this parse operation
		}
	}
	return ParseResult::make_success(lhs, remainder);
}

// Parser: Modifiers
ParseResult UnitParser::modifier(const onestring& in)
{
	onestring remainder = in;
	size_t len = remainder.length();
	if (len == 0)
		return ParseResult::make_success("", "");
	else {
		// Init return value
		onestring lhs = "";

		// Is it a real modifier?
		// NOTE a real parser combinator solution would be able
		// to combine, e.g. character('+') and character('*').  Maybe someday?

		// first char of input
		onechar lead = remainder.at(0);
		ReservedCharacter rc = to_reserved_character(lead);

		if (rc == ReservedCharacter::OptionalMultiple ||
			rc == ReservedCharacter::Multiple ||
			rc == ReservedCharacter::Optional) {
			chop(remainder);
			lhs.append(lead);
		} else {
			onestring msg = "Invalid modifier: ";
			msg.append(lead);
			return ParseResult::make_error(msg, remainder);
		}

		return ParseResult::make_success(lhs, remainder);
	}
}

// Parser: Digits
ParseResult UnitParser::digit_parser(const onestring& in)
{
	// If no input, then there are no digits.
	if (in.length() == 0) {
		return ParseResult::make_error("Out of input", "");
	}

	onestring remainder = in;
	onestring lhs = "";

	/** Check characters one at a time until one is not a digit. If it's a
	 * digit, we store it in the left side as a result and remove
	 * it from the remaining input to check. If it's not a digit, and we
	 * have a result, then we return the digits, and whatever after that
	 * isn't a digit. If it's not a digit, and nothing has been stored as a
	 * result, then no digits were found and parsing digits failed.
	 */

	while (remainder.length() > 0) {
		if (Rule::rule_d(remainder.at(0))) {
			lhs.append(remainder.at(0));
			chop(remainder);
		} else if (!Rule::rule_d(remainder.at(0)) && lhs.length() > 0) {
			return ParseResult::make_success(lhs, remainder);
		} else if (!Rule::rule_d(remainder.at(0)) && lhs.length() == 0) {
			return ParseResult::make_error("No digits found", remainder);
		}
	}

	// If we run out of data to parse without encountering something that isn't
	// a digit, then we return success on the entire input.

	return ParseResult::make_success(lhs, remainder);
}

// Parser: Operators
ParseResult UnitParser::operator_parser(const onestring& in)
{
	// If no input, then there is no operator.
	if (in.length() == 0) {
		return ParseResult::make_error("Out of input", "");
	}

	onestring remainder = in;
	onestring lhs = "";

	// Check if first character of input is a math operator, and return success
	// with the parsed operator and remainder. Otherwise, return error.

	if (Rule::rule_o(remainder.at(0))) {
		lhs.append(remainder.at(0));
		chop(remainder);
		return ParseResult::make_success(lhs, remainder);
	} else {
		return ParseResult::make_error("Not a math operator", remainder);
	}
}

// Parser: Alphanumeric
ParseResult UnitParser::alphanumeric_parser(const onestring& in)
{
	// If no input, then there is no alphanumeric character.
	if (in.length() == 0) {
		return ParseResult::make_error("Out of input", "");
	}

	onestring remainder = in;
	onestring lhs = "";

	/** Check characters one at a time until one is not an alphanumeric
	 * character. If it is, we store it in the left side as a result and remove
	 * it from the remaining input to check. If it's not, and we have a result,
	 * then we return the matched characters, and whatever after that that isn't
	 * matched. If it's not an alphanumeric character, and nothing has been
	 * stored as a result, then no matches were found and parsing alphanumeric
	 * characters failed.
	 */

	while (remainder.length() > 0) {
		if (Rule::rule_a(remainder.at(0))) {
			lhs.append(remainder.at(0));
			chop(remainder);
		} else if (!Rule::rule_a(remainder.at(0)) && lhs.length() > 0) {
			return ParseResult::make_success(lhs, remainder);
		} else if (!Rule::rule_a(remainder.at(0)) && lhs.length() == 0) {
			return ParseResult::make_error("No alphanumeric characters found",
										   remainder);
		}
	}

	// If we run out of data to parse without encountering something that isn't
	// an alphanumeric character, then we return success on the entire input.

	return ParseResult::make_success(lhs, remainder);
}

// Helper Functions
void UnitParser::chop(onestring& in)
{
	if (in.length() > 1) {
		onestring new_rem = in.substr(1, in.length());
		in = new_rem;
	} else if (in.length() == 1) {
		in = in.at(0);
	} else {
		in = "";
	}
}

std::ostream& operator<<(std::ostream& parsedstring, const ParseResult& r)
{
	parsedstring << ((static_cast<bool>(r.result)) ? "Ok" : "Err");
	parsedstring << '(' << r.parsedstring << ", " << r.remainder << ')';
	return parsedstring;
}