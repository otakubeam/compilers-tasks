#include <ast/visitors/print_visitor.hpp>

#include <fmt/color.h>

#include <iostream>

int main() {

  Expression* a = new LiteralExpression{lex::Token{lex::TokenType::NUMBER, lex::Location{}, 1}};
  Expression* b = new LiteralExpression{lex::Token{lex::TokenType::NUMBER, lex::Location{}, 2}};

  lex::Token plus{lex::TokenType::PLUS, lex::Location{}};
  Expression* root = new BinaryExpression(a, b, &plus);

  return 0;
}
