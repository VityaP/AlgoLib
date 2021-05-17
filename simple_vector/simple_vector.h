// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
// #include <cstdlib>

using namespace std;


template<typename T>
class SimpleVector{

public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    SimpleVector(const SimpleVector<T> &other);

    // Move constructor
    SimpleVector(SimpleVector<T>&& other);

    void operator=(const SimpleVector<T> &other);

    // Move operator
    void operator=(SimpleVector<T> &&other);

    const T& operator[](size_t idx) const;
    T& operator[](size_t idx);
    const T* begin() const;
    T* begin();
    const T* end() const;
    T* end();

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);

    ~SimpleVector();

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};