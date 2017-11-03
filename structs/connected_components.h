#ifndef _CONNECTED_H
#define _CONNECTED_H

#include "vector.h"
#include "graph.h"

namespace stuff
{
    class connected_components
    {
        vector<bool> marked_;
        vector<int> ids_;
        int count_;

        private:
        void dfs(graph &g, size_t v)
        {
            marked_[v] = true;
            ids_[v] = count_;

            const auto visit = [&g, this](const int &w) {
                if (marked_[w])
                    return;

                dfs(g, w);
            };
            g.adj(v).iterate(visit);
        }

        public:
        connected_components(graph &g) :
            marked_(g.vertices(), false),
            ids_(g.vertices(), -1),
            count_(0)
        {
            for (size_t v = 0; v < g.vertices(); v++) {
                if (marked_[v])
                    continue;

                dfs(g, v);
                count_++;
            }
        }

        int count()
        {
            return count_;
        }

        int id(size_t v)
        {
            if (v >= ids_.size())
                return -1;

            return ids_[v];
        }
    };
}

#endif
