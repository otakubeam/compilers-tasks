#include <parse/parse_error.hpp>
#include <parse/parser.hpp>

#include <lex/errors.hpp>

#include <fmt/color.h>

#include <iostream>

int main() {
  Parser parser{lex::Lexer(std::cin)};

  while (true) try {
      auto stmt = parser.ParseStatement();
      fmt::print("Statement location is {}", stmt->GetLocation().Format());
    } catch (lex::LexError& error) {
      fmt::print("{}", error.what());
      return 0;
    } catch (parse::errors::ParseError& error) {
      fmt::print("{}", error.what());
      return 0;
    }
}
