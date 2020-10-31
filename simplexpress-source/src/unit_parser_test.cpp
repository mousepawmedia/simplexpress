#include "simplexpress/unit_parser_test.hpp"

void TestSuite_UnitParser::load_tests()
{
	register_test("S-tB0100", new TestCharacterParser());
	register_test("S-tB0101", new TestLiteralParser());
	register_test("S-tB0102", new TestSpecifierParser());
	register_test("S-tB0103", new TestModifierParser());
	register_test("S-tB0104", new TestVariousUnits());
	register_test("S-tB0105", new TestDigitsParser());
	register_test("S-tB0106", new TestOperatorParser());
	register_test("S-tB0107", new TestAlphanumericParser());
}