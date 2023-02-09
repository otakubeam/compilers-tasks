#pragma once

#include <ast/syntax_tree.hpp>
#include <ast/expressions.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Statement : public TreeNode {
 public:
  virtual void Accept(Visitor* /* visitor */){};
};

//////////////////////////////////////////////////////////////////////

class ExprStatement : public Statement {
 public:
  ExprStatement(Expression* expr) : expr_{expr} {
  }

  virtual void Accept(Visitor*) override {
    // visitor->VisitExprStatement(this);
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  Expression* expr_;
};

//////////////////////////////////////////////////////////////////////

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement() {
  }

  virtual void Accept(Visitor*) override {
    std::abort();
  }

  virtual lex::Location GetLocation() override {
    std::abort();
  }

  // ???
};

//////////////////////////////////////////////////////////////////////
