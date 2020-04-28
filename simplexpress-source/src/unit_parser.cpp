#include "simplexpress/specifier.hpp"
#include "simplexpress/unit_parser.hpp"

// ParseResult

ParseResult::ParseResult()
: result(false),
  s(""),
  remainder("")
{}

ParseResult::ParseResult(tril res, onestring str, onestring r)
: result(res),
  s(str),
  remainder(r)
{}

ParseResult ParseResult::make_success(onestring match, onestring rem)
{
	return ParseResult(true, match, rem);
}

ParseResult ParseResult::make_error(onestring err, onestring rem)
{
	return ParseResult(false, err, rem);
}

template <typename F>
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

std::ostream& operator<<(std::ostream& s, const ParseResult& r)
{
	s << ((static_cast<bool>(r.result)) ? "Ok" : "Err");
	s << '(' << r.s << ", " << r.remainder << ')';
	return s;
}

// UnitParser

UnitParser::UnitParser(onestring in) : s(in) {}

void UnitParser::chop(onestring& in)
{
	if (in.length() > 1)
	{
		onestring new_rem = in.substr(1, in.length());
		in = new_rem;
	}
	else if (in.length() == 1)
	{
		in = in.at(0);
	}
	else
	{
		in = "";
	}
}

UnitParser::ParsedAttributes::ParsedAttributes(UnitAttributes a, size_t s)
: attr(a), size(s) {}

UnitParser::ParsedAttributes UnitParser::parse() const
{
	// Init attributes

	UnitAttributes ret = UnitAttributes();
	size_t ret_len = 0;

	onestring remainder = s;
	// Before entering the loop, check if the whole thing is a unit or literal
	ParseResult check_unit_open = ParseResult::parse(remainder, unit_marker);
	remainder = check_unit_open.remainder;

	if (check_unit_open.result)
	{
		// we found a unit - KEEP THIS HERE
		ret.type = UnitType::Specifier;
		// Add the open unit character to the matched count
		++ret_len;

		// First - is it negated?
		ParseResult check_negated = ParseResult::parse(remainder, negator);
		remainder = check_negated.remainder;
		if (check_negated.result)
		{
			ret.negated = true;
			++ret_len;
		}

		// Is it a group?
		// TODO not yet implemented

		// Is it a set?
		// TODO not yet implemented

		// Is it a specifier?
		ParseResult check_specifier = ParseResult::parse(remainder, specifier_parser);
		remainder = check_specifier.remainder;
		if (!check_specifier.result)
		{
			// FIXME: parse error!! - this whole thing should return a ParseResult<T>!!
		}

		// Store it
		ret.matcher = *check_specifier.s.c_str();
		++ret_len;

		// Check modifier

		ParseResult check_modifier = ParseResult::parse(remainder, modifier);
		remainder = check_modifier.remainder;
		if (!check_modifier.result)
		{
			// FIXME: parse error!!
		}

		// store modifier, if any
		if (!check_modifier.s.empty())
		{
			onechar mod = check_modifier.s.at(0);
			if (mod == '+')
			{
				ret.multiple = true;
				++ret_len;
			}
			else if (mod == '?')
			{
				ret.optional = true;
				++ret_len;
			}
			else if (mod == '*')
			{
				ret.optional = true;
				ret.multiple = true;
				++ret_len;
			}
		}
		else
		{
			return UnitParser::ParsedAttributes(ret, ret_len);
		}

		// Check end of unit
		ParseResult check_end = ParseResult::parse(remainder, unit_marker);
		remainder = check_end.remainder;
		if (!check_end.result)
		{
			// FIXME parse error!!
		}
		++ret_len;

		return UnitParser::ParsedAttributes(ret, ret_len);
	}
	else
	{
		// It's a literal - KEEP THIS HERE
		ret.type = UnitType::Literal;

		// First - is it negated?
		ParseResult check_negated = ParseResult::parse(remainder, negator);
		remainder = check_negated.remainder;
		if (check_negated.result)
		{
			ret.negated = true;
			ret_len += check_negated.s.length();
		}

		// Store literal
		ParseResult lit = ParseResult::parse(remainder, literal);
		remainder = lit.remainder;
		if (lit.result)
		{
			ret.matcher = *lit.s.c_str();
			// A literal is always of length 1

			++ret_len;
		}
		else
		{
			// FIXME: parse error!
		}

		ParseResult check_modifier = ParseResult::parse(remainder, modifier);
		remainder = check_modifier.remainder;
		if (!check_modifier.result)
		{
			// FIXME: parse error!!
		}
		// store modifier, if any
		if (!check_modifier.s.empty())
		{
			onechar mod = check_modifier.s.at(0);
			if (mod == '+')
			{
				ret.multiple = true;
				++ret_len;
			}
			else if (mod == '?')
			{
				ret.optional = true;
				++ret_len;
			}
			else if (mod == '*')
			{
				ret.optional = true;
				ret.multiple = true;
				++ret_len;
			}
			else
			{
				// DO NOTHING
			}
		}
		return UnitParser::ParsedAttributes(ret, ret_len);
	}
}

ParseResult UnitParser::character(ReservedCharacter rc, onestring in)
{
	// if empty, no match
	if (in.empty())
	{
		return ParseResult::make_error("Out of input", "");
	}
	else
	{
		onechar char_to_match = in.at(0);
		ReservedCharacter parsed = to_reserved_character(char_to_match);
		if (parsed == rc)
		{
			// Success!
			onestring rem = (in.length() > 1) ? in.substr(1, in.length()) : "";
			return ParseResult::make_success(onestring(char_to_match), rem);
		}
		else
		{
			// No match
			onestring msg = onestring("Expecting ");
			msg.append(static_cast<char>(rc));
			msg += ", got ";
			msg.append(char_to_match);
			return ParseResult::make_error(msg, in);
		}
	}
}

UnitParser::ReservedCharacter UnitParser::to_reserved_character(onechar ch)
{
	if (ch == '+')
		return ReservedCharacter::Multiple;
	else if (ch == '!')
		return ReservedCharacter::Negator;
	else if (ch == '?')
		return ReservedCharacter::Optional;
	else if (ch == '*')
		return ReservedCharacter::OptionalMultiple;
	else if (ch == '/')
		return ReservedCharacter::UnitMarker;
	else
		return ReservedCharacter::Unrecognized;
}

// Open/close unit

ParseResult UnitParser::unit_marker(onestring in)
{
	return character(ReservedCharacter::UnitMarker, in);
}

// Negator

ParseResult UnitParser::negator(onestring in)
{
	return character(ReservedCharacter::Negator, in);
}

// Multiple

ParseResult UnitParser::multiple(onestring in)
{
	return character(ReservedCharacter::Multiple, in);
}

// Optional

ParseResult UnitParser::optional(onestring in)
{
	return character(ReservedCharacter::Multiple, in);
}

// Optional Multiple

ParseResult UnitParser::optional_multiple(onestring in)
{
	return character(ReservedCharacter::OptionalMultiple, in);
}

// Literal
ParseResult UnitParser::literal(onestring in)
{
	// Matches the first character, whatever it is.  Fails if no input present
	if (in.length() == 0)
		return ParseResult::make_error("Out of input!", "");
	else
	{
		// Success
		onestring rem = (in.length() > 1) ? in.substr(1, in.length()) : "";
		return ParseResult::make_success(in.at(0), rem);
	}
}

// Specifier
// NOTE: this is a prime example of why ParseResult<T> is what I want
// Stringly typed parse results will lead to code bloat and repeated logic
ParseResult UnitParser::specifier_parser(onestring in)
{
	onestring remainder = in;
	if (remainder.length() < 1)
	{
		return ParseResult::make_error("Out of input", "");
	}

	// Init return value
	onestring lhs = "";
	// Is it a real specifier?
	// first char of input
	Specifier::SpecifierType lead = Specifier::to_specifier_type(remainder.at(0));

	if (lead != Specifier::SpecifierType::Unsupported)
	{
		chop(remainder);
		lhs.append(static_cast<char>(lead));
	}
	else
	{
		onestring msg = "Unknown specifier!";
		return ParseResult::make_error(msg, remainder);
	}
	// If it is, does it then have a case following?  Upper/lower?
	if (remainder.length() > 0)
	{
		Rule::LetterCase case_modifier = Rule::to_letter_case(remainder.at(0));
		if (case_modifier != Rule::LetterCase::Any)
		{
			chop(remainder);
			lhs.append(static_cast<char>(case_modifier));
		}
		else
		{
			//If it's neither, ignore it as not part of this parse operation
		}
	}
	return ParseResult::make_success(lhs, remainder);
}

// Modifiers

ParseResult UnitParser::modifier(onestring in)
{
	onestring remainder = in;
	size_t len = remainder.length();
	if (len == 0)
		return ParseResult::make_success("", "");
	else
	{
		// Init return value
		onestring lhs = "";

		// Is it a real modifier?
		// NOTE a real parser combinator solution would be able
		// to combine, e.g. character('+') and character('*').  Maybe someday?

		// first char of input
		onechar lead = remainder.at(0);
		ReservedCharacter rc = to_reserved_character(lead);

		if (rc == ReservedCharacter::OptionalMultiple
			|| rc == ReservedCharacter::Multiple
			|| rc == ReservedCharacter::Optional)
		{
			chop(remainder);
			lhs.append(lead);
		}
		else
		{
			onestring msg = "Invalid modifier: ";
			msg.append(lead);
			return ParseResult::make_error(msg, remainder);
		}

		return ParseResult::make_success(lhs, remainder);
	}
}