#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include "graph.h"

namespace stuff
{
    class digraph : public graph_base
    {
        vector<edge> adj_;
        size_t edges_;

        public:
        digraph(int size) :
              adj_(size, edge())
        {
        }

        digraph()
        {
        }

        void add_edge(int v, int w)
        {
            adj_[v].add(w);
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

        digraph reverse()
        {

        }
    };
}

#endif
