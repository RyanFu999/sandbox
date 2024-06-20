#include <vector>
#include <climits>
#include <cstdio>

using namespace std;

void ShortestPath_FLOYD(const vector<vector<unsigned>>& G, vector<vector<unsigned>>& D) {
    unsigned n = G.size();

    vector<vector<vector<bool>>> P(n, vector<vector<bool>>(n, vector<bool>(n, false)));
    for (unsigned v = 0; v < n; ++v) {
        for (unsigned w = 0; w < n; ++w) {
            D[v][w] = G[v][w];
            if (D[v][w] < UINT_MAX) {
                P[v][w][v] = true;
                P[v][w][w] = true;
            }
        }
    }

    for (unsigned u = 0; u < n; ++u) {
        for (unsigned v = 0; v < n; ++v) {
            for (unsigned w = 0; w < n; ++w) {
                if (D[v][u] + D[u][w] < D[v][w]) {
                    D[v][w] = D[v][u] + D[u][w];
                    for (unsigned i = 0; i < n; ++i) {
                        P[v][w][i] = P[v][u][i] || P[u][w][i];
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<unsigned>> graph = {
        {0, 4, 11},
        {6, 0, 2},
        {3, UINT_MAX, 0}
    };
    unsigned n = graph.size();
    vector<vector<unsigned>> D(n, vector<unsigned>(n, 0));
    ShortestPath_FLOYD(graph, D);

    for (unsigned v = 0; v < n; ++v) {
        for (unsigned w = 0; w < n; ++w) {
            printf("%u ", D[v][w]);
        }
        printf("\n");
    }


    return 0;
}
