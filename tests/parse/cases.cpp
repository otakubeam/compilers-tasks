#include <parse/parser.hpp>

// Finally,
#include <catch2/catch.hpp>

//////////////////////////////////////////////////////////////////////

TEST_CASE("Parser: Just works", "[parser]") {
  char stream[] = "1 - 2";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};

  auto expr = p.ParseExpression();
  REQUIRE(typeid(*expr) == typeid(BinaryExpression));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Parser: Booleans", "[parser]") {
  char stream[] = "!true";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};

  auto expr = p.ParseExpression();
  REQUIRE(typeid(*expr) == typeid(UnaryExpression));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Variable declaration", "[parser]") {
  char stream[] = "var x = 5;";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};

  auto stmt = p.ParseStatement();
  REQUIRE(typeid(*stmt) == typeid(VarDeclStatement));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Leading minus", "[parser]") {
  char stream[] = "- 1 - 2";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};

  auto expr = p.ParseExpression();
  REQUIRE(typeid(*expr) == typeid(BinaryExpression));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("No left bracket", "[parser]") {
  char stream[] = "1 - (1 + 2";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};
  CHECK_THROWS(p.ParseExpression());
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("No braced expression", "[parser]") {
  char stream[] = "()";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};
  CHECK_THROWS(p.ParseExpression());
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Parse string literal", "[parser]") {
  char stream[] = " \"a\" + \"b\" ";
  //                -----   -----
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};
  CHECK_NOTHROW(p.ParseExpression());
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Parse string literal (II)", "[parser]") {
  char stream[] = "\"ab\"";
  std::stringstream source{stream};
  Parser p{lex::Lexer{source}};

  auto expr = p.ParseExpression();
  REQUIRE(typeid(*expr) == typeid(LiteralExpression));
}

//////////////////////////////////////////////////////////////////////

TEST_CASE("Variable usage", "[parser]") {
  std::stringstream source("var a = 5; a");

  Parser p{lex::Lexer{source}};
  auto stmt = p.ParseStatement();
  REQUIRE(typeid(*stmt) == typeid(VarDeclStatement));

  auto expr = p.ParseExpression();
  REQUIRE(typeid(*expr) == typeid(VarAccessExpression));
}

//////////////////////////////////////////////////////////////////////
