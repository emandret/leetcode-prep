#include "TopKFrequentElements.hpp"

#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

struct GreaterThanOrEqualFunctor {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second >= b.second;
    }
};

template <typename T, typename Container, typename Compare>
struct PriorityQueue {
  private:
    Container heap;
    Compare is_lower_priority;

    void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    int priorityChild(int current)
    {
        auto left = current * 2 + 1;
        auto right = current * 2 + 2;

        // Out of bound, no child nodes
        if (left >= heap.size()) {
            return -1;
        }

        // No right child, trivial case
        if (right >= heap.size()) {
            return left;
        }

        // Return the highest priority child node
        if (is_lower_priority(heap[left], heap[right])) {
            return right;
        }
        return left;
    }

    void heapifyUp(int current)
    {
        for (;;) {
            // At root node, stop here
            if (current == 0) {
                break;
            }

            // Calculate the parent node index; integer division is akin to floored division,
            // e.g. floor((current - 1) / 2)
            auto parent = (current - 1) / 2;

            // If current node has lower priority, no need to go further up
            if (is_lower_priority(heap[current], heap[parent])) {
                break;
            }

            swap(heap[current], heap[parent]);

            // Go up one level
            current = parent;
        }
    }

    void heapifyDown(int current)
    {
        for (;;) {
            auto best = priorityChild(current);

            // No child nodes, stop here
            if (best == -1) {
                break;
            }

            // If best child has lower priority, no need to go further down
            if (is_lower_priority(heap[best], heap[current])) {
                break;
            }

            swap(heap[current], heap[best]);

            // Go down one level
            current = best;
        }
    }

  public:
    PriorityQueue()
    {
    }

    ~PriorityQueue()
    {
    }

    void push(const T& n)
    {
        // First we insert the new value at the end of the heap
        // We respect the shape property; the tree must be packed left-to-right
        heap.push_back(n);

        // Satisfy the heap property by ensuring the highest priority nodes are at the top
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (heap.size() == 0) {
            return;
        }

        // Crush the root node with the last value
        *heap.begin() = heap.back();

        // Delete the last element
        heap.pop_back();

        // Satisfy the heap property from the root down to the last child
        heapifyDown(0);
    }

    T top() const
    {
        return heap.front();
    }

    int size() const
    {
        return heap.size();
    }

    bool empty() const
    {
        return heap.size() == 0;
    }
};

vector<int> TopKFrequentElements::topKFrequent(vector<int>& nums, int k)
{
    // Count how many occurrences for a given integer => O(n)
    unordered_map<int, int> freqs;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        ++freqs[*it];
    }

    // For each (integer, frequency) pair, keep the k largest frequencies in
    // a min-heap
    PriorityQueue<pair<int, int>, vector<pair<int, int>>, GreaterThanOrEqualFunctor> pq;

    // Iterate over the unordered_map => O(n)
    for (auto [key, count] : freqs) {
        // Empty heap, push first count
        if (pq.empty()) {
            pq.push(pair<int, int>(key, count));
            continue;
        }

        // Check if smallest >= count; if true, continue
        if (pq.top().first == key && pq.top().second >= count) {
            continue;
        }

        // If we are here, then count > smallest

        // Place count at the bottom of the heap; heapifyUp will ensure
        // the min count is bubbled up to root level
        pq.push(pair<int, int>(key, count));

        // If size > k, pop the root (smallest count); heapifyDown will
        // ensure the max count is bubbled down to leaf level
        if (pq.size() > k) {
            pq.pop();
        }
    }

    // Build the return vector
    vector<int> ret;
    for (auto i = 0; i < k; ++i) {
        ret.push_back(pq.top().first);
        pq.pop();
    }

    // Sort in ascending order
    sort(ret.begin(), ret.end(), [](const int& a, const int& b) -> bool {
        return a < b;
    });

    return ret;
}
