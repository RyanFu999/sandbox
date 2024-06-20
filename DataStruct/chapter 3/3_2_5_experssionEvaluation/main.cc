#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

vector<vector<char>> precedence {
    //         +     -    *    /    (    )    #
    /*  +  */ {'>', '>', '<', '<', '<', '>', '>'},
    /*  -  */ {'>', '>', '<', '<', '<', '>', '>'},
    /*  *  */ {'>', '>', '>', '>', '<', '>', '>'},
    /*  /  */ {'>', '>', '>', '>', '<', '>', '>'},
    /*  (  */ {'<', '<', '<', '<', '<', '=', '$'},
    /*  )  */ {'>', '>', '>', '>', '$', '>', '>'},
    /*  #  */ {'<', '<', '<', '<', '<', '$', '='}
};

// 定义运算符对应的索引
unordered_map<char, int> opIndex = {
    {'+', 0},
    {'-', 1},
    {'*', 2},
    {'/', 3},
    {'(', 4},
    {')', 5},
    {'#', 6}
};

char comparePrecedence(char op1, char op2) {
    return precedence[opIndex[op1]][opIndex[op2]];
}

void printStack(const stack<int>& st1, const stack<char>& st2) {
    stack<int> tmp(st1);
    string res1;
    while (!tmp.empty()) {
        res1 = to_string(tmp.top()) + " " + res1;
        tmp.pop();
    }

    stack<char> tmp1(st2);
    string res2;
    while (!tmp1.empty()) {
        string ch;
        ch += tmp1.top();
        res2 = ch + " " + res2;
        tmp1.pop();
    }
    cout << std::left << std::setw(20) << "opnd: " + res1 << std::left << std::setw(40)  << "optr : " + res2 << endl;
}

int calculate(int a, int b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        break;
    }
    printf("Wrong operator: %c!\n", op);
    return INT_MAX;
}

int evaluateExpression(const string& exp) {
    stack<char> optr;
    optr.push('#');
    stack<int> opnd;
    string str = exp + '#';
    unsigned i = 0;
    char ch = str[i];
    while (i < str.size() && (ch != '#' || !optr.empty())) {
        if (ch >= '0' && ch <= '9') {
            int num = 0;
            while (i < str.size() && ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
                ch = str[++i];
            }
            opnd.push(num);
            printStack(opnd, optr);
        } else {
            switch (comparePrecedence(optr.top(), ch)) {
            case '<':
                optr.push(ch);
                ch = str[++i];
                break;
            case '=':
                optr.pop();
                ch = str[++i];
                break;
            case '>':
            {
                char op = optr.top();
                optr.pop();
                int num1 = opnd.top();
                opnd.pop();
                int num2 = opnd.top();
                opnd.pop();
                opnd.push(calculate(num2, num1, op));
                break;
            }
            default:
                printf("wrong expression!\n");
                return INT_MAX;
            }
            printStack(opnd, optr);
        }
    }

    return opnd.top();
}

int main()
{
    string exp = "3*(17-2)";
    int res = evaluateExpression(exp);
    cout << "res: " << res << endl;

    return 0;
}
