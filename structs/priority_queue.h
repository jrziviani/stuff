#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include "heap.h"

namespace stuff
{
    template <typename T>
    class priority_queue
    {
        heap<T> _heap;

        public:
        enum class type {
            MAX_PRIORITY,
            MIN_PRIORITY
        };

        public:
        priority_queue() {}
        priority_queue(type t) :
            _heap((t == type::MAX_PRIORITY) ? compare_max<T> : compare_min<T>) {}

        void enqueue(T d)
        {
            _heap.insert(d);
        }

        T dequeue()
        {
            return _heap.remove();
        }

        bool is_empty()
        {
            return _heap.is_empty();
        }

        T top()
        {
            return _heap.look();
        }
    };
}

#endif
