#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct CSNode {
    int     data;
    CSNode  *firstChild;
    CSNode  *nextsibling;
    CSNode(int d, CSNode* f = nullptr, CSNode* n = nullptr)
        : data(d), firstChild(f), nextsibling(n) {}
};

// 深度优先生成树
void DFSTree(const vector<vector<unsigned>>& G, vector<bool>& visited, unsigned v, CSNode* T) {
    visited[v] = true;
    bool first = true;
    CSNode* q = nullptr;;
    for (unsigned w : G[v]) {
        if (!visited[w]) {
            CSNode* p = new CSNode(w);
            if (first) {
                T->firstChild = p;
                first = false;
            } else {
                q->nextsibling = p;
            }
            q = p;
            DFSTree(G, visited, w, q);
        }
    }
}

// 层序输出树
void print(CSNode* root) {
    if (!root) return;

    std::queue<CSNode*> q;
    q.push(root);

    while (!q.empty()) {
        unsigned num = q.size();
        for (unsigned i = 0; i < num; ++i) {
            CSNode* node = q.front(); // 取出队首节点
            q.pop();
            std::cout << "V" << 1 + node->data << " ";

            // 将当前节点的所有子节点入队
            if (node->firstChild) {
                q.push(node->firstChild);
                // 将当前子节点的所有兄弟节点依次入队
                CSNode* sibling = node->firstChild->nextsibling;
                while (sibling) {
                    q.push(sibling);
                    sibling = sibling->nextsibling;
                }
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<unsigned>> G4 = {
        {1, 2},
        {0, 3, 4},
        {0, 5, 6},
        {1, 7},
        {1, 7},
        {2, 6},
        {2, 5},
        {3, 4}
    };

    CSNode* T = new CSNode(0);
    vector<bool> visited(G4.size(), false);
    DFSTree(G4, visited, 0, T);
    print(T);

    return 0;
}
