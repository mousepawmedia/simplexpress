#include "simplexpress/unit_parser_test.hpp"

void TestSuite_UnitParser::load_tests()
{
	register_test("X-tB0100", new TestCharacterParser());
	register_test("X-tB0101", new TestLiteralParser());
	register_test("X-tB0102", new TestSpecifierParser());
	register_test("X-tB0103", new TestModifierParser());
	register_test("X-tB0104", new TestVariousUnits());
	register_test("X-tB0105", new TestDigitsParser());
	register_test("X-tB0106", new TestOperatorParser());
	register_test("X-tB0107", new TestAlphanumericParser());
}