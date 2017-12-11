#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

using std::size_t;

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
    Graph::Graph graph(n_cities);
    for (auto &v_adj : graph) {
        for (size_t city = 0; city < n_cities; ++city) {
            long weight;
            if (!(infile >> weight)) {
                std::cerr << "error reading weights\n";
                return 1;
            }
            if (weight != 0) {
                v_adj.emplace_back(city, weight);
            }
        }
    }
    /* Done with the input file */
    infile.close();

    auto w1_sp = Graph::shortest_path(graph, warehouses.first);
    auto w2_sp = Graph::shortest_path(graph, warehouses.second);

    auto cmp = [&](size_t lhs, size_t rhs) {
        return w1_sp[lhs] - w2_sp[lhs] < w1_sp[rhs] - w2_sp[rhs];
    };
    std::sort(destinations.begin(), destinations.end(), cmp);
    std::map<size_t, size_t> assignments;
    long total_length = 0;
    for (size_t i = 0; i < n_destinations/2; ++i) {
        assignments[destinations[i]] = warehouses.first;
        total_length += w1_sp[destinations[i]];
    }
    for (size_t i = n_destinations/2; i < n_destinations; ++i) {
        assignments[destinations[i]] = warehouses.second;
        total_length += w2_sp[destinations[i]];
    }

    /* Output */
    std::cout << total_length << '\n';
    for (const auto &ass : assignments) {
        std::cout << ass.first << " " << ass.second << '\n';
    }

    return 0;
}
