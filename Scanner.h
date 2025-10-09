#pragma once

#include "Token.h"

#include <cwctype>
#include <optional>
#include <deque>
#include <string>

namespace xlox {

class Scanner {
public:
  Scanner(std::string source);
  ~Scanner();

  /**
   * @brief Factory constructor from source file */
  static Scanner buildFromSourceFile(std::string sourceFileName);

  std::string getSourceText();

  std::deque<Token>
  scanTokens(); // TODO: update return type from void to a set of tokens?

private:
  void scanToken_();
  char advance_();
  void addToken_(TokenType tokenType);
  void addToken_(TokenType tokenType, std::optional<std::string> literal);

  std::string sourceText_;
  int line_;
  int startIndex_;          // start of token
  int currentIndex_;         // within token
  std::deque<Token> tokens_; // use deque for fast(O(1)) insertion + deletion
};

} // namespace xlox
