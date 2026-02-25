#include "LongestCommonPrefix.hpp"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string LongestCommonPrefix::longestCommonPrefix(vector<string>& strs)
{
    if (strs.empty()) {
        return "";
    }

    // Sort strings lexicographically in ascending order
    // std::sort uses insertion sort (time complexity O(n^2) in the worst case) for small arrays <= 16 elements
    // Otherwise it uses quicksort or heapsort (time complexity O(n*log(n)) in the average case)
    std::sort(strs.begin(), strs.end(), [](const string& a, const string& b) -> bool {
        return a < b;
    });

    // We only need to compare the common prefix for the first and last string
    string a = *strs.begin();
    string b = *(strs.end() - 1);

    int i;
    for (i = 0; i < a.size() && i < b.size() && a[i] == b[i]; ++i)
        ;

    return a.substr(0, i);
}
