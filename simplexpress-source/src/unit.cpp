#include "simplexpress/unit.hpp"
#include "simplexpress/rules.hpp"
#include "simplexpress/simplex.hpp"

// UnitAttributes

UnitAttributes::UnitAttributes()
: optional(false),
  multiple(false),
  negated(false),
  matcher('\0'),
  type(UnitType::Literal)
{}

UnitAttributes::UnitAttributes(bool o, bool m, bool n, onechar match, UnitType t)
: optional(o),
  multiple(m),
  negated(n),
  matcher(match),
  type(t)
{}

UnitAttributes::UnitAttributes(const UnitAttributes& attr)
: optional(attr.optional),
  multiple(attr.multiple),
  negated(attr.negated),
  matcher(attr.matcher),
  type(attr.type)
{}

UnitAttributes::UnitAttributes(UnitAttributes&& attr)
: optional(attr.optional),
  multiple(attr.multiple),
  negated(attr.negated),
  matcher(attr.matcher),
  type(attr.type)
{}

UnitAttributes& UnitAttributes::operator=(const UnitAttributes& a)
{
	optional = a.optional;
	multiple = a.multiple;
	negated = a.negated;
	matcher = a.matcher;
	type = a.type;
	return *this;
}

std::ostream& operator<<(std::ostream& s, const UnitType& r)
{
	switch (r)
	{
		case UnitType::Literal:
			s << "literal";
			break;
		case UnitType::Specifier:
			s << "specifier";
			break;
	}
	return s;
}

Unit::Unit(UnitAttributes a) : attr(a) {}

/*for now these just return false till a later time*/
bool Unit::specifiers(onechar ch)
{
	//Variable that we return
	bool return_var = false;

	/*Which case we are going to be looking for.*/
	Rule::LetterCase sCase = Rule::to_letter_case(model.at(2).c_str()[0]);

	/* Determine specifier */
	Specifier::SpecifierType specifier = Specifier::to_specifier_type(model.at(1).c_str()[0]);

	switch(specifier)
	{
		case Specifier::SpecifierType::Alphanumeric:
			return_var = rule.rule_a(ch, sCase);
			break;
		case Specifier::SpecifierType::Digit:
			return_var = rule.rule_d(ch);
			break;
		case Specifier::SpecifierType::LatinLetter:
			return_var = rule.rule_l(ch, sCase);
			break;
		case Specifier::SpecifierType::Math:
			return_var = false;
			break;
		case Specifier::SpecifierType::Newline:
			return_var = rule.rule_n(ch);
			break;
		case Specifier::SpecifierType::MathOperator:
			return_var = rule.rule_o(ch);
			break;
		case Specifier::SpecifierType::Punctuation:
			return_var = rule.rule_p(ch);
			break;
		case Specifier::SpecifierType::CarriageReturn:
			return_var = rule.rule_r(ch);
			break;
		case Specifier::SpecifierType::Space:
			return_var = rule.rule_s(ch);
			break;
		case Specifier::SpecifierType::Tab:
			return_var = rule.rule_t(ch);
			break;
		case Specifier::SpecifierType::Whitespace:
			return_var = rule.rule_w(ch);
			break;
		case Specifier::SpecifierType::Any:
			return_var = true;
			break;
		default:
			std::cout << "Invalid specifier.\n";
			break;
	}
	return return_var;
}

bool Unit::literals(onechar ch)
{
	/*has to match Unicode character exactly
	otherwise its false*/
	return ch == model[0];
}

bool Unit::literal_sets(onechar ch)
{
	// FIXME: Temporarily ignore unused parameter.
	(void)ch;
	bool return_var = false;
	return return_var;
}

bool Unit::type_choice(onechar ch)
{
	bool return_var = false;
	if(model[0] == '^')
	{
		// NOTE: This does not feel like the recommended way to switch on a onechar
		// FIXME: handle error of not having something after it
		switch(model.at(1).c_str()[0])
		{
		case '<':
			//literal_sets(ch);
			break;
		case '[':
			//sets(ch);
			break;
		default:
			return_var = specifiers(ch);
			break;
		}
	}
	else
	{
		return_var = literals(ch);
	}
	return return_var;
}

int Unit::check_model(onestring s)
{
	// Optional handler
	if (attr.optional)
	{
		if (s.empty())
			return 0;
		else
			return -1;
	}

	if (attr.multiple)
	{
			// iterate until failure
			int ret = 0;

			for (size_t i = 0; i < s.length(); i++)
			{
				if (type_choice(s.at(i)))
					ret += 1;
				else
					break;
			}

			return ret;
	}
	else
	{
		bool result = type_choice(s.at(0));
		if (result > 0)
			return 1;
		else
			return -1;
	}
	return -1;
}

onestring Unit::to_string() const
{
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<<(std::ostream& s, const Unit& u)
{
	s << "Unit<" << u.attr.type << ">::(" << u.attr.matcher << ")@"<< u.model_index;
	return s;
}