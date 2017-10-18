#ifndef _INSERTION_H
#define _INSERTION_H

#include "vector.h"
#include "list.h"

namespace stuff
{
    template <class C, typename T>
    void insertion(C &c, std::function<bool(const T&, const T&)> fn)
    {
        size_t idx_uns = 1;

        for (size_t i = 0; i < c.size() - 1; i++, idx_uns++) {
            if (fn(c[i], c[idx_uns]))
                continue;

            for (size_t j = idx_uns; j > 0; j--) {
                if (fn(c[j - 1], c[j]))
                    break;

                std::swap(c[j], c[j - 1]);
            }
        }
    }

    template <class C, typename T>
    void insertion2(C &c, std::function<bool(const T &, const T&)> fn)
    {
        size_t unsorted = 1;

        for (size_t i = 0; i < c.size() - 1; i++, unsorted++) {
            if (fn(c[i], c[unsorted]))
                continue;

            T current = c[unsorted];
            int j = unsorted - 1;
            for (; j >= 0; j--) {
                if (fn(c[j], current))
                    break;

                c[j + 1] = c[j];
            }
            c[j + 1] = current;
        }
    }

    template <typename T>
    void insertionsort(vector<T> &v, std::function<bool(const T&, const T&)> fn)
    {
        insertion2(v, fn);
    }

    template <typename T>
    void insertionsort(list<T> &l, std::function<bool(const T&, const T&)> fn)
    {
        insertion2(l, fn);
    }
};

#endif

