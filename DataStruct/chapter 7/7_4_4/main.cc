#include <vector>
#include <cstdio>

using namespace std;

class FindArticual {
public:
    FindArticual(vector<vector<unsigned>>& g)
        : G(g), visited(G.size()), low(G.size()) {}

    void    calculate();

private:
    void    DFSArticul(int v0);

private:
    const vector<vector<unsigned>>&     G;
    vector<int>                         visited;
    vector<int>                         low;
    unsigned                            count;
};

void FindArticual::calculate() {
    count = 1;
    unsigned vexnum = G.size();
    visited[0] = 1;
    DFSArticul(G[0][0]); // 从 v1 的第一个邻接点出发
    if (count < vexnum) { // 从第一个邻接点出发，树没有遍历完，说明树有两颗或两颗以上子树
        printf("node: %c\n", 0 + 'A');
        for (auto v : G[0]) {
            if (visited[v] == 0)
                DFSArticul(v);
        }
    }
}

void FindArticual::DFSArticul(int v0) {
    visited[v0] = ++count;
    int min = visited[v0];
    for (auto w : G[v0]) {
        if (visited[w] == 0) {
            DFSArticul(w);
            if (low[w] < min)
                min = low[w];
            if (low[w] >= visited[v0]) // 满足条件，v0 是关节点
                printf("node: %c\n", v0 + 'A'); // 一个节点可能会有多个子树满足 low[w] >= visited[v0] 条件，所以可能会重复输出
        } else if (visited[w] < min) {
            min = visited[w];
        }
    }
    low[v0] = min;
}


int main() {
    vector<vector<unsigned>> G5 = {
        /*  A  */ {1, 2, 5, 11},
        /*  B  */ {0, 2, 3, 6, 7, 12},
        /*  C  */ {0, 1},
        /*  D  */ {1, 4},
        /*  E  */ {3},
        /*  F  */ {0},
        /*  G  */ {1, 7, 8, 10},
        /*  H  */ {1, 6, 10},
        /*  I  */ {6},
        /*  J  */ {11, 12},
        /*  K  */ {6, 7},
        /*  L  */ {0, 9, 12},
        /*  M  */ {1, 9, 11}
    };

    FindArticual f(G5);
    f.calculate();

    return 0;
}
