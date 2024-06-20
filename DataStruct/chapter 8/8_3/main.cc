#include <cstdio>

const unsigned miniSize = 1000;

// head, foot, *Space
struct WORD {
    union {
        WORD    *llink;  // 头部域， 指向前驱节点
        WORD    *uplink; // 底部域， 指向本节点头部
    };
    unsigned    tag:1;   // 标志块，0：空闲，1：占用，头部和尾部均有
    unsigned    size:31; // 头部域，块大小
    WORD        *rlink;  // 头部域， 指向后继节点
};

inline WORD* FootLoc(WORD* p) {
    return p + p->size - 1;
}

// 首次拟合法
WORD* AllocBoundTag(WORD* pav, unsigned n) {
    WORD* p = pav;
    // 找到第一个可用节点
    while (p && p->size < n && p->rlink != pav)
        p = p->rlink;

    if (!p || p->size < n)
        return nullptr;

    WORD* f = FootLoc(p); // 指向底部
    pav = p->rlink;       // pav 指向 *p 节点的后继节点
    if (p->size - n <= miniSize) { // 整块分配，不保留 <= miniSize 的剩余内存
        if (pav == p) {   // p 的后继节点是它自己，整个空间表就剩这一块空余内存，分配完后空间表变为空表
            pav = nullptr;
        } else {
            pav->llink = p->llink; // 在链表中删除 p 节点
            p->llink->rlink = pav;
        }
        p->tag = f->tag = 1; // 修改分配节点头部和底部标志
    } else { // 分配该块的后 n 个字
        f->tag = 1; // 修改分配块的底部标志
        p->size -= n;
        f = FootLoc(p); // f 指向未分配块底部
        f->tag = 0;
        f->uplink = p;
        p = f + 1; // p 指向分配块头部
        p->tag = 1; // 修改分配块的头部标志
        p->size = n;
    }
    return p;
}

void Free(WORD* pav, WORD* p) {
    bool pre = (p - 1)->tag;
    bool next = (p + p->size)->tag;
    if (pre && next) {
        p->tag = 0;
        FootLoc(p)->uplink = p;
        FootLoc(p)->tag = 0;
        if (!pav) {
            pav = p->llink = p->rlink = p;
        } else {
            WORD* q = pav->llink; // p 节点插入到 pav 节点前面
            p->rlink = pav;
            p->llink = q;
            q->rlink = p;
            pav->llink = p;
            pav = p; // 令刚分配的节点为下次查询时最先查询的节点
        }
    } else if (!pre && next) {
        unsigned n = p->size;
        WORD* s = (p - 1)->uplink; // 左空闲块头部地址
        s->size += n;
        WORD* f = p + n - 1;
        f->uplink = s;
        f->tag = 0;
    } else if (pre && !next) {
        WORD* t = p + p->size; // 右空闲块头部地址
        p->tag = 0;
        WORD* q = t->llink;
        p->llink = q;
        q->rlink = p;
        WORD* q1 = t->rlink;
        p->rlink = q1;
        q1->llink = p;
        p->size += t->size;
        FootLoc(t)->uplink = p;
    } else {
        unsigned n = p->size;
        WORD* s = (p - 1)->uplink; // 左空闲块头部地址
        WORD* t = p + p->size; // 右空闲块头部地址
        s->size += n + t->size;
        WORD* q = t->llink;
        WORD* q1 = t->rlink;
        q->rlink = q1;
        q1->llink = q;
        FootLoc(t)->uplink = s;
    }
}

int main() {
    printf("8.3\n");
    return 0;
}
