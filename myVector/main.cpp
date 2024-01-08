#include <QCoreApplication>
#include "myVector.h"
#include <iostream>
using namespace std;

int main()
{
//    int a = 2;
//    myVector vec(10, a);

//    for (int j = 0; j < 10; ++j) {
//        vec.push_back(j);
//    }

//    vec.resize(30, 60);

//    myVector<int> vec1;
//    vec1 = vec;

//    for (unsigned i = 0; i < vec1.size(); ++i) {
//        cout << vec1[i] << endl;
//    }
//    int a = 5;
//    double r = a / 2.0;
//    printf("r %f\n", r);
    double min_change = std::numeric_limits<double>::epsilon();
    std::cout << "double: " << min_change << std::endl;

    int min_change1 = std::numeric_limits<int>::epsilon();
    std::cout << "int: " << min_change1 << std::endl;
    return 0;
}
