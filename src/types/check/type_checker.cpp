#include <types/check/type_checker.hpp>

#include <types/check/type_error.hpp>

#include <types/repr/builtins.hpp>

#include <ast/expressions.hpp>
#include <ast/statements.hpp>

namespace types::check {

TypeChecker::TypeChecker() {
  // Declare intrinsics
}

TypeChecker::~TypeChecker() = default;

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitAssignment(AssignmentStatement* node) {
  auto target_type = Eval(node->target_);
  auto value_type = Eval(node->value_);

  if (value_type->DiffersFrom(target_type)) {
    throw AssignmentError{node->GetLocation()};
  }
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitVarDecl(VarDeclStatement*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitFunDecl(FunDeclStatement*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitReturn(ReturnStatement*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitYield(YieldStatement*) {
  // TODO: throw up to closest match
  return_value = &builtin_unit;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitExprStatement(ExprStatement*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitComparison(ComparisonExpression* node) {
  if (!Eval(node->left_)) {
    throw ArithCmpError{node->GetLocation(), "left"};
  }

  if (!Eval(node->right_)) {
    throw ArithCmpError{node->GetLocation(), "right"};
  }

  return_value = &builtin_bool;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitBinary(BinaryExpression* node) {
  if (Eval(node->left_) != &builtin_int) {
    throw ArithAddError{node->GetLocation(), "left"};
  }

  if (Eval(node->right_) != &builtin_int) {
    throw ArithAddError{node->GetLocation(), "right"};
  }

  return_value = &builtin_int;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitUnary(UnaryExpression* node) {
  Type* expected_type = nullptr;
  auto operand_type = Eval(node->operand_);

  switch (node->operator_.type) {
    case lex::TokenType::NOT:
      expected_type = &builtin_bool;
      break;

    case lex::TokenType::MINUS:
      expected_type = &builtin_int;
      break;

    default:
      FMT_ASSERT(false, "Unreachable");
  }

  if (expected_type->DiffersFrom(operand_type)) {
    throw ArithNegateError{node->GetLocation()};
  }

  return_value = expected_type;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitIf(IfExpression* if_expr) {
  if (builtin_bool.DiffersFrom(Eval(if_expr->condition_))) {
    throw IfCondError{if_expr->GetLocation()};
  }

  auto true_type = Eval(if_expr->true_branch_);
  auto false_type = if_expr->false_branch_ ? Eval(if_expr->false_branch_)  //
                                           : &builtin_unit;
  if (true_type->DiffersFrom(false_type)) {
    throw IfArmsError{if_expr->GetLocation()};
  }

  return_value = true_type;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitBlock(BlockExpression*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitFnCall(FnCallExpression*) {
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitLiteral(LiteralExpression* node) {
  switch (node->token_.type) {
    case lex::TokenType::NUMBER:
      return_value = &builtin_int;
      break;

    case lex::TokenType::STRING:
      return_value = &builtin_string;
      break;

    case lex::TokenType::UNIT:
      return_value = &builtin_unit;
      break;

    case lex::TokenType::TRUE:
    case lex::TokenType::FALSE:
      return_value = &builtin_bool;
      break;

    default:
      FMT_ASSERT(false, "Typechecking unknown literal");
  }

  node->type_ = return_value;
}

////////////////////////////////////////////////////////////////////

void TypeChecker::VisitVarAccess(VarAccessExpression*) {
}

}  // namespace types::check
