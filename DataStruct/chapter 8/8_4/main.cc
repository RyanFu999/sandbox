#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;


const unsigned m = 16;

struct word_b {
    word_b      *llink;
    unsigned    tag:1;
    unsigned    kval:31;
    word_b      *rlink;
};

struct HeadNode {
    unsigned    nodesize;
    word_b      *first;
};

word_b* AllocBuddy(vector<HeadNode>& avail, unsigned n) {
    unsigned m = avail.size();
    unsigned k = 0;
    while (k <= m && (avail[k].nodesize < n + 1 || !avail[k].first))
        ++k;
    if (k > m)
        return nullptr;

    word_b* pa = avail[k].first;
    word_b* pre = pa->llink;
    word_b* suc = pa->rlink;
    if (pa == suc) {
        avail[k].first = nullptr; // 分配后该子表变为空表
    } else {
        pre->rlink = suc;
        suc->llink = pre;
        avail[k].first = suc;
    }

    // 将剩余块插入相应子表
    unsigned i = 1;
    for (; avail[k - i].nodesize >= n + 1; ++i) {
        word_b* pi = pa + (unsigned)pow(2, k - i);
        pi->rlink = pi;
        pi->llink = pi;
        pi->tag = 0;
        pi->kval = k - 1;
        avail[k - i].first = pi;
    }
    pa->tag = 1;
    pa->kval = k - (--i);

    return pa;
}


int main() {
    printf("8.4\n");
    return 0;
}
