#include "Transformer.h"
#include "Token.h"
namespace ds {

/**
 * Transform the token stream from infix to postfix form.
 *
 * @param infix list of tokens in infix notation
 * @return stack<Token> token stack in postfix notation
 */
stack<Token>
InfixToPostfixTransformer::infixToPostfix(const VList<Token> &infix) {
  // Example:
  // https://docs.google.com/presentation/d/1NO2ZKEVu3IZ07Oy-QNxdAell_FThC6RylEWDEGRim6U/edit#slide=id.gecc4e479c6_0_11
  // TODO:
  stack<Token> postfixStk;
  stack<Token> opStk;

for (int i = 0; i < infix.size(); i++) // go through infix token list
  {
    Token tk = infix.get(i); // gets the i-th token
    if (tk.is(Token::Kind::Number) || (tk.is(Token::Kind::Variable))) //push to postfixStk if token is number
    {
      postfixStk.push(tk);
    }
    else if (tk.is(Token::Kind::Plus) || tk.is(Token::Kind::Minus))
    {
      // pop operators from opStack and push them to postfixStack until opStack is empty or there is a open parenthesis
     while (!(opStk.empty()) && !(opStk.top().is(Token::Kind::LeftParen)) && !(opStk.top().is(Token::Kind::Equal)))
      {
        Token temp = opStk.top();
        postfixStk.push(temp);
        opStk.pop(); 
      }
      opStk.push(tk);
    }
    else if (tk.is(Token::Kind::LeftParen))
    {
      opStk.push(tk); // push tk to opStk
    }
    else if (tk.is(Token::Kind::RightParen)) // if it gets to closing paranthesis, pop off operators until we reach opening parenthesis
    {
      while (!opStk.empty()) // while transfer tokens from opStk to postfixSt and if a LeftParen is found then break to stop.
      {
        Token temp = opStk.top();
        if (opStk.top().is(Token::Kind::LeftParen)) 
        {
          opStk.pop(); 
          break;
        }
       postfixStk.push(temp);
        opStk.pop();
      }
    }
    else if (tk.is(Token::Kind::Equal))
    {
      opStk.push(tk);
    }
    else if (tk.is(Token::Kind::Semicolon))
    {
      //since semicolon is end of expression, until opStk is empty or remaining tokens left in opStack, pop them off and push them to postfixStack one by one
      while (!(opStk.empty()))
      {
        Token temp = opStk.top();
        postfixStk.push(temp);
        opStk.pop();
      }
      postfixStk.push(tk);
    }
  }
  return postfixStk; // return the Postfix Stack
}

} // namespace ds
