#include "ValidParentheses.hpp"

#include <cstdlib>
#include <exception>
#include <string>
#include <utility>

using namespace std;

template <typename T>
struct Stack {
    // Exception inherits exception
    struct Exception : public std::exception {
        enum class Code {
            StackUnderflow,
            OutOfMemory,
        };

        Exception(Code err, string msg)
            : error(err)
            , message(std::move(msg))
        {
        }

        Code getCode()
        {
            return error;
        }

        const char *getMessage()
        {
            return message.c_str();
        }

      private:
        Code error;
        string message;
    };

    // Public static field
    static constexpr int alloc_step = 8;

    // Public fields
    T *arr;  // Stack backing array
    int cap; // Stack capacity
    int cur; // Index of top element

    // Constructor
    Stack()
        : arr(nullptr)
        , cap(0)
        , cur(-1)
    {
    }

    // Destructor runs automatically when object goes out of scope
    ~Stack()
    {
        free(arr);
        cap = 0;
        cur = -1;
    }

    void growCapacity()
    {
        int new_cap = cap + alloc_step;
        auto *new_arr = static_cast<T *>(realloc(arr, new_cap * sizeof(*arr)));

        if (new_arr == nullptr) {
            throw Stack::Exception(Stack::Exception::Code::OutOfMemory, "error: memory allocation failed");
        }

        arr = new_arr;
        cap = new_cap;
    }

    void push(const T& v)
    {
        if ((cur + 1) >= cap) {
            growCapacity();
        }
        arr[++cur] = v;
    }

    void pop()
    {
        if (cur < 0) {
            throw Stack::Exception(Stack::Exception::Code::StackUnderflow, "error: stack underflow");
        }
        --cur;
    }

    T top()
    {
        if (cur < 0) {
            return -1;
        }
        return arr[cur];
    }

    int size()
    {
        if (cur < 0) {
            return 0;
        }
        return cur + 1;
    }

    bool empty()
    {
        if (cur < 0) {
            return 1;
        }
        return 0;
    }
};

bool ValidParentheses::isValid(string s)
{
    Stack<char> st;

    for (const char c : s) {
        // Push opening parentheses to the stack
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
            continue;
        }
        // Pop matching parentheses from the stack, or fail
        if (c == ')' || c == ']' || c == '}') {
            // Stack cannot be empty here
            if (st.empty()) {
                return 0;
            }
            char cc = st.top();
            if ((cc == '(' && c != ')') || (cc == '[' && c != ']') || (cc == '{' && c != '}')) {
                return 0;
            }
            st.pop();
        }
    }

    // Expect the stack to be empty here
    return st.empty();
}
