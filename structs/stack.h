#ifndef _STACK_H
#define _STACK_H

#include "list.h"
#include "vector.h"

namespace stuff
{
    template <typename T>
    class vector_stack
    {
        vector<T> _stack;

        public:
        void push(T d)                      // ~O(1)
        {
            _stack.append(d);
        }

        T pop()                             // ~O(1)
        {
            return _stack.pop();
        }

        bool is_empty()                     // O(1)
        {
            return _stack.is_empty();
        }

        size_t size()                       // O(1)
        {
            return _stack.size();
        }
    };

    template <typename T>
    class list_stack
    {
        list<T> _list;

        public:
        void push(T d)                      // O(1)
        {
            _list.append(d);
        }

        T pop()                             // O(1)
        {
            return _list.pop();
        }

        bool is_empty()                     // O(1)
        {
            return _list.is_empty();
        }

        size_t size()                       // O(1)
        {
            return _list.size();
        }
    };
}

#endif
