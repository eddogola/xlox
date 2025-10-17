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
#include <sys/wait.h>

namespace xlox {

Scanner::Scanner(std::string sourceText)
    : sourceText_(sourceText), line_(1), startIndex_(0), currentIndex_(0),
      hadError(false), tokens_({}) {}

Scanner::~Scanner() {}

void Scanner::error(std::string message, int line) {
  std::cerr << std::format("Line {}: {}", line, message) << std::endl;
  hadError = true;
}

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
  throw Exception("Error opening source file: " + sourceFileName);
}

std::string Scanner::getSourceText() { return sourceText_; }

std::deque<Token> Scanner::scanTokens() {

  while (!isAtEnd_()) {
    startIndex_ = currentIndex_;
    scanToken_();
  }
  tokens_.push_back(
      Token(TokenType::EOF_, "", line_, startIndex_)); // close with eof token

  return tokens_;
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
  case '!':
    addToken_(match_('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '<':
    addToken_(match_('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken_(match_('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  case '=':
    addToken_(match_('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '\n':
    line_++;
    break;
  case '/':
    if (match_('/')) {
      while (peek_() != '\n') {
        advance_();
      }
    } else {
      addToken_(TokenType::SLASH);
    }
    break;
  case '"': {
    int length = 0;
    while (peek_() != '"' && !isAtEnd_()) {
      length++;
      advance_();
    }
    if (isAtEnd_()) {
      error("Unterminated string", line_);
    }
    advance_();
    addToken_(TokenType::STRING, sourceText_.substr(startIndex_ + 1, length));
  } break;
  default:
    std::string message = std::format("Token '{}' could not be processed", c);
    error(message, line_);
    break;
  }
}

char Scanner::peek_() {
  if (!isAtEnd_()) {
    return sourceText_[currentIndex_];
  }
  return '\0';
}

char Scanner::advance_() {
  return sourceText_[currentIndex_++]; // returns original value then
                                       // increments; diff from ++currentIndex_
}

bool Scanner::isAtEnd_() { return currentIndex_ >= sourceText_.length(); }

bool Scanner::match_(char expected) {
  if (isAtEnd_() || sourceText_[currentIndex_] != expected) {
    return false;
  }
  currentIndex_++;
  return true;
}

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
