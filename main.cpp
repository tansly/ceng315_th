#include "priority_queue.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using std::size_t;
using Graph = typename std::vector<std::list<std::pair<unsigned long, size_t>>>;

void print_graph(Graph graph)
{
    size_t n_cities = graph.size();
    for (size_t i = 0; i < n_cities; ++i) {
        for (const auto &edge : graph[i]) {
            std::cout << '(' << i << ", " << edge.second << ", " <<
                edge.first << ")\n";
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " " << "input_file\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "failed to open: " << argv[1] << '\n';
        return 1;
    }

    /* Read sizes */
    size_t n_cities, n_destinations;
    if (!(infile >> n_cities >> n_destinations)) {
        std::cerr << "error reading n_cities and n_destinations\n";
        return 1;
    }

    /* Read warehouses */
    std::pair<size_t, size_t> warehouses;
    if (!(infile >> warehouses.first >> warehouses.second)) {
        std::cerr << "error reading warehouses\n";
        return 1;
    }

    /* Read destinations */
    std::vector<size_t> destinations(n_destinations);
    for (auto &dest : destinations) {
        if (!(infile >> dest)) {
            std::cerr << "error reading destinations\n";
            return 1;
        }
    }

    /* Read the graph */
    Graph graph(n_cities);
    for (auto &v_adj : graph) {
        for (size_t city = 0; city < n_cities; ++city) {
            unsigned long weight;
            if (!(infile >> weight)) {
                std::cerr << "error reading weights\n";
                return 1;
            }
            if (weight != 0) {
                v_adj.emplace_back(weight, city);
            }
        }
    }
    /* Done with the input file */
    infile.close();

    print_graph(graph);

    return 0;
}
