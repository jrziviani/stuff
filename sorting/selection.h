#ifndef SELECTION_H_
#define SELECTION_H_

#include "vector.h"
#include "list.h"

#include <functional>

namespace stuff
{
    template <class C, typename T>
    void selection(C &c, std::function<bool(const T&, const T&)> fn)
    {
        for (size_t i = 0; i < c.size(); i++) {
            size_t min = i;
            for (size_t j = i + 1; j < c.size(); j++) {
                if (c[j] < c[min])
                    min = j;
            }
            std::swap(c[i], c[min]);
        }
    }

    template <typename T>
    void selectionsort(vector<T> &v, std::function<bool(const T&, const T&)> fn)
    {
        selection(v, fn);
    }

    template <typename T>
    void selectionsort(list<T> &l, std::function<bool(const T&, const T&)> fn)
    {
        selection(l, fn);
    }
};

#endif
