#include "Scanner.h"
#include "Token.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <string>

namespace xlox {

Scanner::Scanner(std::string sourceText)
    : sourceText_(sourceText), line_(1), startColumn_(0), currentColumn(0),
      tokens_({}) {}

Scanner::~Scanner() {}

Scanner Scanner::buildFromSourceFile(std::string sourceFileName) {
  std::ifstream fileStream(sourceFileName, std::ios::in | std::ios::binary);
  if (fileStream) {
    std::string contents;
    fileStream.seekg(0, std::ios::end);
    contents.resize(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);
    fileStream.read(&contents[0], contents.size());
    fileStream.close();

    return Scanner(contents);
  }
  throw("Error opening source file: " + sourceFileName);
}

std::string Scanner::getSourceText() { return sourceText_; }

std::deque<Token> Scanner::scanTokens() {

  while (!(currentColumn >= sourceText_.length())) {
    startColumn_ = currentColumn;
    scanToken_();
  }

  int startColumn = 0;

  for (int i = 0; i < sourceText_.size(); ++i) {
    char c = sourceText_[i];

    if (c == '\n') {
      line_ += 1;
    }
  }

  Token endToken = Token(TokenType::EOF_, "", line_, startColumn);
  tokens_.push_back(endToken);

  return tokens_;
}

} // namespace xlox

int main() {
  std::string testSourceFile = "test.x"; // maybe change the extension in future
                                         // to be .xlox/xlx/xx/xl/xxl
  xlox::Scanner testScanner =
      xlox::Scanner::buildFromSourceFile(testSourceFile);
  // std::cout << testScanner.getSourceText();
  auto tokens_ = testScanner.scanTokens();

  for (const auto &token : tokens_) {
    std::cout << token.toString() << std::endl;
  }

  return 0;
}
