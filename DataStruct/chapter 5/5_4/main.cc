#include <cstdio>

enum class ElemTag {ATOM, LIST};

#if 1
struct GLNode {
    ElemTag tag;
    union {
        int     atom;
        struct {GLNode * hp, *tp;} ptr;
    };
};
#else
struct GLNode {
    ElemTag tag;
    union {
        int         atom;
        GLNode      *hp;
    };
    GLNode*         *tp;
};
#endif

struct MPNode {
    ElemTag     tag;
    int         exp;
    union {
        float   coef;
        MPNode  *hp;
    };
    MPNode      *tp;
};

int main() {
    printf("Hello World!\n");
    return 0;
}
