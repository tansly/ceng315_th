#include "graph.h"

#include <iostream>
#include <utility>
#include <vector>

using std::size_t;

namespace Graph {

void print_graph(const Graph &graph)
{
    size_t n_cities = graph.size();
    for (size_t i = 0; i < n_cities; ++i) {
        for (const auto &edge : graph[i]) {
            std::cout << '(' << i << ", " << edge.second << ", " <<
                edge.first << ")\n";
        }
    }
}

};
