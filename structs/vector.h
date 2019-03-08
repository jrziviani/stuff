#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <functional>
#include <exception>

namespace stuff
{
    template <typename T>
    class vector
    {
        size_t capacity_;
        size_t size_;
        std::unique_ptr<T[]> arr_;

        void shrink()                             // O(n)
        {
            std::unique_ptr<T[]> tmp = std::make_unique<T[]>(capacity_ / 2);
            for (size_t i = 0; i < size_; i++)
                tmp[i] = arr_[i];

            arr_.reset(nullptr);
            arr_ = std::move(tmp);
            capacity_ /= 2;
        }

        void expand()                             // O(n)
        {
            std::unique_ptr<T[]> tmp = std::make_unique<T[]>(capacity_ * 2);
            for (size_t i = 0; i < size_; i++)
                tmp[i] = arr_[i];

            arr_.reset(nullptr);
            arr_ = std::move(tmp);
            capacity_ *= 2;
        }

        public:
        vector() : vector(20) {}

        vector(size_t capacity) :
            capacity_(capacity),
            size_(0),
            arr_(std::make_unique<T[]>(capacity))
        {
        }

        vector(size_t capacity, T init) :
            vector(capacity)
        {
            for (size_t i = 0; i < capacity; i++)
                append(init);
        }

        void append(const T &d)                   // O(1)
        {
            if (size_ == capacity_)
                expand();

            arr_[size_++] = d;
        }

        void prepend(const T &d)                  // O(n)
        {
            if (size_ == capacity_)
                expand();

            size_t i = size_ - 1;
            do {
                arr_[i + 1] = arr_[i];
            } while (i--);

            arr_[0] = d;
            size_++;
        }

        T pop()                                   // O(1)
        {
            if (is_empty())
                throw std::out_of_range("list is empty");

            if (capacity_ > 20 && size_ <= capacity_ / 4)
                shrink();

            size_--;
            return arr_[size_];
        }

        T dequeue()                               // O(n)
        {
            if (is_empty())
                throw std::out_of_range("list is empty");

            if (capacity_ > 20 && size_ <= capacity_ / 4)
                shrink();

            T ret = arr_[0];
            for (size_t i = 1; i < size_; i++) {
                arr_[i - 1] = arr_[i];
            }
            size_--;
            return ret;
        }

        void swap(size_t position_a, size_t position_b)
        {
            if (position_a >= size_ ||
                position_b >= size_)
                throw std::out_of_range("out of range");

            std::swap(arr_[position_a], arr_[position_b]);
        }

        T &at(size_t position) const              // O(1)
        {
            if (position >= size_)
                throw std::out_of_range("out of range");

            return arr_[position];
        }

        T &front()
        {
            return at(0);
        }

        T &back()
        {
            return at(size_ - 1);
        }

        void iterate(std::function<void(T&)> fn)     // O(n)
        {
            if (is_empty())
                return;

            for (size_t i = 0; i < size_; i++)
                fn(arr_[i]);
        }

        void iterate_rev(std::function<void(T&)> fn) // O(n)
        {
            if (is_empty())
                return;

            for (size_t i = size_ - 1; i > 0; i--)
                fn(arr_[i]);

            fn(arr_[0]);
        }

        T &operator[](std::size_t position) const  // 0(1)
        {
            return at(position);
        }

        bool is_empty() const                      // O(1)
        {
            return size_ == 0;
        }

        size_t size() const                        // O(1)
        {
            return size_;
        }
    };
}

#endif
