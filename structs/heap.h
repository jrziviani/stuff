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
        vector<T> heap_;
        std::function<bool(const T &a, const T &b)> compare_;

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
            return left(i) < heap_.size();
        }

        bool has_right(size_t i) const             // O(1)
        {
            return right(i) < heap_.size();
        }

        void heap_up()                             // O(log n)
        {
            size_t cur = heap_.size() - 1;

            while (has_parent(cur)) {
                size_t par = parent(cur);
                if (!compare_(heap_[cur], heap_[par]))
                    break;

                heap_.swap(cur, par);
                cur = par;
            }
        }

        void heap_down()                           // O(log n)
        {
            size_t cur = 0;

            while (has_left(cur)) {
                size_t child = left(cur);

                if (has_right(cur) && compare_(heap_[right(cur)], heap_[child])) {
                    child = right(cur);
                }

                if (!compare_(heap_[child], heap_[cur]))
                    break;

                heap_.swap(cur, child);
                cur = child;
            }
        }

        public:
        heap() :
            heap(compare_max<T>) {}

        heap(std::function<bool(const T &a, const T &b)> fn) :
            compare_(fn) {}

        void insert(T d)                           // O(log n)
        {
            heap_.append(d);
            heap_up(); // O(log n)
        }

        T remove()                                 // O(log n)
        {
            T res = heap_.front();
            auto tmp = heap_.pop();
            if (!heap_.is_empty()) {
                heap_[0] = tmp;
                heap_down();  // O(log n)
            }
            return res;
        }

        T look()                                   // O(1)
        {
            return heap_.front();
        }

        bool is_empty()
        {
            return heap_.is_empty();
        }
    };

}

#endif
