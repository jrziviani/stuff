#ifndef MERGESORT_H_
#define MERGESORT_H_

#include "vector.h"
#include "list.h"

#include <functional>
#include <iostream>

namespace stuff
{
    template <class C, typename T>
    void merge(C &v,
            size_t lo,
            size_t mid,
            size_t hi,
            std::function<bool(const T &a, const T &b)> fn)
    {
        vector<T> tmp(v.size());

        size_t l = lo;
        size_t m = mid;

        while (lo < m && mid < hi) {
            if (fn(v[lo], v[mid]))
                tmp.append(v[lo++]);
            else
                tmp.append(v[mid++]);
        }

        while (lo < m)
            tmp.append(v[lo++]);

        for (size_t i = 0; i < tmp.size(); i++) {
            v[l++] = tmp[i];
        }
    }

    template <class C, typename T>
    void mergesort(C &c,
                   size_t lo,
                   size_t hi,
                   std::function<bool(const T &a, const T &b)> fn)
    {
        if (hi - lo == 1)
            return;

        size_t mid = lo + (hi - lo) / 2;

        mergesort(c, lo, mid, fn);
        mergesort(c, mid, hi, fn);
        merge(c, lo, mid, hi, fn);
    }

    template <class C, typename T>
    void mergesort_iter(C &c,
                        size_t lo,
                        size_t hi,
                        std::function<bool(const T &a, const T &b)> fn)
    {
        size_t left = lo;
        size_t step = 2;
        while (left <= c.size()) {

            if (left >= c.size()) {
                left = 0;
                step *= 2;
                continue;
            }

            size_t mid = left + (step / 2 - 1) + 1;
            if (mid == hi)
                break;

            size_t right = std::min(mid + (step / 2), hi);
            merge(c, left, mid, right, fn);
            left += step;
        }
    }

    template <typename T>
    void mergesort(vector<T> &v, std::function<bool(const T&, const T&)> fn)
    {
        mergesort_iter(v, 0, v.size(), fn);
    }

    template <typename T>
    void mergesort(list<T> &l, std::function<bool(const T &a, const T &b)> fn)
    {
        mergesort(l, 0, l.size(), fn);
    }
}

#endif
