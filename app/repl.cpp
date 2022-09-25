#include <lex/token_type.hpp>
#include <lex/errors.hpp>
#include <lex/lexer.hpp>

#include <fmt/color.h>

#include <iostream>

int main() {
  lex::Lexer lexer(std::cin);

  while (true) try {
      auto token = lexer.GetNextToken();

      // Try also to get seminfo from numbers, identifiers, strings

      fmt::print("The token type is {}\n", lex::FormatTokenType(token.type));
    } catch (lex::LexError& error) {
      fmt::print("{}", error.what());
      return 0;
    }
}
