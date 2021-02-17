/** Basic Simplex Tests (SIMPLEXpress)
 * Version: 0.1
 *
 * Tests for the generation of the Simplex and the Simplex match function.
 *
 * Author(s): Anna R. Dunster, Ben D. Lovy, Jason C. McDonald
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

#ifndef SIMPLEXPRESS_LEXER_TESTS_HPP
#define SIMPLEXPRESS_LEXER_TESTS_HPP

#include <type_traits>

#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"
#include "simplexpress/simplex.hpp"

// X-tB0301
class TestLexer : public Test
{
	// Lexer test
	onestring model1 = "a^d/";
	onestring input1_pass_one = "a1";
	onestring input1_pass_two = "a123";
	onestring input1_fail = "4";
	uint_fast16_t lex_match_length1 = 2;
	uint_fast16_t lex_fail_length = 0;
	// Test vs generosity
	onestring model2 = "a^d+/3";
	onestring input2_pass_one = "a123";
	onestring input2_pass_two = "a123seven";
	onestring input2_pass_three = "a1237";
	onestring input2_fail = "a12steve";
	uint_fast16_t lex_match_length2 = 4;

public:
	TestLexer() = default;

	testdoc_t get_title() override { return "Lexer Match"; }

	testdoc_t get_docs() override
	{
		return "Successfully run lexer match with correct returns";
	}
	bool run() override
	{
		Simplex simplex1(model1);
		// Lex an input that matches completely
		SimplexResult results1one = simplex1.lex(input1_pass_one);
		PL_ASSERT_TRUE(results1one.match);
		PL_ASSERT_EQUAL(results1one.match_length, lex_match_length1);
		// Lex an input with a remainder
		SimplexResult results1two = simplex1.lex(input1_pass_two);
		PL_ASSERT_TRUE(results1two.match);
		PL_ASSERT_EQUAL(results1two.match_length, lex_match_length1);
		// Correctly fail to lex a non-match
		SimplexResult results1fail = simplex1.lex(input1_fail);
		PL_ASSERT_FALSE(results1fail.match);
		PL_ASSERT_EQUAL(results1fail.match_length, lex_fail_length);
		// Lexing a model that invokes generosity
		Simplex simplex2(model2);
		// Lex an input that matches completely
		SimplexResult results2one = simplex2.lex(input2_pass_one);
		PL_ASSERT_TRUE(results2one.match);
		PL_ASSERT_EQUAL(results2one.match_length, lex_match_length2);
		// Lex an input with a remainder
		SimplexResult results2two = simplex2.lex(input2_pass_two);
		PL_ASSERT_TRUE(results2two.match);
		PL_ASSERT_EQUAL(results2two.match_length, lex_match_length2);
		// Lex an input with a remainder that potentially tricks generosity
		SimplexResult results2three = simplex2.lex(input2_pass_three);
		PL_ASSERT_TRUE(results2three.match);
		PL_ASSERT_EQUAL(results2three.match_length, lex_match_length2);
		// Correctly fail to lex a non-match
		SimplexResult results2fail = simplex2.lex(input2_fail);
		PL_ASSERT_FALSE(results2fail.match);
		PL_ASSERT_EQUAL(results2fail.match_length, lex_fail_length);
		return true;
	}

	~TestLexer() = default;
};

// X-tB0302
class TestLexerSnag : public Test
{
	// Lexer test
	onestring model1 = "a~d/";
	onestring input1_pass_one = "a1";
	onestring input1_pass_two = "a123";
	onestring input1_snag = "1";
	onestring input1_fail = "4";
	uint_fast16_t lex_match_length1 = 2;
	uint_fast16_t lex_fail_length = 0;
	// Test vs generosity
	onestring model2 = "a~d+/3";
	onestring input2_pass_one = "a123";
	onestring input2_pass_two = "a123seven";
	onestring input2_pass_three = "a1237";
	onestring input2_snag = "12";
	onestring input2_fail = "a12steve";
	uint_fast16_t lex_match_length2 = 4;

public:
	TestLexerSnag() = default;

	testdoc_t get_title() override { return "Lexer Match with Snag"; }

	testdoc_t get_docs() override
	{
		return "Successfully run lexer match with snag and correct returns";
	}
	bool run() override
	{
		Simplex simplex1(model1);
		// Lex an input that matches completely
		SimplexResult results1one = simplex1.lex(input1_pass_one);
		PL_ASSERT_TRUE(results1one.match);
		PL_ASSERT_EQUAL(results1one.match_length, lex_match_length1);
		PL_ASSERT_EQUAL(results1one.snag_array[0], input1_snag);
		// Lex an input with a remainder
		SimplexResult results1two = simplex1.lex(input1_pass_two);
		PL_ASSERT_TRUE(results1two.match);
		PL_ASSERT_EQUAL(results1two.match_length, lex_match_length1);
		PL_ASSERT_EQUAL(results1two.snag_array[0], input1_snag);
		// Correctly fail to lex a non-match
		SimplexResult results1fail = simplex1.lex(input1_fail);
		PL_ASSERT_FALSE(results1fail.match);
		PL_ASSERT_EQUAL(results1fail.match_length, lex_fail_length);
		PL_ASSERT_TRUE(results1fail.snag_array.length() == 0);

		// Lex and snag a model that invokes generosity
		Simplex simplex2(model2);
		// Lex an input that matches completely
		SimplexResult results2one = simplex2.lex(input2_pass_one);
		PL_ASSERT_TRUE(results2one.match);
		PL_ASSERT_EQUAL(results2one.match_length, lex_match_length2);
		PL_ASSERT_EQUAL(results2one.snag_array[0], input2_snag);
		// Lex an input with a remainder
		SimplexResult results2two = simplex2.lex(input2_pass_two);
		PL_ASSERT_TRUE(results2two.match);
		PL_ASSERT_EQUAL(results2two.match_length, lex_match_length2);
		PL_ASSERT_EQUAL(results2two.snag_array[0], input2_snag);
		// Lex an input with a remainder that potentially tricks generosity
		SimplexResult results2three = simplex2.lex(input2_pass_three);
		PL_ASSERT_TRUE(results2three.match);
		PL_ASSERT_EQUAL(results2three.match_length, lex_match_length2);
		PL_ASSERT_EQUAL(results2three.snag_array[0], input2_snag);
		// Correctly fail to lex a non-match
		SimplexResult results2fail = simplex2.lex(input2_fail);
		PL_ASSERT_FALSE(results2fail.match);
		PL_ASSERT_EQUAL(results2fail.match_length, lex_fail_length);
		return true;
	}

	~TestLexerSnag() = default;
};

// X-tB0303
class TestLexerStatic : public Test
{
	uint_fast16_t lex_match_length1 = 3;
	uint_fast16_t lex_fail_length = 0;
	uint_fast16_t lex_match_length2 = 8;

public:
	TestLexerStatic() = default;

	testdoc_t get_title() override { return "Static Lexer Match"; }

	testdoc_t get_docs() override
	{
		return "Successfully run lexer match using static overloads";
	}
	bool run() override
	{
		// Lex with a direct string assignment model
		Simplex lex1("^d+/");
		SimplexResult results1 = lex1.lex("123");
		PL_ASSERT_TRUE(results1.match);
		PL_ASSERT_EQUAL(results1.match_length, lex_match_length1);
		// Lex using static function
		SimplexResult results2 = Simplex::lex("123", "^d+/");
		PL_ASSERT_TRUE(results2.match);
		PL_ASSERT_EQUAL(results2.match_length, lex_match_length1);
		// Correctly fail to lex a non-match with static function
		SimplexResult results3 = Simplex::lex("steve", "^d+/");
		PL_ASSERT_FALSE(results3.match);
		PL_ASSERT_EQUAL(results3.match_length, lex_fail_length);
		// Lex using static function and input overrun
		SimplexResult results4 = Simplex::lex("123abc", "^d+/");
		PL_ASSERT_TRUE(results4.match);
		PL_ASSERT_EQUAL(results4.match_length, lex_match_length1);
		// Lex an input with a remainder that potentially tricks generosity
		SimplexResult results5 = Simplex::lex("1237", "^d+/3");
		PL_ASSERT_TRUE(results5.match);
		PL_ASSERT_EQUAL(results5.match_length, lex_match_length1);
		// Test snag with static function
		SimplexResult results6 = Simplex::lex("steve123", "~l+/~d+/");
		PL_ASSERT_TRUE(results6.match);
		PL_ASSERT_EQUAL(results6.match_length, lex_match_length2);
		PL_ASSERT_EQUAL(results6.snag_array[0], "steve");
		PL_ASSERT_EQUAL(results6.snag_array[1], "123");
		return true;
	}

	~TestLexerStatic() = default;
};

// X-sB03 //
class TestSuite_Lexer : public TestSuite
{
public:
	TestSuite_Lexer() = default;
	void load_tests() override;
	testdoc_t get_title() override
	{
		return "SIMPLExpress: Simplex Lexer Tests";
	}
	~TestSuite_Lexer() = default;
};

#endif  // SIMPLEXPRESS_LEXER_TESTS_HPP