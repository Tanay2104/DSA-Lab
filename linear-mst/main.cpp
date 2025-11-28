#include "common.h"
#include "linear-mst.h"

double total_weight(const std::vector<Edge>& mst) {
    double sum = 0;
    for (auto& e : mst) sum += e.w;
    return sum;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == nullptr) // cin redirects to file argv[1]
        {
            std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
            return 1;
        }
    }
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    auto mst = linear_mst(n, edges);
    std::cout << std::fixed << std::setprecision(2)
                << total_weight(mst) << std::endl;
    return 0;
}
