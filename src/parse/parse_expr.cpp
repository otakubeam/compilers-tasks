#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseExpression() {
  return ParseComparison();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseIfExpression() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBlockExpression() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

// Assume non-empty
// Parse comma separated values
std::vector<Expression*> Parser::ParseCSV() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseFnCallExpression(lex::Token ) {
  std::abort();  // Your code goes here
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseComparison() {
  Expression* first = ParseBinary();

  auto token = lexer_.Peek();
  if (Matches(lex::TokenType::LT) || Matches(lex::TokenType::EQUALS)) {
    auto second = ParseBinary();
    first = new ComparisonExpression(first, token, second);
  }

  return first;
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBinary() {
  // 6.1.1. Ambiguity and the Parsing Game
  // https://craftinginterpreters.com/parsing-expressions.html
  FMT_ASSERT(false,
             "Unimplemented: separate into Multiplication/Division and "
             "Addition/Subtraction");
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseUnary() {
  auto token = lexer_.Peek();
  if (Matches(lex::TokenType::MINUS) || Matches(lex::TokenType::NOT)) {
    auto expr = ParsePrimary();
    return new UnaryExpression{token, expr};
  }

  return ParsePrimary();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParsePrimary() {
  // Try parsing grouping first

  if (Matches(lex::TokenType::LEFT_BRACE)) {
    auto expr = ParseExpression();
    Consume(lex::TokenType::RIGHT_BRACE);
    return expr;
  }

  // Then all the base cases

  auto token = lexer_.Peek();

  switch (token.type) {
    case lex::TokenType::NUMBER:
    case lex::TokenType::STRING:
    case lex::TokenType::FALSE:
    case lex::TokenType::TRUE:
    case lex::TokenType::UNIT:
      lexer_.Advance();
      return new LiteralExpression{token};

    case lex::TokenType::IDENTIFIER:
      Consume(lex::TokenType::IDENTIFIER);
      // Later there might be other cases
      return new VarAccessExpression{token};

    default: {
      // 6.3.3: Synchronizing a recursive descent parser
      // https://craftinginterpreters.com/parsing-expressions.html

      auto location = token.location.Format();
      throw parse::errors::ParsePrimaryError{location};
    }
  }

  FMT_ASSERT(false, "Unreachable!");
}

////////////////////////////////////////////////////////////////////
