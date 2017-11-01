#ifndef _DVECTOR_H
#define _DVECTOR_H

#include <memory>
#include <functional>
#include <exception>

namespace stuff
{
    template <typename T>
    class vector
    {
        size_t _capacity;
        size_t _size;
        std::unique_ptr<T[]> _arr;

        void shrink()                             // O(n)
        {
            std::unique_ptr<T[]> tmp = std::make_unique<T[]>(_capacity / 2);
            for (size_t i = 0; i < _size; i++)
                tmp[i] = _arr[i];

            _arr.reset(nullptr);
            _arr = std::move(tmp);
            _capacity /= 2;
        }

        void expand()                             // O(n)
        {
            std::unique_ptr<T[]> tmp = std::make_unique<T[]>(_capacity * 2);
            for (size_t i = 0; i < _size; i++)
                tmp[i] = _arr[i];

            _arr.reset(nullptr);
            _arr = std::move(tmp);
            _capacity *= 2;
        }

        public:
        vector() : vector(20) {}

        vector(size_t capacity) :
            _capacity(capacity),
            _size(0),
            _arr(std::make_unique<T[]>(capacity))
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
            if (_size == _capacity)
                expand();

            _arr[_size++] = d;
        }

        void prepend(const T &d)                  // O(n)
        {
            if (_size == _capacity)
                expand();

            size_t i = _size - 1;
            do {
                _arr[i + 1] = _arr[i];
            } while (i--);

            _arr[0] = d;
            _size++;
        }

        T pop()                                   // O(1)
        {
            if (is_empty())
                throw std::out_of_range("list is empty");

            if (_capacity > 20 && _size <= _capacity / 4)
                shrink();

            _size--;
            return _arr[_size];
        }

        T dequeue()                               // O(n)
        {
            if (is_empty())
                throw std::out_of_range("list is empty");

            if (_capacity > 20 && _size <= _capacity / 4)
                shrink();

            T ret = _arr[0];
            for (size_t i = 1; i < _size; i++) {
                _arr[i - 1] = _arr[i];
            }
            _size--;
            return ret;
        }

        void swap(size_t position_a, size_t position_b)
        {
            if (position_a >= _size ||
                position_b >= _size)
                throw std::out_of_range("out of range");

            std::swap(_arr[position_a], _arr[position_b]);
        }

        T &at(size_t position)                    // O(1)
        {
            if (position >= _size)
                throw std::out_of_range("out of range");

            return _arr[position];
        }

        T &front()
        {
            return at(0);
        }

        T &back()
        {
            return at(_size - 1);
        }

        void iterate(std::function<void(T&)> fn)     // O(n)
        {
            if (is_empty())
                return;

            for (size_t i = 0; i < _size; i++)
                fn(_arr[i]);
        }

        void iterate_rev(std::function<void(T&)> fn) // O(n)
        {
            if (is_empty())
                return;

            for (size_t i = _size - 1; i > 0; i--)
                fn(_arr[i]);

            fn(_arr[0]);
        }

        T &operator[](std::size_t position)        // 0(1)
        {
            return at(position);
        }

        bool is_empty() const                      // O(1)
        {
            return _size == 0;
        }

        size_t size() const                        // O(1)
        {
            return _size;
        }
    };
}

#endif
