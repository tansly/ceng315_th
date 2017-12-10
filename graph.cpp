#include "graph.h"

#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using std::size_t;

namespace Graph {

void print_graph(const Graph &graph)
{
    size_t n_cities = graph.size();
    for (size_t i = 0; i < n_cities; ++i) {
        for (const auto &edge : graph[i]) {
            std::cout << '(' << i << ", " << edge.first << ", " << edge.second << ")\n";
        }
    }
}

std::vector<unsigned long> shortest_path(const Graph &graph, size_t source)
{
    size_t n_cities = graph.size();
    std::vector<unsigned long> dist(n_cities, std::numeric_limits<unsigned long>::max());
    std::vector<bool> visited(n_cities, false);
    dist[source] = 0;

    using VertexDist = std::pair<size_t, unsigned long>;
    auto compare = [](VertexDist lhs, VertexDist rhs) {
        return lhs.second > rhs.second;
    };
    std::priority_queue<VertexDist, std::vector<VertexDist>, decltype(compare)> queue(compare);
    queue.emplace(source, 0);
    for (size_t i = 0; i < n_cities; i++) {
        if (i != source) {
            queue.emplace(i, std::numeric_limits<unsigned long>::max());
        }
    }

    while (!queue.empty()) {
        auto u = queue.top();
        queue.pop();
        if (!visited[u.first]) {
            visited[u.first] = true;
            for (const auto &edge : graph[u.first]) {
                if (dist[edge.first] > dist[u.first] + edge.second) {
                    dist[edge.first] = dist[u.first] + edge.second;
                    queue.emplace(edge.first, dist[edge.first]);
                }
            }
        }
    }
    return dist;
}

};
