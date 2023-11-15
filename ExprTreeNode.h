#ifndef __EXPRTREENODE_H__
#define __EXPRTREENODE_H__

#include "Tokenizer.h"
#include <ostream>

namespace ds {

/**
 * Node in expression tree
 */
class ExprTreeNode {
private:
  static void printHelp(std::ostream &os, const ExprTreeNode *root,
                        std::string &prefix, bool expr1) {
    if (root == nullptr)
      return;
    os << prefix << (expr1 ? "├─" : "└─") << root->token << "\n";
    printHelp(os, root->expr1, prefix + (expr1 ? "│ " : "  "), true);
    printHelp(os, root->expr2, prefix + (expr1 ? "│ " : "  "), false);
  }

public:
  Token token;         // the token of the node
  ExprTreeNode *expr1; // node for expr 1
  ExprTreeNode *expr2; // node for expr 2

  explicit ExprTreeNode(const Token &t) : token(t), expr1(nullptr), expr2(nullptr) {}

  explicit ExprTreeNode(ExprTreeNode *n)
      : token(n->token), expr1(n->expr1), expr2(n->expr2) {}

  ~ExprTreeNode() {
    if (expr1 != nullptr)
      delete expr1;
    if (expr2 != nullptr)
      delete expr2;
  }

  /**
   * Print a given expression tree to os
   */
  friend std::ostream &operator<<(std::ostream &os, const ExprTreeNode &t) {
    printHelp(os, &t, "", false);
    return os;
  }
};

} // namespace ds

#endif // __EXPRTREENODE_H__
