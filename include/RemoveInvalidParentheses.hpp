#ifndef REMOVE_INVALID_PARENTHESES_HPP_
#define REMOVE_INVALID_PARENTHESES_HPP_

#include <set>
#include <string>
#include <vector>

using namespace std;

class RemoveInvalidParentheses
{
  public:
    vector<string> removeInvalidParentheses(string s);

  private:
    void dfs(set<string>& result, int i, const string& s, int rmL, int rmR, int open, string current);
};

#endif // REMOVE_INVALID_PARENTHESES_HPP_