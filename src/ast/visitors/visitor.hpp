#pragma once

//////////////////////////////////////////////////////////////////////

class Expression;
class ComparisonExpression;
class BinaryExpression;
class UnaryExpression;
class DereferenceExpression;
class AddressofExpression;
class IfExpression;
class MatchExpression;
class NewExpression;
class BlockExpression;
class FnCallExpression;
class IntrinsicCall;
class CompoundInitializerExpr;
class FieldAccessExpression;
class LiteralExpression;
class VarAccessExpression;
class TypecastExpression;
class YieldExpression;
class ReturnExpression;

//////////////////////////////////////////////////////////////////////

class Statement;
class ExprStatement;
class AssignmentStatement;

//////////////////////////////////////////////////////////////////////

class VarDeclaration;
class FunDeclaration;
class TypeDeclaration;
class ImplDeclaration;
class TraitDeclaration;

//////////////////////////////////////////////////////////////////////

class BindingPattern;
class LiteralPattern;
class StructPattern;
class VariantPattern;
class DiscardingPattern;

//////////////////////////////////////////////////////////////////////

class Visitor {
 public:

  virtual ~Visitor() = default;

  virtual void VisitLiteral(LiteralExpression* expr) = 0;
  virtual void VisitBinaryExpression(BinaryExpression *expr) = 0;
  virtual void VisitIfExpression(IfExpression *expr) = 0;
  virtual void VisitReturnExpression(IfExpression *expr) = 0;
  virtual void VisitBlockExpression(BlockExpression *expr) = 0;
  virtual void VisitComparison(ComparisonExpression *expr) = 0;
  virtual void VisitVarAccessExpression(VarAccessExpression *expr) = 0;
  virtual void VisitUnary(UnaryExpression *expr) = 0;
  virtual void VisitFnCall(FnCallExpression *expr) = 0;)
};

//////////////////////////////////////////////////////////////////////
