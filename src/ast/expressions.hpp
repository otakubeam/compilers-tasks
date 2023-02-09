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

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

// Binary arithmetic: + - / *

class BinaryExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class UnaryExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class FnCallExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class BlockExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class IfExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class LiteralExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class VarAccessExpression : public LvalueExpression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////

class ReturnExpression : public Expression {
 public:
  // Constructor

  virtual void Accept(Visitor* /*visitor*/) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // TODO: fields, helpers, etc...
};

//////////////////////////////////////////////////////////////////////
