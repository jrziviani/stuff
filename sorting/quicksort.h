#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "vector.h"
#include "list.h"

#include <functional>
#include <random>

namespace stuff
{
    inline size_t get_pivot(size_t left, size_t right)
    {
        return left;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(left, right - 1);
        return dis(gen);
    }

    template <class C, typename T>
    size_t partition(C &c,
                     size_t left,
                     size_t right,
                     std::function<bool(const T &a, const T &b)> fn)
    {
        std::swap(c[get_pivot(left, right)], c[left]);
        size_t pivot = left;
        size_t pi = left + 1;

        for (size_t i = pi; i <= right; i++) {
            if (fn(c[i], c[pivot]))
                std::swap(c[i], c[pi++]);
        }
        std::swap(c[pivot], c[--pi]);

        return pi;
    }

    template <class C, typename T>
    void quicksort(C &c,
                   size_t left,
                   size_t right,
                   std::function<bool(const T &a, const T &b)> fn)
    {
        if (left > right)
            return;

        size_t pivot = partition(c, left, right, fn);
        if (pivot > 0)
            quicksort(c, left, pivot - 1, fn);
        quicksort(c, pivot + 1, right, fn);
    }

    template <typename T>
    void quicksort(vector<T> &v, std::function<bool(const T &a, const T &b)> fn)
    {
        quicksort(v, 0, v.size() - 1, fn);
    }

    template <typename T>
    void quicksort(list<T> &l, std::function<bool(const T &a, const T &b)> fn)
    {
        quicksort(l, 0, l.size() - 1, fn);
    }
}

#endif
