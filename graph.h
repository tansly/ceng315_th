#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>

namespace Graph {

using Graph = typename std::vector<std::vector<std::pair<unsigned long, std::size_t>>>;

void print_graph(const Graph &graph);

};

#endif
