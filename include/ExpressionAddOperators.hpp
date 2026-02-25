#ifndef EXPRESSION_ADD_OPERATORS_HPP_
#define EXPRESSION_ADD_OPERATORS_HPP_

#include <string>
#include <vector>

using namespace std;

class ExpressionAddOperators
{
  public:
    vector<string> addOperators(string num, int target);

  private:
    void dfs(string num, int target, string expr, long currRes, long prevNum, vector<string>& res);
};

#endif // EXPRESSION_ADD_OPERATORS_HPP_
