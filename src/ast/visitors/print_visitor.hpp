#pragma once

#include <lex/token.hpp>
#include <ast/visitor.hpp>
#include <fmt/core.h>
#include <ast/expressions.hpp>

class PrintVisitor : public Visitor {
public:

  virtual void VisitLiteral(LiteralExpression* lit) override {
    indent();

    fmt::print("{}\n", lit->token_);
  }

  void VisitComparison(ComparisonExpression *expr) override {
    expr->lhs->Accept(this);
    fmt::print(lex::FormatTokenType(expr->operator));
    expr->rhs->Accept(this);
  }

  virtual VisitBinaryExpression(BinaryExpression* expr) override {
    ident();
    fmt::print("{}", FormatTokenType(expr->operator_));
    
    fmt::print("Left:\n");
    
    ++tabs;
    expr->left_->Accept(this);
    --tabs;

    ident();
    fmt::print("\n");
    fmt::print("Right:\n");
    
    ++tabs;
    expr->right_->Accept(this);
    --tabs;
  }

  virtual void VisitBlockExpression(BlockExpression *expr) override {
    indent();
    fmt::print("{\n")

    ++tabs;
    for (Statement *child : expr->body) {
      child->Accept(this);
    }
    --tabs;

    indent();
    fmt::print("}\n");
  }
  
  virtual void VisitIfExpression(IfExpression *expr) override {
    ident();
    fmt::print("IF: condition:\n");
    tabs++;
    expr->condition_->Accept(this);
    tabs--;
    ident();
    fmt::print("IF: then branch:\n");
    tabs++;
    expr->then_branch_->Accept(this);
    tabs--;
    ident();
    fmt::print("IF: else branch:\n");
    tabs++;
    expr->expr_branch_->Accept(this);
    tabs--;
  }

  virtual void VisitReturnExpression(IfExpression *expr) override {
    ident();
    fmt::print("RETURN:\n");
    tabs++;
    expr->expr_->Accept(this);
    tabs--;
  }

  virtual void VisitFnCall(FnCallExpression *expr) override {
    ident();
    fmt::print("call {}(\n", expr->name_.identifier_name);
    ++tabs;
    for (Expression *arg : expr->args_) {
      arg->Accept(*this);
      fmt::print(",\n");
    }
    --tabs;
    fmt::print(");\n");
  }

  virtual void VisitUnary(UnaryExpression *expr) override {
    indent();

    expr->expression_->Accept(this);
    fmt::print("{}\n", lit->token_);
  }

  virtual void VisitVarAccessExpression(VarAccessExpression* expr) override {
    ident();

    fmt::print("{}\n", expr->var_->GetName());
  }

private:
  size_t tabs = 0;

  void indent() const {
    for (size_t i = 0; i < tabs; ++i) {
        fmt::print("\t");    
    }
  }

};

// чпых!