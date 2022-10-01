#pragma once

#include <ast/syntax_tree.hpp>

#include <types/type.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Expression : public TreeNode {
 public:
  virtual void Accept(Visitor*){};

  virtual types::Type* GetType() {
    return nullptr;
  }
};

//////////////////////////////////////////////////////////////////////

// Identifier, Named entity
class LvalueExpression : public Expression {
 public:
  virtual int GetAddress() = 0;

  virtual bool IsDirect() {
    // True for compile-time expressions
    // But not for pointers
    return true;
  }
};

//////////////////////////////////////////////////////////////////////

// BinaryExpression (== < >) BinaryExpression
class ComparisonExpression : public Expression {
 public:
  ComparisonExpression(Expression* left, lex::Token op, Expression* right)
      : left_{left}, operator_(op), right_{right} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitComparison(this);
  }

  virtual lex::Location GetLocation() override {
    return operator_.location;
  }

  Expression* left_;
  lex::Token operator_;
  Expression* right_;
};

//////////////////////////////////////////////////////////////////////

// TODO: separate into BinaryFactorExpression (/ and *)
//       and BinaryTermExpression (+ and -)

// UnaryExpression (+ - ) UnaryExpression
class BinaryExpression : public Expression {
 public:
  BinaryExpression(Expression* left, lex::Token op, Expression* right)
      : left_{left}, operator_(op), right_{right} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBinary(this);
  }

  virtual lex::Location GetLocation() override {
    return operator_.location;
  }

  Expression* left_;
  lex::Token operator_;
  Expression* right_;
};

//////////////////////////////////////////////////////////////////////

class UnaryExpression : public Expression {
 public:
  UnaryExpression(lex::Token op, Expression* operand)
      : operator_(op), operand_{operand} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitUnary(this);
  }

  virtual lex::Location GetLocation() override {
    return operator_.location;
  }

  lex::Token operator_;
  Expression* operand_;
};

//////////////////////////////////////////////////////////////////////

class LiteralExpression : public Expression {
 public:
  LiteralExpression(lex::Token token) : token_{token} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitLiteral(this);
  }

  virtual lex::Location GetLocation() override {
    return token_.location;
  }

  lex::Token token_;

  types::Type* type_ = nullptr;
};

//////////////////////////////////////////////////////////////////////

class VarAccessExpression : public LvalueExpression {
 public:
  VarAccessExpression(lex::Token name) : name_{name} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarAccess(this);
  }

  virtual int GetAddress() override {
    return address_;
  }

  std::string GetName() {
    return name_.GetName();
  }

  virtual lex::Location GetLocation() override {
    return name_.location;
  }

  lex::Token name_;

  types::Type* type_ = nullptr;

  int address_ = 0;
};

//////////////////////////////////////////////////////////////////////
