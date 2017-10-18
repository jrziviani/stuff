#ifndef _LIST_H
#define _LIST_H

#include <memory>
#include <functional>

namespace stuff
{
    template <typename T>
    class list
    {
        struct node
        {
            T data;
            std::unique_ptr<node> next;
            node *prev;

            node(const T &d) :
                data(d), next(nullptr), prev(nullptr) {}
        };

        std::unique_ptr<node> _head;
        node *_tail;
        size_t _size;

        void _add_first(const T &d)                // O(1)
        {
            _head = std::make_unique<node>(d);
            _tail = _head.get();
            _size++;
        }

        public:
        list() :
            _head(nullptr),
            _tail(nullptr),
            _size(0) {}

        void append(const T &d)                    // O(1)
        {
            if (_head == nullptr) {
                _add_first(d);
                return;
            }
            _tail->next = std::make_unique<node>(d);
            _tail->next->prev = _tail;
            _tail = _tail->next.get();
            _size++;
        }

        void prepend(const T &d)                   // O(1)
        {
            if (_head == nullptr) {
                _add_first(d);
                return;
            }
            std::unique_ptr<node> tmp = std::make_unique<node>(d);
            tmp->next = std::move(_head);
            _head = std::move(tmp);
            _head->next->prev = _head.get();
            _size++;
        }

        T pop()                                    // O(1)
        {
            if (_head == nullptr)
                throw std::out_of_range("list is empty");

            if (_tail == _head.get())
                return dequeue();

            T ret = _tail->data;
            _tail = _tail->prev;
            _tail->next.reset(nullptr);
            _size--;
            return ret;
        }

        T dequeue()                                // O(1)
        {
            if (_head == nullptr)
                throw std::out_of_range("list is empty");

            T ret = _head->data;
            _head = std::move(_head->next);
            _size--;
            if (_head != nullptr)
                _head->prev = nullptr;
            return ret;
        }

        T& at(size_t position)                     // O(n)
        {
            if (position >= _size)
                throw std::out_of_range("out of range");

            size_t i = 0;
            node *iter = _head.get();
            while (iter != nullptr) {
                if (i == position)
                    break;

                i++;
                iter = iter->next.get();
            }

            return iter->data;
        }

        void iterate(std::function<void(T&)> fn)     // O(n)
        {
            node *iter = _head.get();
            while (iter != nullptr) {
                fn(iter->data);
                iter = iter->next.get();
            }
        }

        void iterate_rev(std::function<void(T&)> fn) // O(n)
        {
            node *iter = _tail;
            while (iter != nullptr) {
                fn(iter->data);
                iter = iter->prev;
            }
        }

        T &operator[](std::size_t position)        // 0(n)
        {
            return at(position);
        }

        bool is_empty()                            // O(1)
        {
            return _head == nullptr;
        }

        size_t size()                              // O(1)
        {
            return _size;
        }
    };
}

#endif
