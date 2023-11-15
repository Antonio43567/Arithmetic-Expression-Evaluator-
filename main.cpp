#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Evaluator.h"
#include "Transformer.h"
#include <doctest.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TEST_CASE("InfixToPostfix") {
  string code = "a = 456 + (1123 - 1); b = a + 1; b;";
  stack<ds::Token> postfixStk = ds::InfixToPostfixTransformer::transform(code);

  SUBCASE("Transform") {
    stringstream ss1;
    stack<ds::Token> postfixStkCopy = postfixStk;
    while (!postfixStkCopy.empty()) {
      ds::Token top = postfixStkCopy.top();
      postfixStkCopy.pop();
      ss1 << top << " ";
    }
    REQUIRE(ss1.str() ==
            "Semicolon(;) Variable(b) Semicolon(;) Equal(=) Plus(+) Number(1) "
            "Variable(a) Variable(b) Semicolon(;) Equal(=) Plus(+) Minus(-) "
            "Number(1) Number(1123) Number(456) Variable(a) ");
  }

  ds::ExprTreeNode *root = ds::Evaluator::buildExprTree(postfixStk);
  SUBCASE("Build") {
    stringstream ss2;
    ss2 << *root;
    REQUIRE(ss2.str() == "└─Semicolon(;)\n"
                         "  ├─Semicolon(;)\n"
                         "  │ ├─Semicolon(;)\n"
                         "  │ │ └─Equal(=)\n"
                         "  │ │   ├─Variable(a)\n"
                         "  │ │   └─Plus(+)\n"
                         "  │ │     ├─Number(456)\n"
                         "  │ │     └─Minus(-)\n"
                         "  │ │       ├─Number(1123)\n"
                         "  │ │       └─Number(1)\n"
                         "  │ └─Equal(=)\n"
                         "  │   ├─Variable(b)\n"
                         "  │   └─Plus(+)\n"
                         "  │     ├─Variable(a)\n"
                         "  │     └─Number(1)\n"
                         "  └─Variable(b)\n");
  }

  ds::BigInt res = ds::Evaluator::evaluateExpr(root);
  SUBCASE("Evaluate") {
    stringstream ss3;
    ss3 << res;
    REQUIRE(ss3.str() == "1579");
  }

  delete root;
}
