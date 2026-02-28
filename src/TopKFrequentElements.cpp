#include "TopKFrequentElements.hpp"
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

struct CompareFreqs {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second < b.second;
    }
};

template <typename T, typename LessThanFunctor>
struct MinHeap {
  private:
    vector<T> heap;
    LessThanFunctor less_than;

    void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    int smallestChild(int current)
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

        // Return the smallest child node
        if (less_than(heap[left], heap[right])) {
            return left;
        }
        return right;
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

            // Ensure current >= parent; if true, no need to go further up
            if (!less_than(heap[current], heap[parent])) {
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
            auto smallest = smallestChild(current);

            // No child nodes, stop here
            if (smallest == -1) {
                break;
            }

            // Ensure smallest >= current; if true, no need to go further down
            if (!less_than(heap[smallest], heap[current])) {
                break;
            }

            swap(heap[current], heap[smallest]);

            // Go down one level
            current = smallest;
        }
    }

  public:
    MinHeap()
    {
    }

    ~MinHeap()
    {
    }

    void push(const T& n)
    {
        // First we insert the new value at the end of the heap
        // We respect the shape property - the tree must be packed left-to-right
        heap.push_back(n);

        // Satisfy the heap property by ensuring n >= parent up to the root
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
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

    // For each (integer, frequency) pair, keep the k largest frequencies in a min-heap
    MinHeap<pair<int, int>, CompareFreqs> topk;
    CompareFreqs less_than;

    // Iterate over the unordered_map => O(n)
    for (auto [key, count] : freqs) {
        // Empty heap, push first count
        if (topk.empty()) {
            topk.push(pair<int, int>(key, count));
            continue;
        }

        // Check if smallest >= count; if true, continue
        if (topk.top().second >= count) {
            continue;
        }

        // If we are here, then count > smallest

        // Place count at the bottom of the heap; heapifyUp will ensure
        // the min count is bubbled up to root level
        topk.push(pair<int, int>(key, count));

        // If size > k, pop the root (smallest count); heapifyDown will ensure
        // the max count is bubbled down to leaf level
        if (topk.size() > k) {
            topk.pop();
        }
    }

    // Build the return vector
    vector<int> ret;
    for (auto i = 0; i < k; ++i) {
        ret.push_back(topk.top().first);
        topk.pop();
    }

    // Sort in ascending order
    std::sort(ret.begin(), ret.end(), [](const int& a, const int& b) -> bool {
        return a < b;
    });

    return ret;
}
