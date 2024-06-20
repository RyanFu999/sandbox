#include <vector>
using namespace std;

enum class GraphKind { DG, DN, UDG, UDN };

struct ArcNode {
    int         adjvex;
    ArcNode     *nextarc;

};

struct VNode {
    int         data;
    ArcNode     *firsrarc;
};

struct ALGraph {
    vector<VNode>   vertices;
    int             vexnum, arcnum;
    int             kind;
};

int main() {
    return 0;
}
