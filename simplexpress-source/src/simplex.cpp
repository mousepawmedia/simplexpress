#include "simplexpress/simplex.hpp"

#include "simplexpress/rules.hpp"

Simplex::Simplex(const onestring& user_model)
{
	UnitParser::parse_model(user_model, model);
}

Simplex::Simplex(const char* user_model)
{
	UnitParser::parse_model(static_cast<onestring>(user_model), model);
}

SimplexResult Simplex::simplex_parser(const onestring& model_check,
									  FlexArray<Unit*>& model_array)
{
	SimplexResult result;
	unsigned int model_index = 0;
	onestring buffer = model_check;
	if (buffer.empty()) {
		result.match = false;
	}
	while (!buffer.empty()) {
		// Checks how many characters are matched by the current Unit in model
		int matched = model_array[model_index]->check_model(buffer);
		std::cout << "Matching " << buffer;
		std::cout << " against " << *model_array[model_index] << "... ";
		if (model_array[model_index]->attr.optional) {
			std::cout << (matched > 0 ? "true" : "false") << "\n";
		} else {
			std::cout << (matched > -1 ? "true" : "false") << "\n";
		}

		// Only advance if we're matching
		if (matched > -1) {
			// If snag unit, store matched characters in snag_array,
			// skip empty optional.
			if (model_array[model_index]->attr.snag && matched >= 0) {
				if (matched > 0) {
					result.snag_array.push(buffer.substr(0, matched));
				} else if (matched == 0) {
					onestring empty = "";
					result.snag_array.push(empty);
				}
			}
			// Check for input greater than matches if last Unit in model.
			if (!next(model_index, model_array)) {
				if (matched < static_cast<int>(buffer.length())) {
					std::cout << "Input longer than model." << std::endl;
					result.match = false;  // Input longer than model, fail
				}
				break;
			}
			// Check whether we're being too greedy on multiples,
			// skip empty optional.
			if (model_array[model_index]->attr.multiple && matched > 0) {
				matched = generosity(buffer, matched, model_index, model_array);
			}
			// Then remove the matched amount from the front.
			if (static_cast<int>(buffer.length()) >= matched) {
				if (static_cast<int>(buffer.length()) == matched) {
					buffer.clear();
				} else {
					onestring new_buffer = buffer.substr(matched);
					buffer = new_buffer;
				}
			} else {
				// We consumed the whole string, exit the loop
				break;
			}
			// If buffer is now empty, but we still have non-optional units to
			// match, fail.
			if (buffer.empty() && next(model_index, model_array)) {
				result.match = (check_optional(model_index, model_array));
				break;
			}
			// Advance to next Unit in model
			++model_index;
		} else {
			result.match = false;  // failed a match
			break;
		}
	}
	// Empty return array if match is false
	if (result.match == false) {
		result.snag_array.clear();
	}
	return result;
}

bool Simplex::match(const onestring& model_check)
{
	SimplexResult result = simplex_parser(model_check, this->model);
	return result.match;
}

bool Simplex::match(const char* model_check)
{
	SimplexResult result =
		simplex_parser(static_cast<onestring>(model_check), this->model);
	return result.match;
}

bool Simplex::match(const onestring& model_check, const onestring& input_model)
{
	FlexArray<Unit*> model_array;
	UnitParser::parse_model(input_model, model_array);

	SimplexResult result = simplex_parser(model_check, model_array);
	return result.match;
}

bool Simplex::match(const char* model_check, const onestring& input_model)
{
	return match(static_cast<onestring>(model_check), input_model);
}

bool Simplex::match(const onestring& model_check, const char* input_model)
{
	return match(model_check, static_cast<onestring>(input_model));
}

bool Simplex::match(const char* model_check, const char* input_model)
{
	return match(static_cast<onestring>(model_check),
				 static_cast<onestring>(input_model));
}

FlexArray<onestring> Simplex::snag(const onestring& snag_check)
{
	SimplexResult result = simplex_parser(snag_check, this->model);
	return result.snag_array;
}

FlexArray<onestring> Simplex::snag(const char* snag_check)
{
	SimplexResult result =
		simplex_parser(static_cast<onestring>(snag_check), this->model);
	return result.snag_array;
}

FlexArray<onestring> Simplex::snag(const onestring& snag_check,
								   const onestring& input_model)
{
	FlexArray<Unit*> model_array;
	UnitParser::parse_model(input_model, model_array);

	SimplexResult result = simplex_parser(snag_check, model_array);
	return result.snag_array;
}

FlexArray<onestring> Simplex::snag(const char* snag_check,
								   const onestring& input_model)
{
	return snag(static_cast<onestring>(snag_check), input_model);
}

FlexArray<onestring> Simplex::snag(const onestring& snag_check,
								   const char* input_model)
{
	return snag(snag_check, static_cast<onestring>(input_model));
}

FlexArray<onestring> Simplex::snag(const char* snag_check,
								   const char* input_model)
{
	return snag(static_cast<onestring>(snag_check),
				static_cast<onestring>(input_model));
}

onestring Simplex::to_string() const
{
	std::ostringstream ss;
	ss << *this;
	return ss.str();
}

bool Simplex::next(const unsigned int& model_index,
				   const FlexArray<Unit*>& model_array)
{
	return !(model_index + 1 >= model_array.length());
}

bool Simplex::check_optional(const unsigned int& model_index,
							 const FlexArray<Unit*>& model_array)
{
	unsigned int current_index = model_index;
	while (next(current_index, model_array)) {
		current_index++;
		if (!model_array[current_index]->attr.optional) {
			return false;
		}
	}
	return true;
}

int Simplex::generosity(const onestring incoming_buffer,
						const int total_matched,
						const int starting_index,
						const FlexArray<Unit*>& model_array)
{
	/** We will handle generosity slightly differently depending whether the
	 * starting unit is optional or not. We know the first character of the
	 * incoming buffer matches the model at the current index, but if it's
	 * optional we want to check it against the model at the next index, too.
	 * If it's optional, then later units could potentially match ALL of the
	 * overlap. If it's not optional, we'll remove it from the passed in buffer,
	 * because it still needs to ultimately return false if overlap is complete.
	 *
	 * Also, we don't want to change any of the external values with this
	 * function, but all of the values will change inside it as they're used,
	 * so we copy everything.*/
	onestring buffer;
	int greedy_match;
	if (model_array[starting_index]->attr.optional) {
		buffer = incoming_buffer;
		greedy_match = total_matched + 1;
	} else {
		buffer = incoming_buffer.substr(1);
		greedy_match = total_matched;
	}
	unsigned int current_index = starting_index;
	// How much are we matching, and where in the string?
	int generous_match = 0;
	int match_start_index = 0;
	int count = 0;

	// Check model on incoming buffer
	while (greedy_match > 0) {
		--greedy_match;
		++count;
		int matched = model_array[current_index + 1]->check_model(buffer);

		if (matched <= 0) {
			// Advance buffer if next unit doesn't match, but if we already
			// advanced the model, we need to retry it against the beginning
			// of the model, so we don't advance.
			if (match_start_index > 0) {
				++greedy_match;
				--count;
			} else {
				if (buffer.length() <= 1) {
					buffer.clear();
				} else {
					buffer = buffer.substr(1);
				}
			}
			// If next unit doesn't match, reset indexes and generous quantity.
			match_start_index = 0;
			current_index = starting_index;
			generous_match = 0;
		} else {
			// If next unit matches, store index if we don't already one...
			if (!(match_start_index > 0)) {
				match_start_index = count;
			}
			// ... advance model and count matches ...
			++current_index;
			generous_match += matched;
			// ... and advance buffer, unless we run out of units or buffer.
			if (!next(current_index, model_array) ||
				static_cast<int>(buffer.length()) <= matched) {
				break;
			} else {
				buffer = buffer.substr(matched);
			}
		}
		// If match consumed multiple characters, index additional characters.
		count += std::max(0, matched - 1);
	}

	/** If we have a successful start index after iterating through the end of
	 * the greedy match, then we have overlap to remove.
	 * Also, if optional, we added an extra position to the check, so we
	 * have to remove it here.*/
	if (match_start_index > 0 &&
		(generous_match + match_start_index >= total_matched)) {
		return (model_array[starting_index]->attr.optional)
				   ? (match_start_index - 1)
				   : match_start_index;
	} else {
		return total_matched;
	}
}

std::ostream& operator<<(std::ostream& s, const Simplex& sx)
{
	s << "[ ";
	for (size_t i = 0; i < sx.model.length(); i++) {
		s << *sx.model[i];
		if (i < sx.model.length() - 1) {
			s << ", ";
		}
	}
	s << " ]";
	return s;
}