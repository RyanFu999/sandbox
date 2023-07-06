#include <QCoreApplication>
#include "myVector.h"
#include <iostream>
using namespace std;

int main()
{
    int a = 2;
    myVector vec(10, a);

    for (int j = 0; j < 10; ++j) {
        vec.push_back(j);
    }

    myVector<int> vec1;
    vec1 = vec;
    for (unsigned i = 0; i < vec1.size(); ++i) {
        cout << vec1[i] << endl;
    }
    return 0;
}
