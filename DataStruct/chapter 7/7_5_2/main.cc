#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

// 边带权的邻接表的节点
struct Node {
    unsigned    vex;
    int         weight;
    Node(unsigned v, int w) : vex(v), weight(w) {}
};

bool TopologicalOrder(const vector<vector<Node>>& G, vector<unsigned>& ve, stack<unsigned>& T) {
    unsigned vexnum = G.size();
    vector<unsigned> indegree(vexnum, 0);
    for (auto &v : G) {
        for (auto& n : v) {
            indegree[n.vex]++;
        }
    }

    stack<unsigned> S;
    for (unsigned i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0)
            S.push(i);
    }

    while (!S.empty()) {
        unsigned u = S.top();
        S.pop();
        T.push(u);
        for (auto& node : G[u]) {
            unsigned k = node.vex;
            if (--indegree[k] == 0)
                S.push(k);

            if (ve[u] + node.weight > ve[k]) // 取最大的值，要等所有的前置都完成
                ve[k] = ve[u] + node.weight;
        }
    }

    if (T.size() < vexnum)
        return false;
    return true;
}

bool CriticalPath(const vector<vector<Node>>& G) {
    stack<unsigned> T;
    unsigned n = G.size();
    vector<unsigned> ve(n);
    if (!TopologicalOrder(G, ve, T))
        return false;

    vector<unsigned> vl(n, ve[n - 1]);
    while (!T.empty()) {
        unsigned j = T.top();
        T.pop();
        for (auto node : G[j]) {
            unsigned k = node.vex;
            if (vl[k] - node.weight < vl[j])
                vl[j] = vl[k] - node.weight;
        }
    }

    for (unsigned j = 0; j < n; ++j) {
        for (auto node : G[j]) {
            unsigned k = node.vex;
            int dut = node.weight;
            if (ve[j] == vl[k] - dut) {
                // j 和 k 之间的边就是关键活动
                printf("V%u - V%u, dut:%d, ee:%u, el:%d\n", j + 1, k + 1, dut, ve[j], vl[k] - dut);
            }
        }
    }
    return true;
}

int main() {
    vector<vector<Node>> graph = {
        {{1, 6}, {2, 4}, {3, 5}},
        {{4, 1}},
        {{4, 1}},
        {{5, 2}},
        {{6, 9}, {7, 7}},
        {{7, 4}},
        {{8, 2}},
        {{8, 4}},
        {}
    };

    if (!CriticalPath(graph))
        printf("ERROR\n");

    printf("7.5.2\n");

    return 0;
}
