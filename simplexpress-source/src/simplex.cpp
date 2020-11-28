#include "simplexpress/simplex.hpp"
#include "simplexpress/rules.hpp"

Simplex::Simplex(const onestring& user_model)
{
	parse_model(user_model, model);
}

bool Simplex::next(unsigned int& model_index, FlexArray<Unit*>& model)
{
	if(model_index+1 >= model.length())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Simplex::parse_model(const onestring& user_model, FlexArray<Unit*>& model_array)
{
	onestring remainder = user_model;
	// If it's empty, return - empty simplex
	if (remainder.empty())
		return;

	// If not, continually loop through remainder calling the unit parser
	while (!remainder.empty())
	{
		// TODO find a way to make VSCode ignore identifier undefined
		auto [attr, l] = UnitParser(remainder).parse();
		model_array.push_back(new Unit(attr));
		if (remainder.length() - l <= 0)
			return;
		onestring new_rem = remainder.substr(l, remainder.length());
		remainder = new_rem;
	}
}

bool Simplex::match(onestring& model_check)
{
	return match(model_check, this->model);
}

bool Simplex::match(onestring& model_check, FlexArray<Unit*>& model_array)
{
	unsigned int model_index = 0;
	onestring buffer = model_check;
	if (buffer.empty()) {
		return false;
	}
	while(!buffer.empty())
	{
		// Checks how long to keep checking for match
		int matched = model_array[model_index]->check_model(buffer);
		std::cout << "Matching " << buffer;
		std::cout << " against " << *model_array[model_index] << "... ";
		if (model_array[model_index]->attr.optional) {
			std::cout << (matched > 0 ? "true" : "false") << "\n";
		} else {
		std::cout << (matched > -1 ? "true" : "false") << "\n";
		}

		// Only advance if we're matching
		if (matched > -1)
		{
			// Check for input greater than matches if last item in model.
			if (!next(model_index, model_array))
			{
				if (matched < static_cast<int>(buffer.length())) {
					std::cout << "Input longer than model." << std::endl;
					return false; // Input longer than model, fail
				}
				else break;
			}
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
			// Advance to next Unit in model
			++model_index;
		}
		else
			return false;  // failed a match
	}
	return true;
}

bool Simplex::match(onestring& model_check, const onestring& input_model)
{
	FlexArray<Unit *> model_array;
	Simplex::parse_model(input_model, model_array);

	return match(model_check, model_array);
}

bool Simplex::match(const char* model_str, const onestring& input_model)
{
	onestring model_check = model_str;
	return match(model_check, input_model);
}

bool Simplex::match(onestring& model_check, const char* input_model_char)
{
	onestring input_model = input_model_char;
	return match(model_check, input_model);
}

bool Simplex::match(const char* model_str, const char* input_model_char)
{
	onestring model_check = model_str;
	onestring input_model = input_model_char;
	return match(model_check, input_model);
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
	for (size_t i = 0; i < sx.model.length(); i++)
	{
		s << *sx.model[i];
		if (i < sx.model.length() - 1)
			s << ", ";
	}
	s << " ]";
	return s;
}