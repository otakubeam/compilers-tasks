#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

#include <types/repr/builtins.hpp>
#include <types/repr/fn_type.hpp>

///////////////////////////////////////////////////////////////////

types::Type* Parser::ParseType() {
  types::Type* result = nullptr;

  switch (lexer_.Peek().type) {
    case lex::TokenType::TY_INT:
      result = &types::builtin_int;
      break;

    case lex::TokenType::TY_BOOL:
      result = &types::builtin_bool;
      break;

    case lex::TokenType::TY_STRING:
      result = &types::builtin_string;
      break;

    case lex::TokenType::TY_UNIT:
      result = &types::builtin_unit;
      break;

    // Example: (Int, Bool) String
    case lex::TokenType::LEFT_BRACE:
      return ParseFunctionType();

    default:
      return nullptr;
  }

  // Advance for simple types
  lexer_.Advance();
  return result;
}

///////////////////////////////////////////////////////////////////

types::Type* Parser::ParseFunctionType() {
  std::abort(); // Your code goes here
}

///////////////////////////////////////////////////////////////////
