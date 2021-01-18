/** Snag Tests (SIMPLEXpress)
 * Version: 0.1
 *
 * Tests for functionality related to the Simplex snag function.
 *
 * Author(s): Anna R. Dunster
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

#ifndef SIMPLEXPRESS_SNAG_TESTS_HPP
#define SIMPLEXPRESS_SNAG_TESTS_HPP

#include <type_traits>

#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"
#include "simplexpress/simplex.hpp"

// X-sB02 //

// X-tB0200
class TestSingleUnitSnag : public Test
{
	onestring model = "~l+/";
	onestring input_one = "steve";
	onestring snag_one = "steve";
	onestring input_fail_one = "";
	onestring input_fail_two = "12345";

public:
	TestSingleUnitSnag() = default;

	testdoc_t get_title() override { return "Basic Snag Test"; }

	testdoc_t get_docs() override
	{
		return "Testing that a single unit Snag model works correctly";
	}
	bool run() override
	{
		// Correct contents and length on positive match
		FlexArray<onestring> snag_array1 = Simplex::snag(input_one, model);
		PL_ASSERT_EQUAL(snag_array1.at(0), snag_one);
		PL_ASSERT_TRUE(snag_array1.length() == 1);
		// Empty array on negative match
		FlexArray<onestring> snag_array2 = Simplex::snag(input_fail_one, model);
		PL_ASSERT_TRUE(snag_array2.length() == 0);
		FlexArray<onestring> snag_array3 = Simplex::snag(input_fail_two, model);
		PL_ASSERT_TRUE(snag_array3.length() == 0);
		return true;
	}

	~TestSingleUnitSnag() = default;
};

// X-tB0201
class TestMultiUnitSnag : public Test
{
	onestring model = "~l+/^d*/";
	onestring input_one = "steve";
	onestring input_two = "steve12345";
	onestring snag_one = "steve";
	onestring input_fail_one = "";
	onestring input_fail_two = "12345";

public:
	TestMultiUnitSnag() = default;

	testdoc_t get_title() override { return "Multi Unit Snag Test"; }

	testdoc_t get_docs() override
	{
		return "Testing that a multi unit Snag model works correctly";
	}
	bool run() override
	{
		// Correct contents and length on positive match
		FlexArray<onestring> snag_array1 = Simplex::snag(input_one, model);
		PL_ASSERT_EQUAL(snag_array1.at(0), snag_one);
		PL_ASSERT_TRUE(snag_array1.length() == 1);
		FlexArray<onestring> snag_array2 = Simplex::snag(input_two, model);
		PL_ASSERT_EQUAL(snag_array2.at(0), snag_one);
		PL_ASSERT_TRUE(snag_array2.length() == 1);
		// Empty array on negative match
		FlexArray<onestring> snag_array3 = Simplex::snag(input_fail_one, model);
		PL_ASSERT_TRUE(snag_array3.length() == 0);
		FlexArray<onestring> snag_array4 = Simplex::snag(input_fail_two, model);
		PL_ASSERT_TRUE(snag_array4.length() == 0);
		return true;
	}

	~TestMultiUnitSnag() = default;
};

// X-tB0202
class TestMultipleSnags : public Test
{
	onestring model = "~l+/~d*/~o+/";
	onestring input_one = "steve12345++++";
	onestring input_two = "steve++++";
	onestring snag_one = "steve";
	onestring snag_two = "12345";
	onestring snag_two_alt = "";
	onestring snag_three = "++++";
	onestring input_fail_one = "";
	onestring input_fail_two = "12345";
	onestring input_fail_three = "steve12345";

public:
	TestMultipleSnags() = default;

	testdoc_t get_title() override { return "Multiple Snag Test"; }

	testdoc_t get_docs() override
	{
		return "Testing that a snag model that will grab multiple snags works "
			   "correctly";
	}
	bool run() override
	{
		// Correct contents and length on positive match
		FlexArray<onestring> snag_array1 = Simplex::snag(input_one, model);
		PL_ASSERT_TRUE(snag_array1.length() == 3);
		PL_ASSERT_EQUAL(snag_array1.at(0), snag_one);
		PL_ASSERT_EQUAL(snag_array1.at(1), snag_two);
		PL_ASSERT_EQUAL(snag_array1.at(2), snag_three);
		FlexArray<onestring> snag_array2 = Simplex::snag(input_two, model);
		PL_ASSERT_TRUE(snag_array2.length() == 3);
		PL_ASSERT_EQUAL(snag_array2.at(0), snag_one);
		PL_ASSERT_EQUAL(snag_array2.at(1), snag_two_alt);
		PL_ASSERT_EQUAL(snag_array2.at(2), snag_three);
		// Empty array on negative match
		FlexArray<onestring> snag_array3 = Simplex::snag(input_fail_one, model);
		PL_ASSERT_TRUE(snag_array3.length() == 0);
		FlexArray<onestring> snag_array4 = Simplex::snag(input_fail_two, model);
		PL_ASSERT_TRUE(snag_array4.length() == 0);
		FlexArray<onestring> snag_array5 =
			Simplex::snag(input_fail_three, model);
		PL_ASSERT_TRUE(snag_array5.length() == 0);
		return true;
	}

	~TestMultipleSnags() = default;
};

// X-tB0203
class TestMemberSnag : public Test
{
	onestring model = "~l+/";
	onestring input_one = "steve";
	onestring snag_one = "steve";
	onestring snag_two = "fred";
	onestring input_fail_one = "";
	onestring input_fail_two = "12345";

public:
	TestMemberSnag() = default;

	testdoc_t get_title() override { return "Member Snag Test"; }

	testdoc_t get_docs() override
	{
		return "Testing a single unit Snag Simplex works correctly as a member "
			   "function with various inputs";
	}
	bool run() override
	{
		Simplex simplex(model);
		// Correct contents and length on positive match
		FlexArray<onestring> snag_array1 = simplex.snag(input_one, model);
		PL_ASSERT_EQUAL(snag_array1.at(0), snag_one);
		PL_ASSERT_TRUE(snag_array1.length() == 1);
		FlexArray<onestring> snag_array2 = simplex.snag("fred", model);
		PL_ASSERT_EQUAL(snag_array2.at(0), snag_two);
		PL_ASSERT_TRUE(snag_array2.length() == 1);
		// Empty array on negative match
		FlexArray<onestring> snag_array3 = simplex.snag(input_fail_one, model);
		PL_ASSERT_TRUE(snag_array3.length() == 0);
		FlexArray<onestring> snag_array4 = simplex.snag(input_fail_two, model);
		PL_ASSERT_TRUE(snag_array4.length() == 0);
		FlexArray<onestring> snag_array5 = simplex.snag("893745", model);
		PL_ASSERT_TRUE(snag_array5.length() == 0);
		return true;
	}

	~TestMemberSnag() = default;
};

class TestSuite_Snag : public TestSuite
{
public:
	TestSuite_Snag() = default;
	void load_tests() override;
	testdoc_t get_title() override
	{
		return "SIMPLExpress: Simplex Snag Tests";
	}
	~TestSuite_Snag() = default;
};

#endif  // SIMPLEXPRESS_SNAG_TESTS_HPP