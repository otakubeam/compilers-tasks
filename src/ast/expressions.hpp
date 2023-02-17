#pragma once

#include <ast/syntax_tree.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Expression : public TreeNode {
 public:
  virtual void Accept(Visitor*) = 0;

  // Later

  // virtual types::Type* GetType() = 0;
};

//////////////////////////////////////////////////////////////////////

// Assignable entity

class LvalueExpression : public Expression {};

//////////////////////////////////////////////////////////////////////

class ComparisonExpression : public Expression {
 public:
  // Constructor
  ComparisonExpression(Expression* lhs, Expression* rhs, lex::Token operator): lhs(lhs), rhs(rhs), operator(operator) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitComparison(this);
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
  Expression* lhs;
  Expression* rhs;
  lex::Token operator;
};

//////////////////////////////////////////////////////////////////////

// Binary arithmetic: + - / *

class BinaryExpression : public Expression {
 public:
  // Constructor
  BinaryExpression(LvalueExpression* left, Expression* right, lex::Token* operator)
  : left_(left), right_(right), operator_(operator) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBinaryExpression(this);
  }

  virtual lex::Location GetLocation() override {
    operator_->GetLocation();
  }

  LvalueExpression* left_;
  Expression* right_;

  lex::Token* operator_;
};

//////////////////////////////////////////////////////////////////////

class UnaryExpression : public Expression {
 public:
  // Constructor
  UnaryExpression(Expression *expression, lex::Token *oper) {
    expression_ = expression;
    operator_ = oper;
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitUnary(this);
  }

  virtual lex::Location GetLocation() override {
    return operator_->location;
  }

  // TODO: fields, helpers, etc...
  Expression *expression_;
  lex::Token *operator_;
};

//////////////////////////////////////////////////////////////////////

class FnCallExpression : public Expression {
 public:
  // Constructor
  template<typename Container>
  FnCallExpression(const lex::Token &name, const Container &args)
    : name_(name),
      args_(args.begin(), args.end())
  {}
  virtual void Accept(Visitor* visitor) override {
    visitor->VisitFnCall(*this);
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }
  lex::Token name_;
  std::vector<Expression*> args_;
 private:
  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class BlockExpression : public Expression {
 public:
  BlockExpression(std::vector<Statement *> body) :
    body{std::move(body)} {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBlockExpression(this);
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  std::vector<Statement *> body;
};

//////////////////////////////////////////////////////////////////////

class IfExpression : public Expression {
 public:
  IfExpression(Expression *condition, Expression* then_branch, Expression* else_branch = nullptr) :
        condition_{condition}, then_branch_{then_branch}, else_branch_{else_branch} {}

  virtual void Accept(Visitor* visitor) override {
    return visitor->VisitIfExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return condition_->GetLocation();
  }

  Expression* condition_;
  Expression* then_branch_;
  Expression* else_branch_;
};

//////////////////////////////////////////////////////////////////////

class LiteralExpression : public Expression {
 public:
  explicit LiteralExpression(lex::Token name): name_{name} {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitLiteral(this);
  }

  virtual lex::Location GetLocation() override {
    return name_.location;
  }

   lex::Token name_;
};

//////////////////////////////////////////////////////////////////////

class VarAccessExpression : public LvalueExpression {
 public:
  // Constructor
  VarAccessExpression(lex::Token* var) : var(var_) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarAccessExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return var_->GetLocation();
  }

  // TODO: fields, helpers, etc...
  lex::Token* var_;
};

//////////////////////////////////////////////////////////////////////

class ReturnExpression : public Expression {
 public:
  explicit ReturnExpression(Expression* expr): expr_{expr} {}

  void Accept(Visitor* visitor) override {
    visitor->VisitReturnExpression(this);
  }

  lex::Location GetLocation() override {
    return expr_->GetLocation();
  }

  Expression* expr_;
};

//////////////////////////////////////////////////////////////////////
