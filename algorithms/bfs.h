#ifndef _BFS_H
#define _BFS_H

#include "queue.h"
#include "graph.h"
#include "vector.h"

#include <functional>
#include <iostream>
namespace stuff
{
    void breadth_search_first(graph_base &g,
                              vector<int> &start,
                              std::function<void(int v)> fn)
    {
        vector_queue<int> q;
        vector<bool> visited(g.vertices(), false);

        for (size_t i = 0; i < start.size(); i++) {
            q.enqueue(start[i]);
            visited[start[i]] = true;
        }

        while (!q.is_empty()) {
            int v = q.dequeue();

            fn(v);

            const auto visit = [&q, &visited](const int &w) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.enqueue(w);
                }
            };
            g.adj(v).iterate(visit);
        }
    }

    void breadth_search_first(graph_base &g,
                              int start,
                              std::function<void(int v)> fn)
    {
        vector<int> st;
        st.append(start);
        breadth_search_first(g, st, fn);
    }
}

#endif
