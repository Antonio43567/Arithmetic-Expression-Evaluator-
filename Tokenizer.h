#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include "Token.h"
#include "VList.h"

namespace ds {

class Tokenizer {
public:
  explicit Tokenizer(const std::string &code) { m_beg = code.begin(); }

  /**
   * Next token
   */
  Token next() {
    while (isspace(peek()))
      forward();
    if (isalpha(peek())) {
      return variable();
    } else if (isdigit(peek())) {
      return number();
    } else if ('(' == peek()) {
      return atom(Token::Kind::LeftParen);
    } else if (')' == peek()) {
      return atom(Token::Kind::RightParen);
    } else if ('=' == peek()) {
      return atom(Token::Kind::Equal);
    } else if ('+' == peek()) {
      return atom(Token::Kind::Plus);
    } else if ('-' == peek()) {
      return atom(Token::Kind::Minus);
    } else if ('*' == peek()) {
      return atom(Token::Kind::Asterisk);
    } else if (';' == peek()) {
      return atom(Token::Kind::Semicolon);
    } else if ('\0' == peek()) {
      return Token(Token::Kind::End, m_beg, 1);
    } else {
      return atom(Token::Kind::Unexpected);
    }
  }

private:
  /**
   * A sequence of digits is a number token
   */
  Token number() {
    std::string::const_iterator start = m_beg;
    forward();
    while (isdigit(peek()))
      forward();
    return Token(Token::Kind::Number, start, m_beg);
  }

  /**
   * A sequence of letters is a variable token
   */
  Token variable() noexcept {
    std::string::const_iterator start = m_beg;
    forward();
    while (isalpha(peek()))
      forward();
    return Token(Token::Kind::Variable, start, m_beg);
  }

  Token atom(Token::Kind kind) { return Token(kind, m_beg++, 1); }

  char peek() const { return *m_beg; }
  void forward() { m_beg++; }

  std::string::const_iterator m_beg{};
};

} // namespace ds

#endif // __TOKENIZER_H__