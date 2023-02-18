#pragma once

#include <ast/declarations.hpp>

#include <lex/lexer.hpp>

class Parser {
 public:
  Parser(lex::Lexer& l);

  ///////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////

  Statement* ParseStatement();

  Statement* ParseExprStatement();
  AssignmentStatement* ParseAssignment(LvalueExpression* target);

  ////////////////////////////////////////////////////////////////////

  Declaration* ParseDeclaration();

  Declaration* ParsePrototype();
  FunDeclStatement* ParseFunPrototype();
  FunDeclStatement* ParseFunDeclStatement();
  VarDeclStatement* ParseVarDeclStatement();
  FunDeclStatement* ParseFunDeclarationStandalone();

  ////////////////////////////////////////////////////////////////////

  Expression* ParseExpression();

  Expression* ParseKeywordExpresssion();

  Expression* ParseReturnStatement();
  Expression* ParseYieldStatement();
  Expression* ParseIfExpression();
  Expression* ParseMatchExpression();
  Expression* ParseNewExpression();

  Expression* ParseBlockExpression();

  Expression* ParseComparison();
  Expression* ParseBinary();

  Expression* ParseUnary();
  Expression* ParseDeref();
  Expression* ParseAddressof();

  // Precedence 1
  Expression* ParsePostfixExpressions();
  Expression* ParseFieldAccess(Expression* expr);
  Expression* ParseIndirectFieldAccess(Expression* expr);
  Expression* ParseIndexingExpression(Expression* expr);
  Expression* ParseFnCallUnnamed(Expression* expr);
  Expression* ParseFnCallExpression(Expression* expr, lex::Token id);

  Expression* ParseCompoundInitializer(lex::Token id);
  Expression* ParseSignleFieldCompound();
  Expression* ParsePrimary();

  ////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////

 private:
  std::string FormatLocation();

  auto ParseCSV() -> std::vector<Expression*>;
  auto ParseFormals() -> std::vector<lex::Token>;

  bool Matches(lex::TokenType type);
  void Consume(lex::TokenType type);
  bool MatchesComparisonSign(lex::TokenType type);

 private:
  lex::Lexer& lexer_;
};
