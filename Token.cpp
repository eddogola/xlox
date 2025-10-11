#include "Token.h"

#include <map>
#include <string>

namespace xlox {

std::map<std::string, TokenType> tokenStringToTokenType = {
    // single character tokens
    {"(", TokenType::LEFT_PAREN},
    {")", TokenType::RIGHT_PAREN},
    {"{", TokenType::LEFT_BRACE},
    {"}", TokenType::RIGHT_BRACE},
    {",", TokenType::COMMA},
    {".", TokenType::DOT},
    {"-", TokenType::MINUS},
    {"+", TokenType::PLUS},
    {";", TokenType::SEMICOLON},
    {"/", TokenType::SLASH},
    {"*", TokenType::STAR},
    {">", TokenType::GREATER},
    {"<", TokenType::LESS},
    {"=", TokenType::EQUAL},
    {"!", TokenType::BANG},

    // two-character tokens
    {"!=", TokenType::BANG_EQUAL},
    {">=", TokenType::GREATER_EQUAL},
    {"<=", TokenType::LESS_EQUAL},

    // keywords
    /*{"and", TokenType::LEFT_PAREN},*/
    /*{"class", TokenType::LEFT_PAREN},*/
    /*{"else", TokenType::LEFT_PAREN},*/
    /*{"false", TokenType::LEFT_PAREN},*/
    /*{"fun", TokenType::LEFT_PAREN},*/
    /*{"for", TokenType::LEFT_PAREN},*/
    /*{"if", TokenType::LEFT_PAREN},*/
    /*{"nil", TokenType::LEFT_PAREN},*/
    /*{"or", TokenType::LEFT_PAREN},*/
    /*{"print", TokenType::LEFT_PAREN},*/
    /*{"return", TokenType::LEFT_PAREN},*/
    /*{"super", TokenType::LEFT_PAREN},*/
    /*{"this", TokenType::LEFT_PAREN},*/
    /*{"true", TokenType::LEFT_PAREN},*/
    /*{"var", TokenType::LEFT_PAREN},*/
    /*{"while", TokenType::LEFT_PAREN},*/
    // {"(", TokenType::LEFT_PAREN},
};

Token::Token(TokenType tokenType, std::string lexeme, int line, int startIndex_)
    : type(tokenType), lexeme(lexeme), line(line), startIndex_(startIndex_) {}

std::string Token::toString() const {
  // return type + "\"" + lexeme + "\"" + "at line " + std::to_string(line) +
  // std::endl;
  return "\"" + lexeme + "\"" + "at line " + std::to_string(line) +
         " and column " + std::to_string(startIndex_) + "\n";
}
} // namespace xlox
