#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include "graph.h"

namespace stuff
{
    class digraph : public graph_base
    {
        vector<edges> adj_;
        size_t edges_;

        public:
        digraph(int size) :
              adj_(size, edges())
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
    };
}

#endif
