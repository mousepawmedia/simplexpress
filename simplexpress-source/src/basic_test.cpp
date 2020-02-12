#include "simplexpress/basic_test.hpp"

void TestSuite_Basic::load_tests()
{
    register_test("S-tB0000", new TestConstructASCIISimplex());
    register_test("S-tB0001", new TestMatchSingleUnitLiteral());
    register_test("S-tB0002", new TestMatchSingleUnitSpecifierAlphanumeric());
    register_test("S-tB0003", new TestMatchSingleUnitSpecifierDigit());
    register_test("S-tB0004", new TestMatchSingleUnitSpecifierLatin());
    register_test("S-tB0005", new TestMatchSingleUnitSpecifierNewline());
    register_test("S-tB0006", new TestMatchSingleUnitSpecifierPunctuation());
    register_test("S-tB0007", new TestMatchSingleUnitSpecifierCarriageReturn());
    register_test("S-tB0008", new TestMatchSingleUnitSpecifierLiteralSpace());
    register_test("S-tB0009", new TestMatchSingleUnitSpecifierTab());
    register_test("S-tB0010", new TestMatchSingleUnitSpecifierWhitespace());
    register_test("S-tB0011", new TestMatchMultiUnitLiterals());
    register_test("S-tB0012", new TestMatchMultiUnitLiteralSpecifier());
    register_test("S-tB0013", new TestMatchMultiUnitSpecifiers());
    register_test("S-tB0014", new TestMatchSpecifierMultiplier());
    register_test("S-tB0015", new TestMatchSpecifierOptional());
    register_test("S-tB0016", new TestMatchSpecifierOptionalMultiple());
    register_test("S-tB0017", new TestMatchAny());
    register_test("S-tB0018", new TestMatchNot());
}