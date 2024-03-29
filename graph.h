#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>

namespace Graph {

using Graph = typename std::vector<std::vector<std::pair<std::size_t, long>>>;

void print_graph(const Graph &graph);

std::vector<long> shortest_path(const Graph &graph, std::size_t source);

};

#endif
