#ifndef LRU_CACHE_HPP_
#define LRU_CACHE_HPP_

#include <unordered_map>

class LRUCacheBase
{
  public:
    virtual int get(int key) = 0;
    virtual void set(int key, int value) = 0;
};

template <typename T>
struct DoublyLinkedList {
    struct Node {
        T data;
        Node *prev;
        Node *next;

        Node(T data)
            : data(data)
            , prev(nullptr)
            , next(nullptr)
        {
        }
    };

    // Keep track of both head AND tail nodes
    Node *head;
    Node *tail;

    DoublyLinkedList()
        : head(nullptr)
        , tail(nullptr)
    {
    }

    void pushFront(Node *no)
    {
        if (!head) {
            head = tail = no;
            no->prev = nullptr;
            no->next = nullptr;
            return;
        }
        removeNode(no);
        no->next = head;
        head->prev = no;
        head = no;
    }

    void removeNode(Node *no)
    {
        if (no->prev) {
            no->prev->next = no->next;
        } else {
            head = no->next; // Remove head node
        }
        if (no->next) {
            no->next->prev = no->prev;
        } else {
            tail = no->prev; // Remove tail node
        }
        no->prev = nullptr;
        no->next = nullptr;
    }
};

class LRUCache : public LRUCacheBase
{
  private:
    struct CacheNode {
        int key;
        int val;

        CacheNode(int k, int v)
            : key(k)
            , val(v)
        {
        }
    };

    // We use a doubly linked list to:
    // - keep track of the least recently used cache node at the tail; and
    // - move the most/least recently accessed node to the head/tail in O(1).
    DoublyLinkedList<CacheNode> cacheList;

    // Each integer key maps to a DoublyLinkedList::Node ptr
    std::unordered_map<int, DoublyLinkedList<CacheNode>::Node *> cacheMap;

    // Max number of linked list nodes
    int capacity;

  public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
};

#endif // LRU_CACHE_HPP_
