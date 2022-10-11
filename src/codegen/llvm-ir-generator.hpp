#pragma once

#include <ast/visitors/template_visitor.hpp>

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

namespace codegen {

class LLVMIrGenerator : public ReturnVisitor<llvm::Value*> {
 public:
  LLVMIrGenerator();
  virtual ~LLVMIrGenerator();

  virtual void VisitAssignment(AssignmentStatement*) override;
  virtual void VisitVarDecl(VarDeclStatement*) override;
  virtual void VisitFunDecl(FunDeclStatement*) override;
  virtual void VisitReturn(ReturnStatement*) override;
  virtual void VisitExprStatement(ExprStatement*) override;

  virtual void VisitComparison(ComparisonExpression*) override;
  virtual void VisitBinary(BinaryExpression*) override;
  virtual void VisitUnary(UnaryExpression*) override;
  virtual void VisitIf(IfExpression*) override;
  virtual void VisitBlock(BlockExpression*) override;
  virtual void VisitFnCall(FnCallExpression*) override;
  virtual void VisitLiteral(LiteralExpression*) override;
  virtual void VisitVarAccess(VarAccessExpression*) override;

  llvm::Module* GetModule();

 private:
  llvm::LLVMContext context_;
  llvm::IRBuilder<> builder_{context_};
  llvm::Module module_;

  std::unordered_map<std::string, llvm::AllocaInst*> named_values_;
};

}  // namespace codegen
