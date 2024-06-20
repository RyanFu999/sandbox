#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct HTNode {
    unsigned    weight;
    unsigned    parent, lchild, rchild;
};

void
Select(const vector<HTNode>& HT, unsigned right, unsigned& s1, unsigned& s2) {
    unsigned min1 = UINT_MAX;
    unsigned min2 = UINT_MAX;

    for (unsigned i = 1; i < right; ++i) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < min1) {
                min2 = min1;
                min1 = HT[i].weight;
                s2 = s1;
                s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight;
                s2 = i;
            }
        }
    }
}

void
HuffmanCoding(vector<HTNode>& HT, vector<string>& HC, const vector<unsigned>& w) {
    unsigned n = w.size();
    if (n <= 1) return;

    unsigned m = n * 2 - 1;
    HT.resize(m + 1);
    for (unsigned i = 1; i <= n; ++i) {
        HT[i] = {w[i - 1], 0, 0, 0};
    }

    // 建 huffman 树
    for (unsigned i = n + 1; i <= m; ++i) {
        unsigned s1 = 0, s2 = 0;
        Select(HT, i, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    // 下面两种方式都可以用
#if 0
    // --- 从叶子到根逆向求每个字符的 huffman 编码
    for (unsigned i = 1; i <= n; ++i) { // 0 - n 都是叶子节点
        string cd;
        unsigned c = i, f = HT[i].parent;
        while (f) {
            if (HT[f].lchild == c)
                cd = "0" + cd;
            else
                cd = "1" + cd;
            c = f;
            f = HT[f].parent;
        }
        HC.push_back(to_string(w[i - 1]) + ": " + cd);
    }
#else
    // 从根节点开始遍历 huffman 树
    for (unsigned i = 1; i <= m; ++i)
        HT[i].weight = 0; // 用来做节点状态标志，表示向左走还是向右走
    unsigned p = m;
    string cd;
    while (p) {
        if (HT[p].weight == 0) { // 向左
            HT[p].weight = 1;
            if (HT[p].lchild != 0) {
                p = HT[p].lchild;
                cd.push_back('0');
            } else if(HT[p].rchild == 0) {
                HC.push_back(to_string(w[p - 1]) + ": " + cd);
            }
        } else if (HT[p].weight == 1) {
            HT[p].weight = 2;
            if (HT[p].rchild != 0) {
                p = HT[p].rchild;
                cd.push_back('1');
            }
        } else {
            HT[p].weight = 0;
            p = HT[p].parent;
            cd.pop_back();
        }
    }
#endif
}

int main()
{
    vector<unsigned> w = {5, 29, 7, 8, 14, 23, 3, 11};
    vector<string> res;
    vector<HTNode> HT;
    HuffmanCoding(HT, res, w);
    for (auto& s : res) {
        cout << s << endl;
    }
    return 0;
}

