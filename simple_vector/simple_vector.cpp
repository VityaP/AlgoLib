#include "simple_vector.h"

template<typename T>
SimpleVector<T>::SimpleVector(){
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
    : data(new T[size]),
      size(size),
      capacity(size)
{    
}

template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T> &other)
    : data(new T[other.capacity]),
      size(other.size),
      capacity(other.capacity)
{    
    copy(other.begin(), other.end(), begin());
}

// Move constructor
template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other)
    : data(other.data),
      size(other.size),
      capacity(other.capacity)
{    
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
void SimpleVector<T>::operator=(const SimpleVector<T> &other){
    if( capacity < other.size ){
        delete [] data;
        data = new T[other.capacity];
        capacity = other.capacity;
    }
    size = other.size;
    copy(other.begin(), other.end(), begin());
}

// Move operator
template<typename T>
void SimpleVector<T>::operator=(SimpleVector<T> &&other){
    
    delete [] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
const T& SimpleVector<T>::operator[](size_t idx) const{
    return data[idx];
}

template<typename T>
T& SimpleVector<T>::operator[](size_t idx){
    return data[idx];
}

template<typename T>
const T* SimpleVector<T>::begin() const{
    return data;
}

template<typename T>
T* SimpleVector<T>::begin(){
    return data;
}

template<typename T>
const T* SimpleVector<T>::end() const{
    return data + size;
}

template<typename T>
T* SimpleVector<T>::end(){
    return data + size;
}

template<typename T>
size_t SimpleVector<T>::Size() const{
    return size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const{
    return capacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value){
    if( size >= capacity ){
        auto new_cap = 0;
        if( capacity == 0 ){
            new_cap = 1;
        }
        else{
            new_cap = 2 * capacity;
        }
        capacity = new_cap;

        auto new_data = new T[new_cap];
        copy(begin(), end(), new_data);
        delete [] data;
        data = new_data;
    }
    data[size++] = value;
}

template<typename T>
SimpleVector<T>::~SimpleVector(){
    if (data != nullptr){
        delete [] data;
    }
}



int main(){


  return 0;
}