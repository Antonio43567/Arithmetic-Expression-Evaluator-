#include "Evaluator.h"

namespace ds {

/**
 * Create an expression tree from a stack of tokens in postifx form
 *
 * @param tokenStk the postfix tokens; may contain variables, numbers, plus,
 * minus, equal, and semicolon
 * @return ExprTreeNode* the root of the generated expression tree
 */
ExprTreeNode *Evaluator::buildExprTree(std::stack<Token> &tokenStk) {
  // TODO:
   if (tokenStk.empty()) // Return null if empty (there is nothing to build a node from) 
  {
    return nullptr;
  }

  Token f = tokenStk.top();
  tokenStk.pop(); // f gets value of top of stack and then the top value if popped out 
  if (f.is_one_of(Token::Kind::Number, Token::Kind::Variable))
  {
    ExprTreeNode *n = new ExprTreeNode(f); 
    return n;
  }
  else if (f.is_one_of(Token::Kind::Plus, Token::Kind::Minus, Token::Kind::Equal, Token::Kind::Semicolon))
  {
    ExprTreeNode *k = new ExprTreeNode(f); 
    
    // assign n->expr2 and n->expr1
    k->expr2 = buildExprTree(tokenStk);
    k->expr1 = buildExprTree(tokenStk);
    
    // return node n. 
    return k;
  }
  return nullptr;
}

/**
 * Evaluate the given expression tree
 *
 * @param root the root of the expression tree
 * @param varTbl the map from a variable to its value
 * @return BigInt the result of the expression; if the tree is empty, simply
 * return an empty BigInt
 */
BigInt Evaluator::evaluateExprTree(const ExprTreeNode *root, std::map<std::string, BigInt> &varTbl) {
  // TODO:
  BigInt r, x1, x2; 
  // if root == nullptr, we just return an empty BigInt
  if (root == nullptr)
  {
    BigInt empty;
    return empty;
  }

  Token q = root->token; // holds the place of the token 

  if (q.is(Token::Kind::Number)) // create a BigInt from root->token.lexeme and return it
  {
    BigInt x(root->token.lexeme);
    return x;
  }
  else if (q.is(Token::Kind::Variable)) // make a query to varTbl and return the value
  {
    return varTbl[root->token.lexeme];
  }
  else if (q.is(Token::Kind::Plus)) 
  {
    x1 = evaluateExprTree(root->expr1, varTbl);
    x2 = evaluateExprTree(root->expr2, varTbl);

    return x1 + x2;
  } else if (q.is(Token::Kind::Minus)) // evaluate root->expr1 and root->expr2 recursively, and return the absolute difference of the two subtrees
  {
    x1 = evaluateExprTree(root->expr1, varTbl);
    x2 = evaluateExprTree(root->expr2, varTbl);

    return x1 - x2;
  }
  else if (q.is(Token::Kind::Equal)) // evaluate root->expr2 and save the result in varTbl and then return it
  {
    varTbl[root->expr1->token.lexeme] = evaluateExprTree(root->expr2, varTbl);
    return varTbl[root->expr1->token.lexeme];
  } 
  else if (q.is(Token::Kind::Semicolon)) 
  {
    x1 = evaluateExprTree(root->expr1, varTbl);
    return evaluateExprTree(root->expr2, varTbl);
  }

  return r; // return the BigInt result 
}


} // namespace ds