#include "BinarySearch.hpp"

int BinarySearch::search(vector<int>& nums, int target)
{
    // We use a half-open interval [0,n)
    size_t left = 0;
    size_t right = nums.size(); // One past last

    while (left < right) {
        // Integer division truncates toward zero and is akin to floor
        size_t mid = left + (right - left) / 2;

        if (target > nums[mid]) {
            left = mid + 1;
        }
        if (target < nums[mid]) {
            right = mid;
            continue;
        }
        return nums[mid];
    }
    return -1;
}
