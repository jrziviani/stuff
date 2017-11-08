#ifndef TOPOLOGICAL_SORT_H_
#define TOPOLOGICAL_SORT_H_

#include "digraph.h"
#include "stack.h"
#include "vector.h"

#include <functional>
#include <iostream>

namespace stuff
{
    class topological_sort
    {
        vector<bool> visited_;
        vector_stack<int> reverse_;

        public:
        topological_sort(digraph &g) :
            visited_(g.nvertices(), false)
        {
            for (size_t v = 0; v < g.nvertices(); v++) {
                if (visited_[v])
                    continue;

                dfs(g, v);
            }
        }

        void dfs(digraph &g, int v)
        {
            visited_[v] = true;

            const auto visit = [this, &g](const edge &w) {
                if (visited_[w.to])
                    return;

                dfs(g, w.to);
            };
            g.adj(v).iterate(visit);
            reverse_.push(v);
        }

        void to_string()
        {
            while(!reverse_.is_empty()) {
                std::cout << reverse_.pop() << '\n';
            }
        }
    };
}

#endif
