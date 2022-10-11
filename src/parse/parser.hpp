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
  ReturnStatement* ParseReturnStatement();
  VarDeclStatement* ParseVarDeclStatement();
  AssignmentStatement* ParseAssignment(LvalueExpression* target);

  ////////////////////////////////////////////////////////////////////

  Expression* ParseExpression();

  Expression* ParseIfExpression();
  Expression* ParseBlockExpression();

  // You can remove the id and use GetPreviousToken
  Expression* ParseFnCallExpression(lex::Token id); 

  Expression* ParseComparison();
  Expression* ParseBinary();
  Expression* ParseUnary();
  Expression* ParsePrimary();

  ////////////////////////////////////////////////////////////////////

  types::Type* ParseType();
  types::Type* ParseFunctionType();
  types::Type* ParseStructType();

  ////////////////////////////////////////////////////////////////////

 private:
  // Used for parsing parameters of functions
  //
  // Try to implement passing lambdas as callbacks
  //
  // template <typename F> (?)
  auto ParseCSV() -> std::vector<Expression*>;

  bool Matches(lex::TokenType type);
  void Consume(lex::TokenType type);

  std::string FormatLocation();

 private:
  lex::Lexer lexer_;
};
