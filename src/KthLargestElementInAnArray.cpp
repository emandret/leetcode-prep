#include "KthLargestElementInAnArray.hpp"

#include <queue>

int KthLargestElementInAnArray::findKthLargest(vector<int>& nums, int k)
{
    // priority_queue is a max-heap; larger values are at the top
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
