#ifndef _QUEUE_H
#define _QUEUE_H

#include "list.h"
#include "vector.h"

namespace stuff
{
    template <typename T>
    class vector_queue
    {
        vector<T> _queue;

        public:
        void enqueue(T d)                   // ~O(1)
        {
            _queue.append(d);
        }

        T dequeue()                         // O(n)
        {
            return _queue.dequeue();
        }

        bool is_empty()                     // O(1)
        {
            return _queue.is_empty();
        }

        size_t size()                       // O(1)
        {
            return _queue.size();
        }
    };

    template <typename T>
    class list_queue
    {
        list<T> _queue;

        public:
        void enqueue(T d)                   // O(1)
        {
            _queue.prepend(d);
        }

        T dequeue()                         // O(1)
        {
            return _queue.pop();
        }

        bool is_empty()                     // O(1)
        {
            return _queue.is_empty();
        }

        size_t size()                       // O(1)
        {
            return _queue.size();
        }
    };
}
#endif
