#ifndef _HEAP_H
#define _HEAP_H

#include "vector.h"
#include <functional>

namespace stuff
{
    // helper functions
    template <typename T>
    bool compare_max(const T &a, const T &b)
    {
        return a > b;
    }

    template <typename T>
    bool compare_min(const T &a, const T &b)
    {
        return a < b;
    }

    template <typename T>
    class heap
    {
        vector<T> _heap;
        std::function<bool(const T &a, const T &b)> _compare;

        size_t parent(size_t i) const              // O(1)
        {
            auto parent = i / 2;
            return (i & 1) ? parent : parent - 1;
        }

        size_t left(size_t i) const                // O(1)
        {
            return i * 2 + 1;
        }

        size_t right(size_t i) const               // O(1)
        {
            return i * 2 + 2;
        }

        bool has_parent(size_t i) const            // O(1)
        {
            return i > 0;
        }

        bool has_left(size_t i) const              // O(1)
        {
            return left(i) < _heap.size();
        }

        bool has_right(size_t i) const             // O(1)
        {
            return right(i) < _heap.size();
        }

        void heap_up()                             // O(log n)
        {
            size_t cur = _heap.size() - 1;

            while (has_parent(cur)) {
                size_t par = parent(cur);
                if (!_compare(_heap[cur], _heap[par]))
                    break;

                _heap.swap(cur, par);
                cur = par;
            }
        }

        void heap_down()                           // O(log n)
        {
            size_t cur = 0;

            while (has_left(cur)) {
                size_t child = left(cur);

                if (has_right(cur) && _compare(_heap[right(cur)], _heap[child])) {
                    child = right(cur);
                }

                if (!_compare(_heap[child], _heap[cur]))
                    break;

                _heap.swap(cur, child);
                cur = child;
            }
        }

        public:
        heap() :
            heap(compare_max<T>) {}

        heap(std::function<bool(const T &a, const T &b)> fn) :
            _compare(fn) {}

        void insert(T d)                           // O(log n)
        {
            _heap.append(d);
            heap_up(); // O(log n)
        }

        T remove()                                 // O(log n)
        {
            T res = _heap.front();
            auto tmp = _heap.pop();
            if (!_heap.is_empty()) {
                _heap[0] = tmp;
                heap_down();  // O(log n)
            }
            return res;
        }

        bool is_empty()
        {
            return _heap.is_empty();
        }
    };

}

#endif
