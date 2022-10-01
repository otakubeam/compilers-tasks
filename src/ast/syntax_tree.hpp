#pragma once

#include <ast/visitors/visitor.hpp>

#include <lex/location.hpp>

//////////////////////////////////////////////////////////////////////

class TreeNode {
 public:
  // https://craftinginterpreters.com/representing-code.html#working-with-trees
  virtual void Accept(Visitor* visitor) = 0;

  virtual lex::Location GetLocation() = 0;

  virtual ~TreeNode() = default;
};

//////////////////////////////////////////////////////////////////////
