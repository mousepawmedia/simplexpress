#include "simplexpress/lex_test.hpp"

void TestSuite_Lexer::load_tests()
{
	register_test("X-tB0301", new TestLexer());
	register_test("X-tB0302", new TestLexerSnag());
	register_test("X-tB0303", new TestLexerStatic());

}