#include "Scanner.h"
#include "Exception.h"
#include "Token.h"

#include <deque>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

namespace xlox {

Scanner::Scanner(std::string sourceText)
    : sourceText_(sourceText), line_(1), startIndex_(0), currentIndex_(0),
      hadError(false), tokens_({}) {}

void Scanner::error(std::string message, int line) {
  std::cerr << std::format("Line {}: {}", line_, message);
  hadError = true;
}

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
  throw std::runtime_error("Error opening source file: " + sourceFileName);
}

std::string Scanner::getSourceText() { return sourceText_; }

char Scanner::advance_() { return sourceText_[currentIndex_++]; }

void Scanner::addToken_(TokenType tokenType) {
  std::optional<std::string> noInput = std::nullopt;
  addToken_(tokenType, noInput);
}

void Scanner::addToken_(TokenType tokenType,
                        std::optional<std::string> maybeLiteral) {
  int lexemeLength = currentIndex_ - startIndex_;
  [[maybe_unused]] std::string lexeme =
      sourceText_.substr(startIndex_, lexemeLength);
  if (maybeLiteral.has_value()) {
    std::string literal = maybeLiteral.value();
    tokens_.push_back(Token(tokenType, literal, line_, startIndex_));
  } else {
    tokens_.push_back(Token(tokenType, lexeme, line_, startIndex_));
  }
}

void Scanner::scanToken_() {
  char c = advance_();

  switch (c) {
  case '(':
    addToken_(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken_(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken_(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken_(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken_(TokenType::COMMA);
    break;
  case '.':
    addToken_(TokenType::DOT);
    break;
  case '-':
    addToken_(TokenType::MINUS);
    break;
  case '+':
    addToken_(TokenType::PLUS);
    break;
  case ';':
    addToken_(TokenType::SEMICOLON);
    break;
  case '*':
    addToken_(TokenType::STAR);
    break;
  case '\n':
    line_++;
    break;
  default:
    std::string message = std::format("Token '{}' could not be processed", c));
    error(message, line);
    break;
  }
}

std::deque<Token> Scanner::scanTokens() {

  while (!(currentIndex_ >=
           sourceText_.length())) { // while not at the end of the source code
    startIndex_ = currentIndex_;
    scanToken_();
  }

  // close with EOF token
  Token endToken = Token(TokenType::EOF_, "", line_, startIndex_);
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
