#include "KthLargestElementInAnArray.hpp"

#include <queue>

int KthLargestElementInAnArray::findKthLargest(vector<int>& nums, int k)
{
    // By default, priority_queue behaves as a max-heap; larger value => higher priority
    priority_queue<int> pq;

    // Push all ints onto the priority_queue
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        pq.push(*it);
    }

    // Pop kth-minus-one largests
    for (auto i = 0; i < (k - 1); ++i) {
        pq.pop();
    }

    // Return kth largest
    return pq.top();
}
