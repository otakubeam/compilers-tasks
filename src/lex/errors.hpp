#pragma once

#include <lex/location.hpp>

#include <string>

namespace lex {

struct LexError : std::exception {
  LexError(std::string error, Location location) {
    message =
        fmt::format("LexError: {} at location {}", error, location.Format());
  }

  std::string message;

  const char* what() const noexcept override {
    return message.c_str();
  }
};

}  // namespace lex
