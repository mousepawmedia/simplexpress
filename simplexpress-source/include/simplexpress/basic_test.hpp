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

class TestConstructShortASCIISimplex : public Test
{
    std::string model = "^l+/-^a+/-^d/.png^(24)?/";
    std::string input = "test.png";
public:
    TestConstructShortASCIISimplex() = default;

    testdoc_t get_title()
    {
        return "Construct short ASCII Simplex";
    }

    testdoc_t get_docs()
    {
        return "Successfully construct 8-char model Simplex from an ASCII model";
    }
    bool run()
    {
        Simplex simplex(model, input);
        return true;
    }

    ~TestConstructShortASCIISimplex(){}
};

class TestConstructLongASCIISimplex : public Test
{
    std::string model = "^l+/-^a+/-^d/.png^(24)?/";
    std::string input = "testname-one1-1.png";
public:
    TestConstructLongASCIISimplex() = default;

    testdoc_t get_title()
    {
        return "Construct long (>10 character) ASCII Simplex";
    }

    testdoc_t get_docs()
    {
        return "Successfully construct 20-char model Simplex from an ASCII model";
    }
    bool run()
    {
        Simplex simplex(model, input);
        return true;
    }

    ~TestConstructLongASCIISimplex(){}
};

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