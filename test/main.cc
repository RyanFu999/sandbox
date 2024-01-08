#include <QCoreApplication>
#include <stdio.h>
#include <string>
#include <iostream>
#include "test.h"
#include "myTime.h"
using namespace std;

std::string remove_ctrl_reserve(std::string s) {
    std::string result;
    result.reserve(s.length());
    for (unsigned i = 0; i < s.length(); ++i) {
        if (s[i] >= 0x20)
            result += s[i];
    }
    return result;
}

int main(void)
{
    unsigned size = 100000;
    string s(size, 'z');
    string res;

    myTimer timer("message");
    for (unsigned i  = 0; i < size; ++i) {
        res += s[i];
    }


    return 0;
}


