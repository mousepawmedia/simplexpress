/** SIMPLEXpress Experimenter
 * Version: 1.0
 *
 * A simple loop that can be enabled in the tester for manual testing and
 * experiments with Simplex models and results.
 *
 * Author(s): Anna R Dunster
 */

/* LICENSE
 * Copyright (c) 2021 MousePaw Media.
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
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef SIMPLEXPRESS_EXPERIMENTER_HPP
#define SIMPLEXPRESS_EXPERIMENTER_HPP

#include "iosqueak/channel.hpp"
#include "onestring/onestring.hpp"
#include "simplexpress/simplex.hpp"

/** Simplex Experimenter.
 * A simple loop to input a model and an input to
 * manually test the output of various matches. */
void simplex_experimenter()
{
	onestring model_input;
	Simplex simplex;
	onestring user_input;
	SimplexResult simplex_result;

	/** Get input and return as onestring */
	auto get_input = []() {
		std::string console_input;
		getline(std::cin, console_input);
		onestring return_str = console_input;
		return return_str;
	};

	channel << "Experimenter Engaged." << IOCtrl::endl;
	while (true) {
		channel << "Enter a Simplex model, or just hit enter to exit:"
				<< IOCtrl::endl;
		model_input = get_input();
		if (model_input.empty()) {
			break;
		} else {
			simplex = Simplex(model_input);
		}
		channel << "Your model is: " << simplex
				<< "\nEnter the user input to check against the model:"
				<< IOCtrl::endl;
		user_input = get_input();
		simplex_result =
			simplex.simplex_parser(user_input, simplex.model, false);
		channel << "Checking " << user_input << " against the model.\n"
				<< simplex_result << IOCtrl::endl;
	}
}

#endif  // !SIMPLEXPRESS_EXPERIMENTER_HPP