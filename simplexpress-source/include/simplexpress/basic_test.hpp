/** Basic Sanity Tests (SIMPLExpress)
  * Version: 0.1
  *
  * Once other tests have been added to SIMPLExpress, this file can
  * be removed.
  *
  * Author(s): Ben D. Lovy, Jason C. McDonald
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

#ifndef SIMPLEXPRESS_BASIC_TESTS_HPP
#define SIMPLEXPRESS_BASIC_TESTS_HPP

#include <type_traits>

#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"

#include "simplexpress/simplex.hpp"

class TestConstructASCIISimplex : public Test
{
    onestring model = "^l+/-^a+/-^d/.png^(24)?/";
public:
    TestConstructASCIISimplex() = default;

    testdoc_t get_title()
    {
        return "Construct ASCII Simplex";
    }

    testdoc_t get_docs()
    {
        return "Successfully construct 8-char model Simplex from an ASCII model";
    }
    bool run()
    {
        Simplex simplex(model);
        return true;
    }

    ~TestConstructASCIISimplex(){}
};

class TestMatchSingleUnitLiteral : public Test
{
    onestring model = "-";
    onestring input_pass = "-";
    onestring input_fail = "+";
public:
    TestMatchSingleUnitLiteral() = default;

    testdoc_t get_title()
    {
        return "Match Literal - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single literal";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitLiteral(){}
};

class TestMatchSingleUnitSpecifierAlphanumeric : public Test
{
    onestring model = "^a/";
    onestring input_pass_one = "h";
    onestring input_pass_two = "5";
    onestring input_fail = "^";
public:
    TestMatchSingleUnitSpecifierAlphanumeric() = default;

    testdoc_t get_title()
    {
        return "Match Alphanumeric Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single alphanumeric character";
    }
    bool run()
    {
        Simplex simplex= Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierAlphanumeric(){}
};

class TestMatchSingleUnitSpecifierDigit : public Test
{
    onestring model = "^d/";
    onestring input_pass = "5";
    onestring input_fail = "h";
public:
    TestMatchSingleUnitSpecifierDigit() = default;

    testdoc_t get_title()
    {
        return "Match Alphanumeric Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single alphanumeric character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierDigit(){}
};

class TestMatchSingleUnitSpecifierLatin : public Test
{
    onestring model = "^l/";
    onestring input_pass = "h";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierLatin() = default;

    testdoc_t get_title()
    {
        return "Match Latin Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single latin character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierLatin(){}
};

class TestMatchSingleUnitSpecifierNewline : public Test
{
    onestring model = "^n/";
    onestring input_pass = "\n";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierNewline() = default;

    testdoc_t get_title()
    {
        return "Match Newline Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single newline";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierNewline(){}
};

class TestMatchSingleUnitSpecifierPunctuation : public Test
{
    onestring model = "^p/";
    onestring input_pass = ".";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierPunctuation() = default;

    testdoc_t get_title()
    {
        return "Match Punctuation Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single punctuation character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierPunctuation(){}
};

class TestMatchSingleUnitSpecifierCarriageReturn : public Test
{
    onestring model = "^r/";
    onestring input_pass = "\r";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierCarriageReturn() = default;

    testdoc_t get_title()
    {
        return "Match Carriage Return Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single carriage return";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierCarriageReturn(){}
};

class TestMatchSingleUnitSpecifierLiteralSpace : public Test
{
    onestring model = "^s/";
    onestring input_pass = " ";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierLiteralSpace() = default;

    testdoc_t get_title()
    {
        return "Match Literal Space Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single space character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierLiteralSpace(){}
};

class TestMatchSingleUnitSpecifierTab : public Test
{
    onestring model = "^t/";
    onestring input_pass = "\t";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierTab() = default;

    testdoc_t get_title()
    {
        return "Match Tab Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single tab character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierTab(){}
};

class TestMatchSingleUnitSpecifierWhitespace : public Test
{
    onestring model = "^w/";
    onestring input_pass_one = " ";
    onestring input_pass_two = "\t";
    onestring input_pass_three = "\n";
    onestring input_fail = "5";
public:
    TestMatchSingleUnitSpecifierWhitespace() = default;

    testdoc_t get_title()
    {
        return "Match Whitespace Specifier - Single-Unit Model";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a single whitespace character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_TRUE(simplex.match(input_pass_three));
        //FIXME: this test seems to try to assert true instead, why?
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSingleUnitSpecifierWhitespace(){}
};

class TestMatchMultiUnitLiterals : public Test
{
    onestring model = "hi";
    onestring input_pass = "hi";
    onestring input_fail = "5j";
public:
    TestMatchMultiUnitLiterals() = default;

    testdoc_t get_title()
    {
        return "Match Two Literals";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing two literal characters";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchMultiUnitLiterals(){}
};

class TestMatchMultiUnitLiteralSpecifier : public Test
{
    onestring model = "^d/i";
    onestring input_pass_one = "4i";
    onestring input_pass_two = "9i";
    onestring input_fail_one = "ai";
    onestring input_fail_two = "32";
public:
    TestMatchMultiUnitLiteralSpecifier() = default;

    testdoc_t get_title()
    {
        return "Match Specifier + Literal";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing a specifier followed by a literal";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail_one));
        PL_ASSERT_FALSE(simplex.match(input_fail_two));
        return true;
    }

    ~TestMatchMultiUnitLiteralSpecifier(){}
};

class TestMatchMultiUnitSpecifiers : public Test
{
    onestring model = "^d/^l/";
    onestring input_pass_one = "4i";
    onestring input_pass_two = "9i";
    onestring input_fail_one = "ai";
    onestring input_fail_two = "32";
public:
    TestMatchMultiUnitSpecifiers() = default;

    testdoc_t get_title()
    {
        return "Match Two Specifiers";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing two specifiers";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail_one));
        PL_ASSERT_FALSE(simplex.match(input_fail_two));
        return true;
    }

    ~TestMatchMultiUnitSpecifiers(){}
};

class TestMatchSpecifierMultiplier : public Test
{
    onestring model = "^d+/";
    onestring input_pass_one = "3g";
    onestring input_pass_two = "65";
    onestring input_fail = "g";
public:
    TestMatchSpecifierMultiplier() = default;

    testdoc_t get_title()
    {
        return "Match Specifier with Multiplier";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing one or more specifier matches";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSpecifierMultiplier(){}
};

class TestMatchSpecifierOptional : public Test
{
    onestring model = "x^d?/";
    onestring input_pass_one = "x";
    onestring input_pass_two = "x5";
    onestring input_fail = "xd";
public:
    TestMatchSpecifierOptional() = default;

    testdoc_t get_title()
    {
        return "Match Optional Specifier";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing an optional specifier";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSpecifierOptional(){}
};

class TestMatchSpecifierOptionalMultiple : public Test
{
    onestring model = "x^d*/";
    onestring input_pass_one = "x";
    onestring input_pass_two = "x5";
    onestring input_fail = "xd";
public:
    TestMatchSpecifierOptionalMultiple() = default;

    testdoc_t get_title()
    {
        return "Match OptionalMultiple Specifier";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing an optional specifier";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchSpecifierOptionalMultiple(){}
};

class TestMatchAny : public Test
{
    onestring model = "^./";
    onestring input_pass_one = "^";
    onestring input_pass_two = "6";
public:
    TestMatchAny() = default;

    testdoc_t get_title()
    {
        return "Match Any Character";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model containing any character";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        return true;
    }

    ~TestMatchAny(){}
};

class TestMatchNot : public Test
{
    onestring model = "^!d/";
    onestring input_pass_one = "b";
    onestring input_pass_two = "^";
    onestring input_fail = "4";
public:
    TestMatchNot() = default;

    testdoc_t get_title()
    {
        return "Match Negated Specifier";
    }

    testdoc_t get_docs()
    {
        return "Successfully match against a model with a negated specifier";
    }
    bool run()
    {
        Simplex simplex = Simplex(model);
        PL_ASSERT_TRUE(simplex.match(input_pass_one));
        PL_ASSERT_TRUE(simplex.match(input_pass_two));
        PL_ASSERT_FALSE(simplex.match(input_fail));
        return true;
    }

    ~TestMatchNot(){}
};

// TODO: m specifier (math)

// TODO: o specifier (math operator)

// TODO: Set

// TODO:  Literal set

// TODO: Group

// TODO: Line beginning/end

// TODO: Number or Range

class TestSuite_Basic : public TestSuite
{
public:
    TestSuite_Basic() = default;
    void load_tests();
    testdoc_t get_title()
    {
        return "SIMPLExpress: Basic Sanity Tests";
    }
    ~TestSuite_Basic()
    {}
};

#endif //SIMPLEXPRESS_BASIC_TESTS_HPP