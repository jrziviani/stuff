#ifndef HEAPSORT_H_
#define HEAPSORT_H_

namespace stuff
{

    template <typename T>
    void heapsort(vector<T> &v, std::function<bool(const T&, const T&)> fn)
    {
        heapsort(v, 0, v.size(), fn);
    }
}

#endif
