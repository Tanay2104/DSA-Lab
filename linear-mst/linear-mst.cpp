#include "linear-mst.h"
#include "common.h"

// -----------------------------------------------------------------------------
// Disjoint Set Union (Union-Find)
// -----------------------------------------------------------------------------
struct DSU {
    std::vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { std::iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) std::swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

// -----------------------------------------------------------------------------
// Helper: Boruvka Step — contracts components and returns MST edges so far
// -----------------------------------------------------------------------------
static std::vector<Edge> boruvka_step(int n, std::vector<Edge>& edges, DSU& dsu) {
    std::vector<int> min_edge(n, -1);
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = dsu.find(edges[i].u);
        int v = dsu.find(edges[i].v);
        if (u == v) continue;
        if (min_edge[u] == -1 || edges[i].w < edges[min_edge[u]].w)
            min_edge[u] = i;
        if (min_edge[v] == -1 || edges[i].w < edges[min_edge[v]].w)
            min_edge[v] = i;
    }

    std::vector<Edge> chosen;
    for (int i = 0; i < n; i++) {
        int idx = min_edge[i];
        if (idx != -1) {
            Edge e = edges[idx];
            if (dsu.unite(e.u, e.v))
                chosen.push_back(e);
        }
    }
    return chosen;
}

// -----------------------------------------------------------------------------
// Helper: Filter heavy edges using sampled MST
// -----------------------------------------------------------------------------
static std::vector<Edge> filter_edges(const std::vector<Edge>& edges, const std::vector<Edge>& mst) {
    // Build DSU from sampled MST
    int maxv = 0;
    for (auto& e : edges)
        maxv = std::max({maxv, e.u, e.v});
    DSU dsu(maxv + 1);
    for (auto& e : mst)
        dsu.unite(e.u, e.v);

    std::vector<Edge> filtered;
    for (auto& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v))
            filtered.push_back(e);
    }
    return filtered;
}

// -----------------------------------------------------------------------------
// Main recursive function implementing KKT expected linear-time MST
// -----------------------------------------------------------------------------
std::vector<Edge> linear_mst(int n, const std::vector<Edge>& edges) {
    if (edges.empty() || n <= 1)
        return {};

    // Base case: if few edges, use Kruskal directly
    if ((int)edges.size() <= 2 * n) {
        std::vector<Edge> sorted = edges;
        std::sort(sorted.begin(), sorted.end(), [](auto& a, auto& b){ return a.w < b.w; });
        DSU dsu(n);
        std::vector<Edge> mst;
        for (auto& e : sorted)
            if (dsu.unite(e.u, e.v))
                mst.push_back(e);
        return mst;
    }

    DSU dsu(n);
    std::vector<Edge> mst;

    // 1. A few Boruvka steps to reduce graph
    for (int i = 0; i < 3; i++) {
        auto added = boruvka_step(n, const_cast<std::vector<Edge>&>(edges), dsu);
        mst.insert(mst.end(), added.begin(), added.end());
    }

    // Collect remaining edges between current components
    std::unordered_map<long long, double> mp;
    std::vector<Edge> rem;
    for (auto& e : edges) {
        int u = dsu.find(e.u);
        int v = dsu.find(e.v);
        if (u == v) continue;
        if (u > v) std::swap(u, v);
        long long key = ((long long)u << 32) | v;
        if (!mp.count(key) || e.w < mp[key]) {
            mp[key] = e.w;
        }
    }
    for (auto& kv : mp) {
        int u = (int)(kv.first >> 32);
        int v = (int)(kv.first & 0xffffffff);
        rem.push_back({u, v, kv.second});
    }

    if (rem.empty()) return mst;

    // 2. Random sampling
    std::vector<Edge> sample;
    sample.reserve(rem.size() / 2);
    std::mt19937 rng(42);
    std::bernoulli_distribution coin(0.5);
    for (auto& e : rem)
        if (coin(rng))
            sample.push_back(e);

    // 3. Recurse on sampled subgraph
    auto sample_mst = linear_mst(n, sample);

    // 4. Filter heavy edges
    auto filtered = filter_edges(rem, sample_mst);

    // 5. Recurse on filtered set
    auto mst_filtered = linear_mst(n, filtered);
    mst.insert(mst.end(), mst_filtered.begin(), mst_filtered.end());

    return mst;
}
