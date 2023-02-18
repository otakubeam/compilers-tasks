#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseExpression() {
  return ParseComparison();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseKeywordExpresssion() {
  if (auto return_statement = ParseReturnStatement()) {
    return return_statement;
  }

  if (auto yield_statement = ParseYieldStatement()) {
    return yield_statement;
  }

  if (auto if_expr = ParseIfExpression()) {
    return if_expr;
  }

  if (auto match_expr = ParseMatchExpression()) {
    return match_expr;
  }

  if (auto new_expr = ParseNewExpression()) {
    return new_expr;
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseDeref() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseAddressof() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseIfExpression() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseMatchExpression() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseNewExpression() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBlockExpression() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseComparison() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBinary() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseUnary() {
  std::abort();  // Your code goes here
}

///////////////////////////////////////////////////////////////////

// Assume lex::TokenType::ARROW has already been parsed
Expression* Parser::ParseIndirectFieldAccess(Expression* expr) {
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseFieldAccess(Expression* expr) {
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseIndexingExpression(Expression* expr) {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseFnCallExpression(Expression* expr, lex::Token id) {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseFnCallUnnamed(Expression* expr) {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParsePostfixExpressions() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParsePrimary() {
  // Try parsing grouping first

  // > Your code goes here

  // Then keyword expressions

  // > Your code goes here

  // Then all the base cases: IDENT, INT, TRUE, FALSE, ETC...

  // > Your code goes here

  FMT_ASSERT(false, "Unreachable!");
}

////////////////////////////////////////////////////////////////////

// var t = {.field = 3, .bar = true,};
Expression* Parser::ParseCompoundInitializer(lex::Token curly) {
  std::abort();
}

// Short-hand notation: .<Tag> <Expr>
// e.g: `.some 5` which is the same as `{ .some = 5 }`
Expression* Parser::ParseSignleFieldCompound() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseReturnStatement() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseYieldStatement() {
  std::abort();
}

///////////////////////////////////////////////////////////////////
