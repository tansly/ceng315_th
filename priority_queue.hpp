#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <set>
#include <utility>
#include <vector>

class PriorityQueue {
public:
private:
    std::set<std::pair<unsigned long, std::size_t>> dist;
    std::vector<decltype(dist.begin())> vertex_map;
};

#endif
