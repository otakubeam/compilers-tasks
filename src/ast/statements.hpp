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

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitExprStatement(this);
  }

  virtual lex::Location GetLocation() override {
    return expr_->GetLocation();
  }

  Expression* expr_;
};

//////////////////////////////////////////////////////////////////////

class ReturnStatement : public Statement {
 public:
  ReturnStatement(lex::Token return_token, Expression* return_value)
      : return_token_{return_token}, return_value_{return_value} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitReturn(this);
  }

  virtual lex::Location GetLocation() override {
    return return_token_.location;
  }

  lex::Token return_token_;
  Expression* return_value_;
};

//////////////////////////////////////////////////////////////////////

class VarDeclStatement : public Statement {
 public:
  VarDeclStatement(VarAccessExpression* lvalue, Expression* value)
      : lvalue_{lvalue}, value_{value} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarDecl(this);
  }

  virtual lex::Location GetLocation() override {
    return lvalue_->GetLocation();
  }

  std::string GetVarName() {
    return lvalue_->GetName();
  }

  VarAccessExpression* lvalue_;

  Expression* value_;
};

//////////////////////////////////////////////////////////////////////

class FunDeclStatement : public Statement {
 public:
  struct FormalParam {
    lex::Token ident;
    types::Type* type;

    std::string GetParameterName() {
      return ident.GetName();
    }
  };

  ///////////////////////////////////////////////////////////////////////

  FunDeclStatement(lex::Token name, types::Type* /* return_type */,
                   std::vector<FormalParam> formals, BlockExpression* block)
      : name_{name}, formals_{std::move(formals)}, block_{block} {
  }

  ///////////////////////////////////////////////////////////////////////

  auto GetArgumentTypes() -> std::vector<types::Type*> {
    std::vector<types::Type*> result;

    for (auto fm : formals_) {
      result.push_back(fm.type);
    }

    return result;
  }

  ///////////////////////////////////////////////////////////////////////

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitFunDecl(this);
  }

  virtual lex::Location GetLocation() override {
    return name_.location;
  }

  std::string GetFunctionName() {
    return name_.GetName();
  }

  ///////////////////////////////////////////////////////////////////////

  lex::Token name_;
  types::FnType* type_ = nullptr;

  std::vector<FormalParam> formals_;
  BlockExpression* block_;
};

//////////////////////////////////////////////////////////////////////

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement(lex::Token assign, LvalueExpression* target,
                      Expression* value)
      : assign_{assign}, target_{target}, value_{value} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitAssignment(this);
  }

  virtual lex::Location GetLocation() override {
    return assign_.location;
  }

  lex::Token assign_;

  LvalueExpression* target_;

  Expression* value_;
};

//////////////////////////////////////////////////////////////////////
