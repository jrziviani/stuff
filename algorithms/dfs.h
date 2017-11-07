#ifndef DFS_H_
#define DFS_H_

#include "stack.h"
#include "graph.h"
#include "vector.h"

#include <functional>
#include <iostream>
namespace stuff
{
    void depth_search_first(graph_base &g,
                            vector<int> &start,
                            std::function<void(int v)> fn)
    {
        vector_stack<int> s;
        vector<bool> visited(g.nvertices(), false);

        for (size_t i = 0; i < start.size(); i++) {
            s.push(start[i]);
            visited[start[i]] = true;
        }

        while (!s.is_empty()) {
            int v = s.pop();

            fn(v);

            const auto visit = [&s, &visited](const int &w) {
                if (!visited[w]) {
                    visited[w] = true;
                    s.push(w);
                }
            };
            g.adj(v).iterate(visit);
        }
    }

    void depth_search_first(graph_base &g,
                            int start,
                            std::function<void(int v)> fn)
    {
        vector<int> st;
        st.append(start);
        depth_search_first(g, st, fn);
    }
}

#endif

