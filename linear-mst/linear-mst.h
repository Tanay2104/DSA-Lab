#include "common.h"

struct Edge {
    int u, v;
    double w;
};

std::vector<Edge> linear_mst(int n, const std::vector<Edge>& edges);

