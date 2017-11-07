#ifndef GRAPH_H_
#define GRAPH_H_

#include "vector.h"
#include "list.h"

#include <iterator>

namespace stuff
{
    namespace priv
    {
        class edge_iterator
        {
            const list<int> *const edge_;
            size_t current_;

            private:
            int get_current() const
            {
                if (edge_ == nullptr)
                    return -1;

                return (*edge_)[current_];
            }

            public:
            using value_type = const int;
            using difference_type = const std::ptrdiff_t;
            using pointer = const int*;
            using reference = const int&;
            using iterator_category = std::output_iterator_tag;

            edge_iterator() = default;
            explicit edge_iterator(const list<int> *const e) :
                edge_(e),
                current_(0)
            {
            }

            reference operator*() const
            {
                return (*edge_)[current_];
            }

            edge_iterator& operator++()
            {
                current_++;
                return *this;
            }

            edge_iterator operator++(int)
            {
                auto tmp = *this;
                current_++;
                return tmp;
            }

            edge_iterator& operator--()
            {
                current_--;
                return *this;
            }

            edge_iterator operator--(int)
            {
                auto tmp = *this;
                current_--;
                return tmp;
            }

            bool operator==(const edge_iterator &rhs) const
            {
                return (*edge_)[current_] == rhs.get_current();
            }

            bool operator!=(const edge_iterator &rhs)
            {
                return current_ < (*edge_).size();
            }
        };
    }

    class edges
    {
        list<int> edge_;
        using iterator = priv::edge_iterator;

        public:
        edges()
        {
        }

        ~edges()
        {
        }

        edges(const edges &l)
        {
            edge_ = l.edge_;
        }

        edges(edges &&l)
        {
            edge_ = std::move(l.edge_);
        }

        edges &operator=(const edges &l)
        {
            if (this == &l)
                return *this;

            edge_ = l.edge_;
            return *this;
        }

        edges &operator=(edges &&) = delete;

        void add(int w)
        {
            edge_.append(w);
        }

        size_t size() const
        {
            return edge_.size();
        }

        void iterate(std::function<void(const int &)> fn) const
        {
            edge_.const_iterate(fn);
        }

        iterator begin() const
        {
            return iterator(&edge_);
        }

        iterator end() const
        {
            return iterator(nullptr);
        }
    };

    class graph_base
    {
        public:
        virtual void add_edge(int v, int w) = 0;
        virtual const edges &adj(int v) = 0;
        virtual int nvertices() const = 0;
        virtual int nedges() const = 0;
    };

    class graph : public graph_base
    {
        vector<edges> adj_;
        size_t edges_;

        //using iterator = priv::graph_iterator;

        public:
        graph(int size) :
            adj_(size, edges())
        {
        }

        graph()
        {
        }

        void add_edge(int v, int w)
        {
            adj_[v].add(w);
            adj_[w].add(v);
            edges_++;
        }

        const edges &adj(int v)
        {
            return adj_[v];
        }

        int nvertices() const
        {
            return adj_.size();
        }

        int nedges() const
        {
            return edges_;
        }

        int degree(int v)
        {
            int deg = 0;
            adj_.iterate([&deg](const auto &) { deg++; });

            return deg;
        }

        int max_degree()
        {
            int max = 0;
            for (int v = 0; v < adj_.size(); v++) {
                int deg = degree(v);
                if (deg > max)
                    max = deg;
            }
            return max;
        }

        double average_degree() const
        {
            return 2.0 * nedges() / nvertices();
        }

        int number_self_loops()
        {
            int count = 0;
            for (int v = 0; v < adj_.size(); v++) {
                adj_[v].iterate([&count, v](const auto &w) {
                        if (v == w) count++; });
            }
            return count / 2;
        }
/*
        iterator begin()
        {

        }

        iterator end()
        {

        }
        */
    };
}

#endif
