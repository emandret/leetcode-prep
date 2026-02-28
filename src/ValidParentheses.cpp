#include "ValidParentheses.hpp"

#include <cstdlib>
#include <exception>
#include <string>
#include <utility>

using namespace std;

struct CharStack {
    struct Exception : public exception {
        enum class Code {
            StackUnderflow,
            OutOfMemory,
        };

        Exception(Code code, string message)
            : code(code)
            , message(std::move(message))
        {
        }

        Code getCode()
        {
            return code;
        }

        const char *getMessage()
        {
            return message.c_str();
        }

      private:
        Code code;
        string message;
    };

    // Public static field
    static constexpr int alloc_step = 8;

    // Public fields
    char *arr; // Stack backing array
    int cap;   // Stack capacity
    int cur;   // Index of top element

    // Constructor
    CharStack()
        : arr(nullptr)
        , cap(0)
        , cur(-1)
    {
    }

    // Destructor runs automatically when object goes out of scope
    ~CharStack()
    {
        free(arr);
        cap = 0;
        cur = -1;
    }

    void growCapacity()
    {
        int new_cap = cap + alloc_step;
        char *new_arr = static_cast<char *>(realloc(arr, new_cap * sizeof(*arr)));

        if (new_arr == nullptr) {
            throw CharStack::Exception(CharStack::Exception::Code::OutOfMemory, "error: memory allocation failed");
        }

        arr = new_arr;
        cap = new_cap;
    }

    void push(char c)
    {
        if ((cur + 1) >= cap) {
            growCapacity();
        }
        arr[++cur] = c;
    }

    void pop()
    {
        if (cur < 0) {
            throw CharStack::Exception(CharStack::Exception::Code::StackUnderflow, "error: stack underflow");
        }
        --cur;
    }

    char top()
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
    CharStack stack;

    for (const char c : s) {
        // Push opening parentheses to the stack
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
            continue;
        }
        // Pop matching parentheses from the stack, or fail
        if (c == ')' || c == ']' || c == '}') {
            // Stack cannot be empty here
            if (stack.empty()) {
                return 0;
            }
            char cc = stack.top();
            if ((cc == '(' && c != ')') || (cc == '[' && c != ']') || (cc == '{' && c != '}')) {
                return 0;
            }
            stack.pop();
        }
    }

    // Expect the stack to be empty here
    return stack.empty();
}
