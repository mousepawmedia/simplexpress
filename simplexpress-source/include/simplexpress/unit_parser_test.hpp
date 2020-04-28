/** Unit Parser Tests (SIMPLExpress)
  * Version: 0.1
  *
  * Last Updated: 02 April 2020
  * Author(s): Ben D. Lovy
  */

/* LICENSE
 * Copyright (c) 2020 MousePaw Media.
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

#ifndef SIMPLEXPRESS_UNITPARSER_TESTS_HPP
#define SIMPLEXPRESS_UNITPARSER_TESTS_HPP

#include <type_traits>

#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"

#include "simplexpress/unit_parser.hpp"
#include "simplexpress/unit.hpp"

class TestCharacterParser : public Test
{
	onestring pass = "!a";
	onestring pass_two = "/";
	onestring fail = "a";
	onestring fail_two = "";
	onestring expected_pass = ParseResult::make_success('!', "a").to_string();
	onestring expected_pass_two = ParseResult::make_success('/', "").to_string();
	onestring expected_fail = ParseResult::make_error("Expecting !, got a", "a").to_string();
	onestring expected_fail_two = ParseResult::make_error("Out of input", "").to_string();
public:
	TestCharacterParser() = default;

	testdoc_t get_title()
	{
		return "Single Character Parser";
	}

	testdoc_t get_docs()
	{
		return "Successfully match '!' with the character parser";
	}
	bool run()
	{
		PL_ASSERT_EQUAL(
			UnitParser::negator(pass).to_string(),
			expected_pass);
		PL_ASSERT_EQUAL(
			UnitParser::unit_marker(pass_two).to_string(),
			expected_pass_two);
		PL_ASSERT_EQUAL(
			UnitParser::negator(fail).to_string(),
			expected_fail);
		PL_ASSERT_EQUAL(
			UnitParser::negator(fail_two).to_string(),
			expected_fail_two);
		return true;
	}

	~TestCharacterParser() {}
};

class TestLiteralParser : public Test
{
	onestring pass = "a";
	onestring pass_two = "a1";
	onestring fail = "";
	onestring expected_pass = ParseResult::make_success('a', "").to_string();
	onestring expected_pass_two = ParseResult::make_success('a', "1").to_string();
	onestring expected_fail = ParseResult::make_error("Out of input!", "").to_string();
public:
	TestLiteralParser() = default;

	testdoc_t get_title()
	{
		return "Literal Parser";
	}

	testdoc_t get_docs()
	{
		return "Verifies input consists of a single onechar";
	}
	bool run()
	{
		PL_ASSERT_EQUAL(
			UnitParser::literal(pass).to_string(),
			expected_pass);
		PL_ASSERT_EQUAL(
			UnitParser::literal(fail).to_string(),
			expected_fail);
		return true;
	}

	~TestLiteralParser() {}
};

class TestSpecifierParser : public Test
{
	onestring pass_one = "c";
	onestring pass_two = "lux";
	onestring pass_three = "sh";
	onestring fail = "q";
	onestring fail_two = "";
	onestring expected_pass_one = ParseResult::make_success('c', "").to_string();
	onestring expected_pass_two = ParseResult::make_success("lu", "x").to_string();
	onestring expected_pass_three = ParseResult::make_success("s", "h").to_string();
	onestring expected_fail = ParseResult::make_error("Unknown specifier!", "q").to_string();
	onestring expected_fail_two = ParseResult::make_error("Out of input", "").to_string();
public:
	TestSpecifierParser() = default;

	testdoc_t get_title()
	{
		return "Specifier Parser";
	}

	testdoc_t get_docs()
	{
		return "Verifies input contains a valid specifier and optional case modifier";
	}
	bool run()
	{
		PL_ASSERT_EQUAL(
			UnitParser::specifier_parser(pass_one).to_string(),
			expected_pass_one);
		PL_ASSERT_EQUAL(
			UnitParser::specifier_parser(pass_two).to_string(),
			expected_pass_two);
		PL_ASSERT_EQUAL(
			UnitParser::specifier_parser(pass_three).to_string(),
			expected_pass_three);
		PL_ASSERT_EQUAL(
			UnitParser::specifier_parser(fail).to_string(),
			expected_fail);
		PL_ASSERT_EQUAL(
			UnitParser::specifier_parser(fail_two).to_string(),
			expected_fail_two);
		return true;
	}

	~TestSpecifierParser() {}
};

class TestModifierParser : public Test
{
	onestring pass_one = "";
	onestring pass_two = "*/";
	onestring pass_three = "+/";
	onestring pass_four = "?/";
	// Checking for end of unit isn't this parser's job
	onestring pass_five = "+*";
	onestring fail = "a";
	onestring expected_pass_one = ParseResult::make_success("", "").to_string();
	onestring expected_pass_two = ParseResult::make_success('*', "/").to_string();
	onestring expected_pass_three = ParseResult::make_success('+', "/").to_string();
	onestring expected_pass_four = ParseResult::make_success('?', "/").to_string();
	onestring expected_pass_five = ParseResult::make_success('+', "*").to_string();
	onestring expected_fail = ParseResult::make_error("Invalid modifier: a", "a").to_string();
public:
	TestModifierParser() = default;

	testdoc_t get_title()
	{
		return "Modifier Parser";
	}

	testdoc_t get_docs()
	{
		return "Verifies input contains exactly one valid modifier";
	}
	bool run()
	{
		PL_ASSERT_EQUAL(
			UnitParser::modifier(pass_one).to_string(),
			expected_pass_one);
		PL_ASSERT_EQUAL(
			UnitParser::modifier(pass_two).to_string(),
			expected_pass_two);
		PL_ASSERT_EQUAL(
			UnitParser::modifier(pass_three).to_string(),
			expected_pass_three);
		PL_ASSERT_EQUAL(
			UnitParser::modifier(pass_four).to_string(),
			expected_pass_four);
		PL_ASSERT_EQUAL(
			UnitParser::modifier(pass_five).to_string(),
			expected_pass_five);
		PL_ASSERT_EQUAL(
			UnitParser::modifier(fail).to_string(),
			expected_fail);
		return true;
	}

	~TestModifierParser() {}
};

class TestVariousUnits : public Test
{
	onestring pass = "a";
	onestring pass_two = "/l/";
	onestring pass_three = "/a+/";
	onestring pass_four = "/d*/";
	onestring pass_five = "!q";
	onestring pass_six = "/!d/";
	Unit expected_pass = Unit(UnitAttributes(false, false, false, 'a', UnitType::Literal));
	Unit expected_pass_two = Unit(UnitAttributes(false, false, false, 'l', UnitType::Specifier));
	Unit expected_pass_three = Unit(UnitAttributes(false, true, false, 'a', UnitType::Specifier));
	Unit expected_pass_four = Unit(UnitAttributes(true, true, false, 'd', UnitType::Specifier));
	Unit expected_pass_five = Unit(UnitAttributes(false, false, true, 'q', UnitType::Literal));
	Unit expected_pass_six = Unit(UnitAttributes(false, false, true, 'd', UnitType::Specifier));
public:
	TestVariousUnits() = default;

	testdoc_t get_title()
	{
		return "UnitParser::parse()";
	}

	testdoc_t get_docs()
	{
		return "Tests UnitParser against various types of inputs";
	}
	bool run()
	{
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass).parse().attr).to_string(),
			expected_pass.to_string());
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass_two).parse().attr).to_string(),
			expected_pass_two.to_string());
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass_three).parse().attr).to_string(),
			expected_pass_three.to_string());
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass_four).parse().attr).to_string(),
			expected_pass_four.to_string());
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass_five).parse().attr).to_string(),
			expected_pass_five.to_string());
		PL_ASSERT_EQUAL(
			Unit(UnitParser(pass_six).parse().attr).to_string(),
			expected_pass_six.to_string());
		return true;
	}

	~TestVariousUnits() {}
};

class TestSuite_UnitParser : public TestSuite
{
public:
	TestSuite_UnitParser() = default;
	void load_tests();
	testdoc_t get_title()
	{
		return "SIMPLExpress: Unit Parser Tests";
	}
	~TestSuite_UnitParser() {}
};

#endif