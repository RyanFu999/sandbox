#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstdio>
#include <memory>
#include <utility>
#include <iostream>
using namespace std;

template<typename T>
class myVector
{
public:
    myVector() : _start(nullptr), _finish(nullptr), _endOfStorage(nullptr) {}
    myVector(size_t n, const T& value = T())
        : _start(nullptr), _finish(nullptr), _endOfStorage(nullptr) {
        reserve(n);
        while (n--) {
            push_back(value);
        }
    }
    ~myVector() {
        if (_start) {
            delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _endOfStorage = nullptr;
        }
    }

    void        reserve(size_t n);
    void        resize(size_t n, const T& value = T());
    void        push_back(T &&value);
    void        push_back(const T& value);

    size_t      capacity() const { return _endOfStorage - _start; }
    size_t      size() const { return _finish - _start; }

    T&              operator[](size_t pos) { return _start[pos]; }
    myVector<T>&    operator=(const myVector<T>& v);

private:
    T*          _start;
    T*          _finish; // 最后一个元素的下一个地址
    T*          _endOfStorage; // 空间的尾地址
};

template<typename T>
inline void myVector<T>::reserve(size_t n)
{
    if (n > capacity()) {
        size_t sz = size();
        T* arr = new T[n];
        if (_start) {
            memcpy(arr, _start, sizeof(T) * sz);
            delete[] _start;
        }
        _start = arr;
        _finish = _start + sz;
        _endOfStorage = _start + n;
    }
}

template<typename T>
inline void myVector<T>::resize(size_t n, const T &value)
{
    if (n > capacity()) {
        reserve(n);
    } else if (n > size()) {
        while (_finish != _start + n) {
            *_finish = value;
            ++_finish;
        }
    }
    _finish = _start + n;
}

template<typename T>
inline void myVector<T>::push_back(T&& value)
{
    if (_finish == _endOfStorage) {
        size_t sz = _endOfStorage == nullptr ? 1 : 2 * capacity();
        reserve(sz);
    }
    *_finish = value;
    ++_finish;
}

template<typename T>
inline void myVector<T>::push_back(const T &value)
{
    if (_finish == _endOfStorage) {
        size_t sz = _endOfStorage == nullptr ? 1 : 2 * capacity();
        reserve(sz);
    }
    *_finish = value;
    ++_finish;
}

template<typename T>
inline myVector<T>& myVector<T>::operator=(const myVector<T>& v)
{
    if (this != &v) {
        delete[] _start;
        size_t n = v.capacity();
        size_t sz = v.size();
        _start = new T[n];
        memcpy(_start, v._start, sizeof(T) * sz);
        _finish = _start + sz;
        _endOfStorage = _start + n;
    }
    return *this;
}


#endif // MYVECTOR_H
