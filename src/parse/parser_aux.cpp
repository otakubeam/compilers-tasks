#include <parse/parse_error.hpp>
#include <parse/parser.hpp>

Parser::Parser(lex::Lexer& l) : lexer_{l} {
}

