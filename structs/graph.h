#ifndef GRAPH_H_
#define GRAPH_H_

#include "vector.h"
#include "list.h"

namespace stuff
{
    class edge
    {
        list<int> edge_;

        public:
        edge()
        {
        }

        ~edge()
        {
        }

        edge(const edge &l)
        {
            edge_ = l.edge_;
        }

        edge(edge &&l)
        {
            edge_ = std::move(l.edge_);
        }

        edge &operator=(const edge &l)
        {
            if (this == &l)
                return *this;

            edge_ = l.edge_;
            return *this;
        }

        edge &operator=(edge &&) = delete;

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
    };

    class graph_base
    {
        public:
        virtual void add_edge(int v, int w) = 0;
        virtual const edge &adj(int v) = 0;
        virtual int vertices() const = 0;
        virtual int edges() const = 0;
    };

    class graph : public graph_base
    {
        vector<edge> adj_;
        size_t edges_;

        public:
        graph(int size) :
            adj_(size, edge())
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

        const edge &adj(int v)
        {
            return adj_[v];
        }

        int vertices() const
        {
            return adj_.size();
        }

        int edges() const
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
            return 2.0 * edges() / vertices();
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
    };
}

#endif
