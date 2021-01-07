#include "simplexpress/simplex_test.hpp"

void TestSuite_Basic::load_tests()
{
	register_test("X-tB0000", new TestConstructASCIISimplex());
	register_test("X-tB0001", new TestMatchSingleUnitLiteral());
	register_test("X-tB0002", new TestMatchSingleUnitSpecifierAlphanumeric());
	register_test("X-tB0003", new TestMatchSingleUnitSpecifierDigit());
	register_test("X-tB0004", new TestMatchSingleUnitSpecifierLatin());
	register_test("X-tB0005", new TestMatchSingleUnitSpecifierNewline());
	register_test("X-tB0006", new TestMatchSingleUnitSpecifierPunctuation());
	register_test("X-tB0007", new TestMatchSingleUnitSpecifierCarriageReturn());
	register_test("X-tB0008", new TestMatchSingleUnitSpecifierLiteralSpace());
	register_test("X-tB0009", new TestMatchSingleUnitSpecifierTab());
	register_test("X-tB0010", new TestMatchSingleUnitSpecifierWhitespace());
	register_test("X-tB0011", new TestMatchMultiUnitLiterals());
	register_test("X-tB0012", new TestMatchMultiUnitLiteralSpecifier());
	register_test("X-tB0013", new TestMatchMultiUnitSpecifiers());
	register_test("X-tB0014", new TestMatchSpecifierMultiplier());
	register_test("X-tB0015", new TestMatchSpecifierOptional());
	register_test("X-tB0016", new TestMatchSpecifierOptionalMultiple());
	register_test("X-tB0017", new TestMatchAny());
	register_test("X-tB0018", new TestMatchNot());
	register_test("X-tB0019", new TestMatchWithSnag());
	register_test("X-tB0020", new TestNegativeMultiple());
	register_test("X-tB0021", new TestLiteralModifiers());
	register_test("X-tB0050", new TestStaticMatch());
	register_test("X-tB0051", new TestGreedyLogic());
}