#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include "heap.h"

namespace stuff
{
    template <typename T>
    class priority_queue
    {
        heap<T> heap_;

        public:
        enum class type {
            MAX_PRIORITY,
            MIN_PRIORITY
        };

        public:
        priority_queue() {}
        priority_queue(type t) :
            heap_((t == type::MAX_PRIORITY) ? compare_max<T> : compare_min<T>) {}

        void enqueue(T d)
        {
            heap_.insert(d);
        }

        T dequeue()
        {
            return heap_.remove();
        }

        bool is_empty()
        {
            return heap_.is_empty();
        }

        T top()
        {
            return heap_.look();
        }
    };
}

#endif
