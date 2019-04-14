#ifndef BIT_H_
#define BIT_H_

#include "vector.h"

#include <limits>

namespace stuff
{
    class binary_index_tree
    {
        vector<long int> data_;

    public:
        binary_index_tree(size_t capacity, int init) :
            data_(capacity, init)
        {
        }

        void update(size_t index, long int value)
        {
            while (index < data_.size()) {
                data_[index] =+ value;
                index += (index & -index);
            }
        }

        long int read(size_t index)
        {
            if (index >= data_.size()) {
                return std::numeric_limits<long int>::min();
            }

            long int sum = 0;
            while (index) {
                sum += data_[index];
                index -= (index & -index);
            }

            return sum;
        }
    };
}

#endif // BIT_H_
