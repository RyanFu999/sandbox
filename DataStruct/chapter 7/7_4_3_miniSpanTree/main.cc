#include <vector>
#include <cstdio>
#include <climits>

using namespace std;

unsigned minimum(const vector<pair<unsigned, int>>& closedge) {
    unsigned res = 0;
    int lowcost = INT_MAX;
    for (unsigned i = 0; i < closedge.size(); ++i) {
        if (closedge[i].second != 0 && closedge[i].second < lowcost) {
            res = i;
            lowcost = closedge[i].second;
        }
    }
    return res;
}

/*
 * 和书上相比做了一些化简：
 * 1. 直接用邻接矩阵表示图，没有用 struct MGraph
 * 2. 用 vector<pair<unsigned, int>> 表示 closedge
 */
void MinSpanTree_PRIM(const vector<vector<int>>& G, unsigned u) {
    unsigned vecnum = G.size();
    // closedge[i] 表示集合 U 一步到达 集合 V-U 中顶点 i 的最小cost；
    // pair<unsigned, int>: first 表示通过哪个顶点到达 i，second: 最小 cost 的值
    vector<pair<unsigned, int>> closedge(vecnum);
    for (unsigned i = 0; i < vecnum; ++i) {
            closedge[i] = {u, G[u][i]};
    }

    printf("first vec is V%u\n", u + 1);
    for (unsigned i = 1; i < vecnum; ++i) {
        unsigned k = minimum(closedge);
        printf("next vec is V%u, cost: %d\n", k + 1, closedge[k].second);
        closedge[k].second = 0; // 点 k 加入集合 U

        for (unsigned j = 0; j < vecnum; ++j) {
            if (G[k][j] < closedge[j].second)
                closedge[j] = {k, G[k][j]}; // 更新 U 到 集合 V-U 中顶点的最小 cost
        }
    }
}

int main() {
    vector<vector<int>> Graph = {
      //           v1,        v2,      v3,    v4,      v5,        v6
      /*  v1  */  {0,         6,       1,     5,       INT_MAX,   INT_MAX},
      /*  v2  */  {6,         0,       5,     INT_MAX, 3,         INT_MAX},
      /*  v3  */  {1,         5,       0,     5,       6,         4},
      /*  v4  */  {5,         INT_MAX, 5,     0,       INT_MAX,   2},
      /*  v5  */  {INT_MAX,   3,       6,     INT_MAX, 0,         6},
      /*  v6  */  {INT_MAX,   INT_MAX, 4,     2,       6,         0}
    };

    MinSpanTree_PRIM(Graph, 0);
    return 0;
}
