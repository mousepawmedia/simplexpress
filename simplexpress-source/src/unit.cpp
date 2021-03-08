#include "simplexpress/unit.hpp"

#include "simplexpress/rules.hpp"
#include "simplexpress/simplex.hpp"

// UnitAttributes

UnitAttributes::UnitAttributes()
: optional(false), multiple(false), snag(false), negated(false), matcher('\0'),
  type(UnitType::Literal)
{
}

UnitAttributes::UnitAttributes(bool optional,
							   bool multiple,
							   bool snag,
							   bool negated,
							   onestring match,
							   UnitType type)
: optional(optional), multiple(multiple), snag(snag), negated(negated),
  matcher(match), type(type)
{
}

UnitAttributes::UnitAttributes(const UnitAttributes& attr)
: optional(attr.optional), multiple(attr.multiple), snag(attr.snag),
  negated(attr.negated), matcher(attr.matcher), type(attr.type)
{
}

UnitAttributes::UnitAttributes(UnitAttributes&& attr)
: optional(attr.optional), multiple(attr.multiple), snag(attr.snag),
  negated(attr.negated), matcher(attr.matcher), type(attr.type)
{
}

UnitAttributes& UnitAttributes::operator=(const UnitAttributes& attr)
{
	optional = attr.optional;
	multiple = attr.multiple;
	snag = attr.snag;
	negated = attr.negated;
	matcher = attr.matcher;
	type = attr.type;
	return *this;
}

std::ostream& operator<<(std::ostream& s, const UnitType& r)
{
	switch (r) {
		case UnitType::Literal:
			s << "literal";
			break;
		case UnitType::Specifier:
			s << "specifier";
			break;
	}
	return s;
}

Unit::Unit(UnitAttributes attr) : attr(attr) {}

Unit::Unit() {}

Unit::Unit(const Unit& unit) : attr(unit.attr) {}

bool Unit::specifiers(onechar ch) const
{
	bool return_var = false;
	Rule::LetterCase specifier_case;

	/* Determine specifier to match. */
	Specifier::SpecifierType specifier =
		Specifier::to_specifier_type(attr.matcher.at(0));

	/* Determine case, if specified.*/
	if (attr.matcher.length() >= 2) {
		specifier_case = Rule::to_letter_case(attr.matcher.at(1));
	} else {
		specifier_case = Rule::LetterCase::Any;
	}

	/* Check input against selected specifier rule. */
	switch (specifier) {
		case Specifier::SpecifierType::Alphanumeric:
			return_var = Rule::rule_a(ch, specifier_case);
			break;
		case Specifier::SpecifierType::Digit:
			return_var = Rule::rule_d(ch);
			break;
		case Specifier::SpecifierType::LatinLetter:
			return_var = Rule::rule_l(ch, specifier_case);
			break;
		case Specifier::SpecifierType::Newline:
			return_var = Rule::rule_n(ch);
			break;
		case Specifier::SpecifierType::MathOperator:
			return_var = Rule::rule_o(ch);
			break;
		case Specifier::SpecifierType::Punctuation:
			return_var = Rule::rule_p(ch);
			break;
		case Specifier::SpecifierType::CarriageReturn:
			return_var = Rule::rule_r(ch);
			break;
		case Specifier::SpecifierType::Space:
			return_var = Rule::rule_s(ch);
			break;
		case Specifier::SpecifierType::Tab:
			return_var = Rule::rule_t(ch);
			break;
		case Specifier::SpecifierType::Whitespace:
			return_var = Rule::rule_w(ch);
			break;
		case Specifier::SpecifierType::Any:
			return_var = Rule::rule_z(ch);
			break;
		default:
			channel << IOCat::debug << "Invalid specifier.\n" << IOCtrl::endl;
			break;
	}
	return return_var;
}

bool Unit::literals(onechar ch) const
{
	// Match Unicode character exactly.
	return ch == attr.matcher.at(0);
}

bool Unit::literal_sets(onechar ch)
{
	// FIXME: Temporarily ignore unused parameter.
	(void)ch;
	bool return_var = false;
	return return_var;
}

bool Unit::model_matches(onechar ch) const
{
	bool return_var = false;
	if (attr.type == UnitType::Specifier) {
		// Run if this unit is a specifier.
		return_var = specifiers(ch);
		// TODO: UnitType and logic for sets and literal sets
	} else {
		// Otherwise run as a literal.
		return_var = literals(ch);
	}
	return return_var;
}

int Unit::check_model(onestring parsestring) const
{
	// Negated handler
	if (attr.negated) {
		// Negative, optional, and multiple
		if (attr.optional && attr.multiple) {
			// Iterate until failure. If empty, pass.
			int ret = 0;
			for (size_t i = 0; i < parsestring.length(); ++i) {
				if (!model_matches(parsestring.at(i))) {
					ret += 1;
				} else {
					break;
				}
			}
			return ret;
		}
		// Negative optional
		else if (attr.optional) {
			// Check for a match. If empty or no (negative) matches, pass.
			if (!model_matches(parsestring.at(0))) {
				return single_character_match;
			} else {
				return no_optional_match;
			}
		}
		// Negative multiple
		else if (attr.multiple) {
			// If no matches, fail match.
			if (model_matches(parsestring.at(0))) {
				return no_required_match;
			}
			// Otherwise, iterate until failure.
			int ret = 0;
			for (size_t i = 0; i < parsestring.length(); ++i) {
				if (!model_matches(parsestring.at(i))) {
					ret += 1;
				} else {
					break;
				}
			}
			return ret;
		}
		// Only Negative
		if (model_matches(parsestring.at(0))) {
			return no_required_match;
		} else {
			return single_character_match;
		}
	}

	// Optional and multiple
	else if (attr.optional && attr.multiple) {
		// Iterate until failure. If empty, pass.
		int ret = 0;
		for (size_t i = 0; i < parsestring.length(); ++i) {
			if (model_matches(parsestring.at(i))) {
				ret += 1;
			} else {
				break;
			}
		}
		return ret;
	}

	// Optional handler
	else if (attr.optional) {
		// Check for a match. If empty or no matches, pass.
		if (model_matches(parsestring.at(0))) {
			return single_character_match;
		} else {
			return no_optional_match;
		}
	}

	// Multiple handler
	else if (attr.multiple) {
		// If no matches, fail match.
		if (!model_matches(parsestring.at(0))) {
			return no_required_match;
		}
		// Otherwise, iterate until failure.
		int ret = 0;
		for (size_t i = 0; i < parsestring.length(); i++) {
			if (model_matches(parsestring.at(i))) {
				ret += 1;
			} else {
				break;
			}
		}
		return ret;
	}

	// Otherwise check single character
	else {
		if (model_matches(parsestring.at(0))) {
			return single_character_match;
		} else {
			return no_required_match;
		}
	}
}

onestring Unit::to_string() const
{
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<<(std::ostream& stream, const Unit& unit)
{
	stream << "Unit<" << unit.attr.type << ">::(" << unit.attr.matcher << ")::("
		   << (unit.attr.optional ? "?" : "") << (unit.attr.multiple ? "+" : "")
		   << (unit.attr.snag ? "~" : "") << (unit.attr.negated ? "!" : "")
		   << ")";
	return stream;
}