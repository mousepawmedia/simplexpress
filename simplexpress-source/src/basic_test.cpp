#include "simplexpress/basic_test.hpp"

void TestSuite_Basic::load_tests()
{
    register_test("S-tB0000", new TestConstructShortASCIISimplex());
    register_test("S-tB0001", new TestConstructLongASCIISimplex());
}