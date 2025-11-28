#include "thief.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == nullptr) // cin redirects to file argv[1]
        {
            std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
            return 1;
        }
    }
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    int x, y;
    for(int i = 0; i < m; i++){
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout << solve(adj) << endl;

}

