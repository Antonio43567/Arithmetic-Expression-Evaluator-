#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include "BigInt.h"
#include "ExprTreeNode.h"
#include "Tokenizer.h"
#include <map>
#include <stack>
#include <string>

namespace ds {

class Evaluator {
public:
  /**
   * Create an expression tree from code
   */
  static ExprTreeNode *buildExprTree(std::stack<Token> &tokenStk);

  /**
   * Evaluate the expression tree
   */
  static BigInt evaluateExpr(const ExprTreeNode *root) {
    std::map<std::string, BigInt> varTbl;
    return evaluateExprTree(root, varTbl);
  }

private:
  static BigInt evaluateExprTree(const ExprTreeNode *root,
                                 std::map<std::string, BigInt> &varTbl);
};

} // namespace ds

#endif // __EVALUATOR_H__
