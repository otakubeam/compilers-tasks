#include <lex/lexer.hpp>

namespace lex {

Lexer::Lexer(std::istream& source) : scanner_{source} {
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetNextToken() {
  SkipWhitespace();

  SkipComments();

  if (auto op = MatchOperators()) {
    return *op;
  }

  if (auto lit = MatchLiterls()) {
    return *lit;
  }

  if (auto word = MatchWords()) {
    return *word;
  }

  FMT_ASSERT(false, "Could not match any token\n");
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetPreviousToken() {
  return prev_;
}

////////////////////////////////////////////////////////////////////

void Lexer::Advance() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

bool Lexer::Matches(lex::TokenType) {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

Token Lexer::Peek() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

bool IsWhitespace(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void Lexer::SkipWhitespace() {
  while (IsWhitespace(scanner_.CurrentSymbol())) {
    scanner_.MoveRight();
  }
}

////////////////////////////////////////////////////////////////////

void Lexer::SkipComments() {
  while (scanner_.CurrentSymbol() == '#') {
    scanner_.MoveNextLine();
    SkipWhitespace();
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchOperators() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

std::optional<TokenType> Lexer::MatchOperator() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchLiterls() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchNumericLiteral() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchStringLiteral() {
  std::abort();  // Your code goes here
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchWords() {
  std::abort();  // Your code goes here
}

}  // namespace lex
