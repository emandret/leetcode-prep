#ifndef GROUP_ANAGRAMS_HPP_
#define GROUP_ANAGRAMS_HPP_

#include <string>
#include <vector>

using namespace std;

class GroupAnagrams
{
  public:
    vector<vector<string>> groupAnagrams(vector<string>& strs);

  private:
    string strSort(string& s);
};

#endif // GROUP_ANAGRAMS_HPP_
