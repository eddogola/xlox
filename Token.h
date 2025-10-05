#pragma once

#include <map>
#include <string>

namespace xlox {

enum TokenType {
  // single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // one or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  EOF_ // appended at the end of a sequence of tokens
       // underscore at the end to not eclipse C macro `EOF``
};

extern std::map<std::string, TokenType> tokenStringToTokenType;

struct Token {
public:
  Token(TokenType type, std::string lexeme, int line, int startColumn);
  std::string toString() const;

private:
  [[maybe_unused]] TokenType type;
  std::string lexeme;
  int line;
  int startColumn;
};
} // namespace xlox
