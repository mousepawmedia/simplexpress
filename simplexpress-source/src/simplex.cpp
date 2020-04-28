#include "simplexpress/simplex.hpp"
#include "simplexpress/rules.hpp"

Simplex::Simplex(onestring user_model)
{
	parse_model(user_model);
}

bool Simplex::next()
{
	if(model_index+1 >= model.size())
	{
		return false;
	}
	else
	{
		++model_index;
		return true;
	}
}

void Simplex::parse_model(onestring user_model)
{
	onestring remainder = user_model;
	// If it's empty, return - empty simplex
	if (remainder.empty())
		return;

	// If not, continually loop through remainder
	// calling the unit parser
	while (!remainder.empty())
	{
		auto [attr, l] = UnitParser(remainder).parse();
		model.push_back(new Unit(attr));
		if (remainder.length() - l <= 0)
			return;
		onestring new_rem = remainder.substr(l, remainder.length());
		remainder = new_rem;
	}
}

bool Simplex::match(onestring model_check)
{
	onestring buffer = model_check;
	while(!buffer.empty())
	{
		int matched = model[model_index]->check_model(buffer);
		std::cout << "Matching " << buffer;
		std::cout << " against " << *model[model_index] << "... ";
		std::cout << (matched > -1 ? "true" : "false") << "\n";

		// Only advance if we're matching
		if (matched > -1)
		{
			// On a match, remove the matched amount from the front
			if (static_cast<int>(buffer.length()) > matched)
			{
				onestring new_buffer = buffer.substr(matched);
				buffer = new_buffer;
			}
			else
			{
				// We consumed the whole string, exit the loop
				break;
			}
			if (!next())
				break; // we're done
		}
		else
			return false;  // failed a match
	}
	// Reset simplex counter for future matches
	// NOTE: I think model_index should be a local var, and this method static
	model_index = 0;
	return true;
}

onestring Simplex::to_string() const
{
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<<(std::ostream& s, const Simplex& sx)
{
	s << "[ ";
	for (size_t i = 0; i < sx.model.size(); i++)
	{
		s << *sx.model[i];
		if (i < sx.model.size() - 1)
			s << ", ";
	}
	s << " ]";
	return s;
}