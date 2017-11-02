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

        std::unique_ptr<node> head_;
        node *tail_;
        size_t size_;

        void add_first_(const T &d)                // O(1)
        {
            head_ = std::make_unique<node>(d);
            tail_ = head_.get();
            size_++;
        }

        public:
        list() :
            head_(nullptr),
            tail_(nullptr),
            size_(0) {}

        ~list()
        {
        }

        list(const list &l)
        {
            l.const_iterate([this](const T &v) {
                this->append(v);
            });
        }

        list(list &&l)
        {
            head_ = std::move(l.head_);
            tail_ = std::move(l.tail_);
            size_ = l._size;
            l._size = 0;
        }

        list &operator=(const list &l)
        {
            if (&l == this)
                return *this;

            node *iter = head_.get();
            while (iter != nullptr) {
                append(iter->data);
                iter = iter->next.get();
            }

            return *this;
        }

        list &operator=(list &&l)
        {
            if (&l == this)
                return *this;

            head_ = std::move(l.head_);
            tail_ = std::move(l.tail_);
            size_ = l._size;
            l._size = 0;

            return *this;
        }

        void append(const T &d)                    // O(1)
        {
            if (head_ == nullptr) {
                add_first_(d);
                return;
            }
            tail_->next = std::make_unique<node>(d);
            tail_->next->prev = tail_;
            tail_ = tail_->next.get();
            size_++;
        }

        void prepend(const T &d)                   // O(1)
        {
            if (head_ == nullptr) {
                add_first_(d);
                return;
            }
            std::unique_ptr<node> tmp = std::make_unique<node>(d);
            tmp->next = std::move(head_);
            head_ = std::move(tmp);
            head_->next->prev = head_.get();
            size_++;
        }

        T pop()                                    // O(1)
        {
            if (head_ == nullptr)
                throw std::out_of_range("list is empty");

            if (tail_ == head_.get())
                return dequeue();

            T ret = tail_->data;
            tail_ = tail_->prev;
            tail_->next.reset(nullptr);
            size_--;
            return ret;
        }

        T dequeue()                                // O(1)
        {
            if (head_ == nullptr)
                throw std::out_of_range("list is empty");

            T ret = head_->data;
            head_ = std::move(head_->next);
            size_--;
            if (head_ != nullptr)
                head_->prev = nullptr;
            return ret;
        }

        T& at(size_t position)                     // O(n)
        {
            if (position >= size_)
                throw std::out_of_range("out of range");

            size_t i = 0;
            node *iter = head_.get();
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
            node *iter = head_.get();
            while (iter != nullptr) {
                fn(iter->data);
                iter = iter->next.get();
            }
        }

        void const_iterate(std::function<void(const T&)> fn) // O(n)
        {
            node *iter = head_.get();
            while (iter != nullptr) {
                fn(iter->data);
                iter = iter->next.get();
            }
        }

        void iterate_rev(std::function<void(T&)> fn) // O(n)
        {
            node *iter = tail_;
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
            return head_ == nullptr;
        }

        size_t size()                              // O(1)
        {
            return size_;
        }
    };
}

#endif
