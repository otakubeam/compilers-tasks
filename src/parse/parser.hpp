#pragma once

#include <ast/statements.hpp>

#include <lex/lexer.hpp>

class Parser {
 public:
  Parser(lex::Lexer l);

  ///////////////////////////////////////////////////////////////////

  Statement* ParseStatement();

  Statement* ParseExprStatement();
  FunDeclStatement* ParseFunDeclStatement();
  VarDeclStatement* ParseVarDeclStatement();
  AssignmentStatement* ParseAssignment(LvalueExpression* target);

  ////////////////////////////////////////////////////////////////////

  Expression* ParseExpression();

  Expression* ParseComparison();
  Expression* ParseBinary();
  Expression* ParseUnary();
  Expression* ParsePrimary();

  ////////////////////////////////////////////////////////////////////

 private:
  bool Matches(lex::TokenType type);
  void Consume(lex::TokenType type);

  std::string FormatLocation();

 private:
  lex::Lexer lexer_;
};
