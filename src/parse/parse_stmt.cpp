#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

///////////////////////////////////////////////////////////////////

Statement* Parser::ParseStatement() {
  if (auto var_declaration = ParseVarDeclStatement()) {
    return var_declaration;
  }

  if (auto expr_statement = ParseExprStatement()) {
    return expr_statement;
  }

  // TODO: while, function declaration, struct declaration
  //
  // NOTE: if () {} else {} and block ({...})
  // could be either expressions or statements

  FMT_ASSERT(false, "Unreachable!");
}

///////////////////////////////////////////////////////////////////

VarDeclStatement* Parser::ParseVarDeclStatement() {
  if (!Matches(lex::TokenType::VAR)) {
    return nullptr;
  }

  // 1. Get a name to assign to

  Consume(lex::TokenType::IDENTIFIER);

  auto lvalue = new VarAccessExpression{lexer_.GetPreviousToken()};

  // 2. Get an expression to assign to

  Consume(lex::TokenType::ASSIGN);

  auto value = ParseExpression();

  Consume(lex::TokenType::SEMICOLUMN);

  return new VarDeclStatement{lvalue, value};
}

///////////////////////////////////////////////////////////////////

Statement* Parser::ParseExprStatement() {
  auto expr = ParseExpression();

  if (Matches(lex::TokenType::ASSIGN)) {
    // Check if the expression is assignable
    if (auto target = dynamic_cast<LvalueExpression*>(expr)) {
      return ParseAssignment(target);
    }

    throw parse::errors::ParseNonLvalueError{FormatLocation()};
  }

  Consume(lex::TokenType::SEMICOLUMN);

  return new ExprStatement{expr};
}

///////////////////////////////////////////////////////////////////

AssignmentStatement* Parser::ParseAssignment(LvalueExpression* target) {
  auto assignment_loc = lexer_.GetPreviousToken();
  auto value = ParseExpression();
  Consume(lex::TokenType::SEMICOLUMN);
  return new AssignmentStatement{assignment_loc, target, value};
}
