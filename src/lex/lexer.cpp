#include <lex/lexer.hpp>

#include <lex/errors.hpp>

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

  throw LexError{"Could not match any token", scanner_.GetLocation()};
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetPreviousToken() {
  return prev_;
}

////////////////////////////////////////////////////////////////////

// Lazy loading of the next Token
void Lexer::Advance() {
  prev_ = peek_;

  if (!need_advance_) {
    need_advance_ = true;
  } else {
    peek_ = GetNextToken();
    need_advance_ = false;
  }
}

////////////////////////////////////////////////////////////////////

bool Lexer::Matches(lex::TokenType type) {
  if (Peek().type != type) {
    return false;
  }

  Advance();
  return true;
}

////////////////////////////////////////////////////////////////////

Token Lexer::Peek() {
  if (need_advance_) {
    Advance();
  }
  return peek_;
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
  // Your code goes here
  std::abort();
}

////////////////////////////////////////////////////////////////////

std::optional<TokenType> Lexer::MatchOperator() {
  // Your code goes here
  std::abort();
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchLiterls() {
  if (auto num_token = MatchNumericLiteral()) {
    return num_token;
  }

  if (auto string_token = MatchStringLiteral()) {
    return string_token;
  }

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchNumericLiteral() {
  // Your code goes here
  std::abort();
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchStringLiteral() {
  // Your code goes here
  std::abort();
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchWords() {
  // Your code goes here
  std::abort();
}

////////////////////////////////////////////////////////////////////

std::string Lexer::BufferWord() {
  std::string result;

  while (isalnum(scanner_.CurrentSymbol())) {
    result.push_back(scanner_.CurrentSymbol());
    scanner_.MoveRight();
  }

  return result;
}

}  // namespace lex
