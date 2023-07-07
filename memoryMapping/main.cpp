#include <QCoreApplication>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;


class A {
public:
    A(int num) : _num(num) {}

    void        show() { cout << "num: " << _num << endl; }

private:
    int             _num;
};

void saveMemoryToFile(const char* memory, size_t size, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    file.write(memory, size);
    file.close();
}

void readMemoryFromFile(char* memory, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    // 获取文件大小
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // 读取文件内容
    file.read(memory, fileSize);
    file.close();
}

// 打印一段内存的内容，二进制表示
void printMemoryBinary(const char* memory, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::bitset<8> bits(memory[i]);
        std::cout << bits << ' ';
    }
    std::cout << std::endl;
}

int main() {
    unsigned pagesize = 1 << 13; // 8k
    char* page = new char[pagesize]; // 申请了 8k 的内存；

    size_t shift = sizeof(A);
    char* offset = page + shift; // 第二个 A 对象的起始地址
#if 1
    A* a = new (page) A(1160); // 在申请的内存上创建对象
    a->show();

    A* c = new (offset) A(5678); // 在未被占用的内存上创建 c 对象
    c->show();

    saveMemoryToFile(page, pagesize, "C:/lian/sandbox/testFile");
#else
    readMemoryFromFile(page, "C:/lian/sandbox/testFile");

    A* b = reinterpret_cast<A*>(page); //直接通过地址获取对象
    b->show();

    A* d = reinterpret_cast<A*>(offset); // 直接通过地址获取对象
    d->show();
#endif
    return 0;
}
