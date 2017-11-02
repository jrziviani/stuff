#ifndef _STACK_H
#define _STACK_H

#include "list.h"
#include "vector.h"

namespace stuff
{
    template <typename T>
    class vector_stack
    {
        vector<T> stack_;

        public:
        void push(T d)                      // ~O(1)
        {
            stack_.append(d);
        }

        T pop()                             // ~O(1)
        {
            return stack_.pop();
        }

        T peek()
        {
            return stack_[stack_.size() - 1];
        }

        bool is_empty()                     // O(1)
        {
            return stack_.is_empty();
        }

        size_t size()                       // O(1)
        {
            return stack_.size();
        }
    };

    template <typename T>
    class list_stack
    {
        list<T> list_;

        public:
        void push(T d)                      // O(1)
        {
            list_.append(d);
        }

        T pop()                             // O(1)
        {
            return list_.pop();
        }

        bool is_empty()                     // O(1)
        {
            return list_.is_empty();
        }

        size_t size()                       // O(1)
        {
            return list_.size();
        }
    };
}

#endif
