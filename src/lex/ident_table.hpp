#pragma once

#include <lex/token_type.hpp>

#include <string>
#include <map>

#include <fmt/core.h>

namespace lex {

class IdentTable {
 public:
  IdentTable() {
    Populate();
  }

  // Use-of-string-view-for-map-lookup
  // https://stackoverflow.com/questions/35525777

  TokenType LookupWord(const std::string_view) {
    std::abort();
  }

 private:
  void Populate() {
  }

 private:
  // What-are-transparent-comparators
  // https://stackoverflow.com/questions/20317413

  std::map<std::string, TokenType, std::less<>> map_;
};

}  // namespace lex
