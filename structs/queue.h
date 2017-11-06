#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"
#include "vector.h"

namespace stuff
{
    template <typename T>
    class vector_queue
    {
        vector<T> queue_;

        public:
        void enqueue(T d)                   // ~O(1)
        {
            queue_.append(d);
        }

        T dequeue()                         // O(n)
        {
            return queue_.dequeue();
        }

        bool is_empty()                     // O(1)
        {
            return queue_.is_empty();
        }

        size_t size()                       // O(1)
        {
            return queue_.size();
        }
    };

    template <typename T>
    class list_queue
    {
        list<T> queue_;

        public:
        void enqueue(T d)                   // O(1)
        {
            queue_.prepend(d);
        }

        T dequeue()                         // O(1)
        {
            return queue_.pop();
        }

        bool is_empty()                     // O(1)
        {
            return queue_.is_empty();
        }

        size_t size()                       // O(1)
        {
            return queue_.size();
        }
    };
}
#endif
