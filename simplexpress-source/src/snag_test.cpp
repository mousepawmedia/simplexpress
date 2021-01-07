#include "simplexpress/snag_test.hpp"

void TestSuite_Snag::load_tests()
{
	register_test("X-tB0200", new TestSingleUnitSnag());
	register_test("X-tB0201", new TestMultiUnitSnag());
	register_test("X-tB0202", new TestMultipleSnags());
}
