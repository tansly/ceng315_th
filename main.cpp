#include "graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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
            unsigned long weight;
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
    std::vector<std::pair<size_t, unsigned long>> w1_to_dests;
    std::vector<std::pair<size_t, unsigned long>> w2_to_dests;
    for (const auto &dest : destinations) {
        w1_to_dests.emplace_back(dest, w1_sp[dest]);
    }
    for (const auto &dest : destinations) {
        w2_to_dests.emplace_back(dest, w2_sp[dest]);
    }

    auto cmp_less = [&](const std::pair<size_t, unsigned long> &lhs,
            const std::pair<size_t, unsigned long> &rhs) {
        return lhs.second - w2_to_dests[lhs.first].second <
            rhs.second - w2_to_dests[rhs.first].second;
    };
    std::sort(w1_to_dests.begin(), w1_to_dests.end(), cmp_less);
    std::map<size_t, size_t> assignments;
    unsigned long total_length = 0;
    for (size_t i = 0; i < n_destinations/2; ++i) {
        assignments[w1_to_dests[i].first] = warehouses.first;
        total_length += w1_to_dests[i].second;
    }
    for (size_t i = n_destinations/2; i < n_destinations; ++i) {
        assignments[w1_to_dests[i].first] = warehouses.second;
        total_length += w2_to_dests[w1_to_dests[i].first].second;
    }

    /* Output */
    std::cout << total_length << '\n';
    for (const auto &ass : assignments) {
        std::cout << ass.first << " " << ass.second << '\n';
    }

    return 0;
}
