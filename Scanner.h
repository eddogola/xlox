#pragma once

#include "Token.h"

#include <cwctype>
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
  std::string sourceText_;
  int line_;
  int startColumn_;          // start of token
  int currentColumn;         // within token
  std::deque<Token> tokens_; // use deque for fast(O(1)) insertion + deletion
};

} // namespace xlox
