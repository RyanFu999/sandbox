#include <deque>
#include <iostream>

using namespace std;

void Output(const deque<int>& B) {
    for (auto i : B) {
        cout << i << " ";
    }
    cout << endl;
}

void GetPowerSet(unsigned i, const deque<int>& A, deque<int>& B) {
    if (i >= A.size())
        Output(B);
    else {
        int x = A[i];
        B.push_back(x);
        GetPowerSet(i + 1, A, B);
        B.pop_back();
        GetPowerSet(i + 1, A, B);
    }
}

int main() {
    deque<int> A = {1, 2, 3};
    deque<int> B;
    GetPowerSet(0, A, B);
    return 0;
}
