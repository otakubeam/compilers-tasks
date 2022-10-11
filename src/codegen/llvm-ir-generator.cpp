#pragma once

#include <codegen/llvm-ir-generator.hpp>

#include <ast/expressions.hpp>
#include <ast/statements.hpp>

namespace codegen {

LLVMIrGenerator::LLVMIrGenerator() : module_{"file", context_} {
}

LLVMIrGenerator::~LLVMIrGenerator() = default;

void LLVMIrGenerator::VisitAssignment(AssignmentStatement*) {
}

void LLVMIrGenerator::VisitVarDecl(VarDeclStatement*) {
}

void LLVMIrGenerator::VisitFunDecl(FunDeclStatement*) {
}

void LLVMIrGenerator::VisitReturn(ReturnStatement*) {
}

void LLVMIrGenerator::VisitExprStatement(ExprStatement*) {
}

void LLVMIrGenerator::VisitComparison(ComparisonExpression*) {
}

void LLVMIrGenerator::VisitBinary(BinaryExpression*) {
}

void LLVMIrGenerator::VisitUnary(UnaryExpression*) {
}

void LLVMIrGenerator::VisitIf(IfExpression*) {
}

void LLVMIrGenerator::VisitBlock(BlockExpression*) {
}

void LLVMIrGenerator::VisitFnCall(FnCallExpression*) {
}

void LLVMIrGenerator::VisitLiteral(LiteralExpression* node) {
  switch (node->token_.type) {
    case lex::TokenType::NUMBER:
      return_value = llvm::ConstantInt::get(
          context_,
          llvm::APInt{
              32,                                              // numBits
              (uint64_t)std::get<int>(node->token_.sem_info),  // val
              true,                                            // isSigned
          });
      break;

    default:
      FMT_ASSERT(false, "Typechecking unknown literal");
  }
}

void LLVMIrGenerator::VisitVarAccess(VarAccessExpression* node) {
  return_value = named_values_[node->GetName()];
}

llvm::Module* LLVMIrGenerator::GetModule() {
  return &module_;
}

}  // namespace codegen
