#ifndef NQUEENS_II_HPP_
#define NQUEENS_II_HPP_

#include <string>
#include <vector>

using namespace std;

class NQueensII
{
  public:
    int totalNQueens(int n);

  private:
    void backtrack(int n, int depth, vector<bool>& used, vector<int>& cur, int& result);
};

#endif // NQUEENS_II_HPP_
