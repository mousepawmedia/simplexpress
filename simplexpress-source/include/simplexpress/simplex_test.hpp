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

#ifndef SIMPLEXPRESS_BASIC_TESTS_HPP
#define SIMPLEXPRESS_BASIC_TESTS_HPP

#include "goldilocks/assertions.hpp"
#include "goldilocks/goldilocks.hpp"
#include "simplexpress/simplex.hpp"

// X-sB00 //

// X-tB0000a
class TestConstructASCIISimplex : public Test
{
	onestring model = "~l+/-^a+/-^d/.png";
	onestring expected = "[ Unit<specifier>::(l)::(+~), "
						 "Unit<literal>::(-)::(), "
						 "Unit<specifier>::(a)::(+), "
						 "Unit<literal>::(-)::(), "
						 "Unit<specifier>::(d)::(), "
						 "Unit<literal>::(.)::(), "
						 "Unit<literal>::(p)::(), "
						 "Unit<literal>::(n)::(), "
						 "Unit<literal>::(g)::() ]";

public:
	TestConstructASCIISimplex() = default;

	testdoc_t get_title() override { return "Construct ASCII Simplex"; }

	testdoc_t get_docs() override
	{
		return "Successfully construct 8-char model Simplex from an ASCII "
			   "model";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_EQUAL(simplex.to_string(), expected);
		return true;
	}

	~TestConstructASCIISimplex() = default;
};

// X-tB0000b
class TestConstructLiteralUnit : public Test
{
	onestring model1 = "N^%n*/o!";
	onestring model2 = "h^%i*/^d/";
	onestring expected1 = "[ Unit<literal>::(N)::(), "
						  "Unit<literal>::(n)::(?+), "
						  "Unit<literal>::(o)::(), "
						  "Unit<literal>::(!)::() ]";
	onestring expected2 = "[ Unit<literal>::(h)::(), "
						  "Unit<literal>::(i)::(?+), "
						  "Unit<specifier>::(d)::() ]";

public:
	TestConstructLiteralUnit() = default;

	testdoc_t get_title() override
	{
		return "Construct Simplex With Literal Units";
	}

	testdoc_t get_docs() override
	{
		return "Successfully construct 8-char model Simplex from an ASCII "
			   "model that includes literals inside Units";
	}
	bool run() override
	{
		Simplex simplex1(model1);
		PL_ASSERT_EQUAL(simplex1.to_string(), expected1);
		Simplex simplex2(model2);
		PL_ASSERT_EQUAL(simplex2.to_string(), expected2);
		return true;
	}

	~TestConstructLiteralUnit() = default;
};

// X-tB0000c
class TestConstructCharSimplex : public Test
{
	onestring expected = "[ Unit<specifier>::(l)::(+~), "
						 "Unit<literal>::(-)::(), "
						 "Unit<specifier>::(a)::(+), "
						 "Unit<literal>::(-)::(), "
						 "Unit<specifier>::(d)::(), "
						 "Unit<literal>::(.)::(), "
						 "Unit<literal>::(p)::(), "
						 "Unit<literal>::(n)::(), "
						 "Unit<literal>::(g)::() ]";

public:
	TestConstructCharSimplex() = default;

	testdoc_t get_title() override { return "Construct Simplex using char*"; }

	testdoc_t get_docs() override
	{
		return "Successfully construct Simplex from a char* model";
	}
	bool run() override
	{
		Simplex simplex("~l+/-^a+/-^d/.png");
		PL_ASSERT_EQUAL(simplex.to_string(), expected);
		return true;
	}

	~TestConstructCharSimplex() = default;
};

// X-tB0000d
class TestMultiCharSpeciferSimplex : public Test
{
	onestring model1 = "^al/";
	onestring expected1 = "[ Unit<specifier>::(al)::() ]";
	onestring model2 = "^al+/";
	onestring expected2 = "[ Unit<specifier>::(al)::(+) ]";

public:
	TestMultiCharSpeciferSimplex() = default;

	testdoc_t get_title() override
	{
		return "Multi-Character Specifier Unit generation";
	}

	testdoc_t get_docs() override
	{
		return "Successfully construct Simplex using a multi-character "
			   "specifier Unit model";
	}
	bool run() override
	{
		Simplex simplex1(model1);
		PL_ASSERT_EQUAL(simplex1.to_string(), expected1);
		Simplex simplex2(model2);
		PL_ASSERT_EQUAL(simplex2.to_string(), expected2);
		return true;
	}

	~TestMultiCharSpeciferSimplex() = default;
};

// X-tB0001
class TestMatchSingleUnitLiteral : public Test
{
	onestring model = "-";
	onestring input_pass = "-";
	onestring input_fail = "+";
	onestring input_fail_two = "--";

public:
	TestMatchSingleUnitLiteral() = default;

	testdoc_t get_title() override
	{
		return "Match Literal - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single literal";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchSingleUnitLiteral() = default;
};

// X-tB0002
class TestMatchSingleUnitSpecifierAlphanumeric : public Test
{
	onestring model = "^a/";
	onestring input_pass_one = "h";
	onestring input_pass_two = "5";
	onestring input_fail_one = "^";
	onestring input_fail_two = "h5";

public:
	TestMatchSingleUnitSpecifierAlphanumeric() = default;

	testdoc_t get_title() override
	{
		return "Match Alphanumeric Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single "
			   "alphanumeric character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail_one));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchSingleUnitSpecifierAlphanumeric() = default;
};

// X-tB0003
class TestMatchSingleUnitSpecifierDigit : public Test
{
	onestring model = "^d/";
	onestring input_pass = "5";
	onestring input_fail = "h";

public:
	TestMatchSingleUnitSpecifierDigit() = default;

	testdoc_t get_title() override
	{
		return "Match Digit Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single digit "
			   "character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierDigit() = default;
};

// X-tB0004
class TestMatchSingleUnitSpecifierLatin : public Test
{
	onestring model = "^l/";
	onestring input_pass = "h";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierLatin() = default;

	testdoc_t get_title() override
	{
		return "Match Latin Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single latin "
			   "character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierLatin() = default;
};

// X-tB0005
class TestMatchSingleUnitSpecifierNewline : public Test
{
	onestring model = "^n/";
	onestring input_pass = "\n";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierNewline() = default;

	testdoc_t get_title() override
	{
		return "Match Newline Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single newline";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierNewline() = default;
};

// X-tB0006
class TestMatchSingleUnitSpecifierPunctuation : public Test
{
	onestring model = "^p/";
	onestring input_pass = ".";
	onestring input_pass_two = "!";
	onestring input_fail = "5";
	onestring input_fail_two = "*";

public:
	TestMatchSingleUnitSpecifierPunctuation() = default;

	testdoc_t get_title() override
	{
		return "Match Punctuation Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single "
			   "punctuation character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchSingleUnitSpecifierPunctuation() = default;
};

// X-tB0007
class TestMatchSingleUnitSpecifierCarriageReturn : public Test
{
	onestring model = "^r/";
	onestring input_pass = "\r";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierCarriageReturn() = default;

	testdoc_t get_title() override
	{
		return "Match Carriage Return Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single "
			   "carriage return";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierCarriageReturn() = default;
};

// X-tB0008
class TestMatchSingleUnitSpecifierLiteralSpace : public Test
{
	onestring model = "^s/";
	onestring input_pass = " ";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierLiteralSpace() = default;

	testdoc_t get_title() override
	{
		return "Match Literal Space Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single space "
			   "character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierLiteralSpace() = default;
};

// X-tB0009
class TestMatchSingleUnitSpecifierTab : public Test
{
	onestring model = "^t/";
	onestring input_pass = "\t";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierTab() = default;

	testdoc_t get_title() override
	{
		return "Match Tab Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single tab "
			   "character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierTab() = default;
};

// X-tB0010
class TestMatchSingleUnitSpecifierWhitespace : public Test
{
	onestring model = "^w/";
	onestring input_pass_one = " ";
	onestring input_pass_two = "\t";
	onestring input_pass_three = "\n";
	onestring input_fail = "5";

public:
	TestMatchSingleUnitSpecifierWhitespace() = default;

	testdoc_t get_title() override
	{
		return "Match Whitespace Specifier - Single-Unit Model";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a single "
			   "whitespace character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_TRUE(simplex.match(input_pass_three));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSingleUnitSpecifierWhitespace() = default;
};

// X-tB0011
class TestMatchMultiUnitLiterals : public Test
{
	onestring model = "hi";
	onestring input_pass = "hi";
	onestring input_fail = "5j";
	onestring input_fail_two = "hi34";

public:
	TestMatchMultiUnitLiterals() = default;

	testdoc_t get_title() override { return "Match Multiple Literals"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing multiple literal "
			   "characters";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		PL_ASSERT_TRUE(simplex.match("HI", "HI"));
		PL_ASSERT_FALSE(simplex.match("HI", "hi"));
		return true;
	}

	~TestMatchMultiUnitLiterals() = default;
};

// X-tB0012
class TestMatchMultiUnitLiteralSpecifier : public Test
{
	onestring model = "^d/i";
	onestring input_pass_one = "4i";
	onestring input_pass_two = "9i";
	onestring input_fail_one = "ai";
	onestring input_fail_two = "32";

public:
	TestMatchMultiUnitLiteralSpecifier() = default;

	testdoc_t get_title() override { return "Match Specifier + Literal"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a specifier "
			   "followed by a literal";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail_one));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchMultiUnitLiteralSpecifier() = default;
};

// X-tB0013
class TestMatchMultiUnitSpecifiers : public Test
{
	onestring model = "^d/^l/";
	onestring input_pass_one = "4i";
	onestring input_pass_two = "9i";
	onestring input_fail_one = "ai";
	onestring input_fail_two = "32";
	onestring input_fail_three = "3a7";

public:
	TestMatchMultiUnitSpecifiers() = default;

	testdoc_t get_title() override { return "Match Two Specifiers"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing two specifiers";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail_one));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchMultiUnitSpecifiers() = default;
};

// X-tB0014
class TestMatchSpecifierMultiplier : public Test
{
	onestring model = "^d+/";
	onestring input_pass_one = "3";
	onestring input_pass_two = "65";
	onestring input_fail = "g";
	onestring input_fail_two = "65abc";

public:
	TestMatchSpecifierMultiplier() = default;

	testdoc_t get_title() override { return "Match Specifier with Multiplier"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing a multiplier "
			   "specifier";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchSpecifierMultiplier() = default;
};

// X-tB0015
class TestMatchSpecifierOptional : public Test
{
	onestring model = "x^d?/";
	onestring input_pass_one = "x";
	onestring input_pass_two = "x5";
	onestring input_fail = "xd";

public:
	TestMatchSpecifierOptional() = default;

	testdoc_t get_title() override { return "Match Optional Specifier"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing an optional "
			   "specifier";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchSpecifierOptional() = default;
};

// X-tB0016
class TestMatchSpecifierOptionalMultiple : public Test
{
	onestring model = "x^d*/";
	onestring input_pass_one = "x";
	onestring input_pass_two = "x5";
	onestring input_pass_three = "x12";
	onestring input_fail = "xd";
	onestring input_fail_two = "x45c";

public:
	TestMatchSpecifierOptionalMultiple() = default;

	testdoc_t get_title() override
	{
		return "Match OptionalMultiple Specifier";
	}

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing an optional "
			   "multiple specifier";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_TRUE(simplex.match(input_pass_three));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		return true;
	}

	~TestMatchSpecifierOptionalMultiple() = default;
};

// X-tB0017
class TestMatchAny : public Test
{
	onestring model = "^./";
	onestring input_pass_one = "^";
	onestring input_pass_two = "6";
	onestring input_fail = "";

public:
	TestMatchAny() = default;

	testdoc_t get_title() override { return "Match Any Character"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model containing any character";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchAny() = default;
};

// X-tB0018
class TestMatchNot : public Test
{
	onestring model = "^!d/";
	onestring input_pass_one = "b";
	onestring input_pass_two = "^";
	onestring input_fail = "4";

public:
	TestMatchNot() = default;

	testdoc_t get_title() override { return "Match Negated Specifier"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a model with a negated specifier";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail));
		return true;
	}

	~TestMatchNot() = default;
};

// X-tB0019
class TestMatchWithSnag : public Test
{
public:
	TestMatchWithSnag() = default;

	testdoc_t get_title() override { return "Match Using Snag Units"; }

	testdoc_t get_docs() override
	{
		return "Match various inputs using snag marker instead of unit marker";
	}

	bool run() override
	{
		PL_ASSERT_TRUE(Simplex::match("1", "~d/"));
		PL_ASSERT_FALSE(Simplex::match("seven", "~d/"));
		return true;
	}

	~TestMatchWithSnag() = default;
};

// X-tB0020
class TestNegativeMultiple : public Test
{
	onestring model = "abc^!d+/";
	onestring model2 = "^!d+/abc";
	onestring model3 = "^!d+/ and ^d+/";
	onestring model4 = "abc^!d*/";
	onestring input_pass_one = "abcstuff";
	onestring input_pass_two = "abc!@#";
	onestring input_fail_one = "abc123";
	onestring input_fail_two = "abc";

public:
	TestNegativeMultiple() = default;

	testdoc_t get_title() override
	{
		return "Match using Negative Multiple modifiers";
	}

	testdoc_t get_docs() override
	{
		return "Match cases with negative multiples to ensure correct behavior";
	}

	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match(input_pass_one));
		PL_ASSERT_TRUE(simplex.match(input_pass_two));
		PL_ASSERT_FALSE(simplex.match(input_fail_one));
		PL_ASSERT_FALSE(simplex.match(input_fail_two));
		PL_ASSERT_TRUE(Simplex::match("stuffabc", model2));
		PL_ASSERT_FALSE(Simplex::match("123abc", model2));
		PL_ASSERT_FALSE(Simplex::match("abc", model2));
		PL_ASSERT_TRUE(Simplex::match("ABC and 123", model3));
		PL_ASSERT_TRUE(Simplex::match("... and 5", model3));
		PL_ASSERT_FALSE(Simplex::match("123 and 123", model3));
		PL_ASSERT_TRUE(Simplex::match("abc", model4));
		PL_ASSERT_FALSE(Simplex::match("abc123", model4));
		return true;
	}

	~TestNegativeMultiple() = default;
};

// X-tB0021
class TestLiteralModifiers : public Test
{
public:
	TestLiteralModifiers() = default;

	testdoc_t get_title() override { return "Match Literals With Modifiers"; }

	testdoc_t get_docs() override
	{
		return "Match models containing literals with modifiers such as "
			   "optional, multiple, negative.";
	}

	bool run() override
	{
		// Optionals
		PL_ASSERT_TRUE(Simplex::match("hi?5", "hi?^d/"));
		PL_ASSERT_TRUE(Simplex::match("hi5", "h^%i?/^d/"));
		PL_ASSERT_TRUE(Simplex::match("h5", "h^%i?/^d/"));
		PL_ASSERT_FALSE(Simplex::match("hiii5", "h^%i?/^d/"));
		PL_ASSERT_FALSE(Simplex::match("q5", "h^%i?/^d/"));
		// Multiples
		PL_ASSERT_TRUE(Simplex::match("hiii5", "h^%i+/^d/"));
		PL_ASSERT_FALSE(Simplex::match("h5", "h^%i+/^d/"));
		PL_ASSERT_FALSE(Simplex::match("q5", "h^%i+/^d/"));
		// Optional Multiple
		PL_ASSERT_TRUE(Simplex::match("hi5", "h^%i*/^d/"));
		PL_ASSERT_TRUE(Simplex::match("hiii5", "h^%i*/^d/"));
		PL_ASSERT_TRUE(Simplex::match("h5", "h^%i*/^d/"));
		PL_ASSERT_FALSE(Simplex::match("h 5", "h^%i*/^d/"));
		PL_ASSERT_FALSE(Simplex::match("q5", "h^%i*/^d/"));
		// Negative
		PL_ASSERT_TRUE(Simplex::match("hj5", "h^!%i/^d/"));
		PL_ASSERT_TRUE(Simplex::match("h75", "h^!%i/^d/"));
		PL_ASSERT_FALSE(Simplex::match("hi5", "h^!%i/^d/"));
		PL_ASSERT_FALSE(Simplex::match("h5", "h^!%i/^d/"));
		return true;
	}

	~TestLiteralModifiers() = default;
};

// X-tB0022
class TestOperatorSpecifier : public Test
{
public:
	TestOperatorSpecifier() = default;

	testdoc_t get_title() override { return "Match Operator Specifier"; }

	testdoc_t get_docs() override
	{
		return "Match models containing math operator specifiers";
	}

	bool run() override
	{
		// Pass
		PL_ASSERT_TRUE(Simplex::match("+", "^o/"));
		PL_ASSERT_TRUE(Simplex::match("%", "^o/"));
		PL_ASSERT_TRUE(Simplex::match("-^*", "^o+/"));
		// Fail
		PL_ASSERT_FALSE(Simplex::match("#", "^o/"));
		PL_ASSERT_FALSE(Simplex::match(")", "^o/"));
		PL_ASSERT_FALSE(Simplex::match("abc", "^o+/"));
		return true;
	}

	~TestOperatorSpecifier() = default;
};

// X-tB0023
class TestCapitalSpecifiers : public Test
{
public:
	TestCapitalSpecifiers() = default;

	testdoc_t get_title() override { return "Match Capitalized Specifiers"; }

	testdoc_t get_docs() override
	{
		return "Match models with capitalized specifiers";
	}

	bool run() override
	{
		// Pass
		PL_ASSERT_TRUE(Simplex::match("abc", "^al+/"));
		PL_ASSERT_TRUE(Simplex::match("ABC", "^au+/"));
		// Fail
		PL_ASSERT_FALSE(Simplex::match("abc", "^au+/"));
		PL_ASSERT_FALSE(Simplex::match("ABC", "^al+/"));
		return true;
	}

	~TestCapitalSpecifiers() = default;
};

// TODO: Set

// TODO:  Literal set

// TODO: Group

// TODO: Line beginning/end

// TODO: Number or Range

// X-tB0050
class TestStaticMatch : public Test
{
	onestring model = "^d/";
	onestring input_pass = "5";
	onestring input_fail = "d";
	onestring input_fail2 = "12345";

public:
	TestStaticMatch() = default;

	testdoc_t get_title() override { return "Static Match"; }

	testdoc_t get_docs() override
	{
		return "Test success of the Static Match Functions";
	}
	bool run() override
	{
		// Test using onestring variables
		PL_ASSERT_TRUE(Simplex::match(input_pass, model));
		PL_ASSERT_FALSE(Simplex::match(input_fail, model));
		PL_ASSERT_FALSE(Simplex::match(input_fail, model));
		// Test using string literals
		PL_ASSERT_TRUE(Simplex::match("5", model));
		PL_ASSERT_FALSE(Simplex::match("d", model));
		PL_ASSERT_TRUE(Simplex::match(input_pass, "^d/"));
		PL_ASSERT_TRUE(Simplex::match("5", "^d/"));
		return true;
	}

	~TestStaticMatch() = default;
};

// X-tB0051
class TestGreedyLogic : public Test
{
	onestring model1 = "^l+/fred";
	onestring model2 = "^l+/fred^d+/";
	onestring model3 = "^l+/ and ^d+/";
	onestring model4 = "^l*/X^d+/";
	onestring model1_pass = "stufffred";
	onestring model1_fail = "stuff";
	onestring model2_pass = "stufffred1234";
	onestring model2_fail = "stuff1234";
	onestring model3_pass = "fred and 1234";
	onestring model3_fail = "fred 1234";
	onestring model3_fail_two = "and 4";
	onestring model4_pass_one = "XaX3";
	onestring model4_pass_two = "X1";
	onestring model4_fail = "steve2";

public:
	TestGreedyLogic() = default;

	testdoc_t get_title() override { return "Test Greedy Logic"; }

	testdoc_t get_docs() override
	{
		return "Tests whether multiple is getting too greedy";
	}

	bool run() override
	{
		// Model 1
		PL_ASSERT_TRUE(Simplex::match(model1_pass, model1));
		PL_ASSERT_FALSE(Simplex::match(model1_fail, model1));
		// Model 2
		PL_ASSERT_TRUE(Simplex::match(model2_pass, model2));
		PL_ASSERT_FALSE(Simplex::match(model2_fail, model2));
		// Model 3
		PL_ASSERT_TRUE(Simplex::match(model3_pass, model3));
		PL_ASSERT_FALSE(Simplex::match(model3_fail, model3));
		PL_ASSERT_FALSE(Simplex::match(model3_fail_two, model3));
		// Model 4
		PL_ASSERT_TRUE(Simplex::match(model4_pass_one, model4));
		PL_ASSERT_TRUE(Simplex::match(model4_pass_two, model4));
		PL_ASSERT_FALSE(Simplex::match(model4_fail, model4));
		return true;
	}

	~TestGreedyLogic() = default;
};

// X-tB0052
class TestMemberMatchChar : public Test
{
	onestring model = "^!d/";
	onestring input_pass_one = "b";
	onestring input_pass_two = "^";
	onestring input_fail = "4";

public:
	TestMemberMatchChar() = default;

	testdoc_t get_title() override { return "Member Match using char*"; }

	testdoc_t get_docs() override
	{
		return "Successfully match against a member model with a char* input";
	}
	bool run() override
	{
		Simplex simplex(model);
		PL_ASSERT_TRUE(simplex.match("b"));
		PL_ASSERT_TRUE(simplex.match("^"));
		PL_ASSERT_FALSE(simplex.match("4"));
		return true;
	}

	~TestMemberMatchChar() = default;
};

// X-sB00 //
class TestSuite_Basic : public TestSuite
{
public:
	TestSuite_Basic() = default;
	void load_tests() override;
	testdoc_t get_title() override
	{
		return "SIMPLExpress: Basic Simplex Tests";
	}
	~TestSuite_Basic() = default;
};

#endif  // SIMPLEXPRESS_BASIC_TESTS_HPP