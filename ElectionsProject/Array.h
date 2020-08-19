
#ifndef PLEASEFINAL_ARRAY_H
#define PLEASEFINAL_ARRAY_H
#include <iostream>
using namespace std;
const int INIT_ARR_SIZE = 1;
template<class T>
class Array
{
    int physicalSize, logicalSize;
    char delimiter;
    T* arr;

public:
    Array(int size = INIT_ARR_SIZE, char delimiter = ' ');
    Array(const Array& other);
    ~Array();

    const Array& operator=(const Array& other);
    const Array& operator+=(const T& newVal);

    void setSize(int size);
    int getSize() const;
    int getLogical();
    T* getArr();
    T& operator[](int index);
    const T& operator[](int index) const;

    friend ostream& operator<<(ostream& os, const Array& arr)
    {
        for (int i = 0; i < arr.logicalSize; i++)
            os << arr.arr[i] << arr.delimiter;
        return os;
    }
};

template<class T>
Array<T>::Array(int maxSize, char delimiter) : physicalSize(maxSize), logicalSize(0), delimiter(delimiter)
{
    arr = new T[physicalSize];
}


template<class T>
Array<T>::Array(const Array& other) : arr(nullptr)
{
    *this = other;
}

template<class T>
Array<T>::~Array()
{
    delete[]arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
    if (this != &other)
    {
        delete[]arr;
        physicalSize = other.physicalSize;
        logicalSize = other.logicalSize;
        delimiter = other.delimiter;
        arr = new T[physicalSize];
        for (int i = 0; i < logicalSize; i++)
            arr[i] = other.arr[i];
    }
    return *this;
}

//This operator supports the enlargement of the array indefinitely
template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
    if (logicalSize == physicalSize)
    {
        physicalSize *= 2;

        T* temp = new T[physicalSize];
        for (int i = 0; i < logicalSize; i++)
            temp[i] = arr[i];

        delete[]arr;
        arr = temp;
    }

    if (logicalSize < physicalSize)
        arr[logicalSize++] = newVal;
    return *this;
}

template<class T>
void Array<T>::setSize(int size)
{
    delete []arr;

    physicalSize = logicalSize = size;
    arr = new T[physicalSize];
}

template<class T>
T& Array<T>::operator[](int index)
{
    return arr[index];
}

template<class T>
const T& Array<T>::operator[](int index) const
{
    return arr[index];
}

template<class T>
int Array<T>::getSize() const {
    return physicalSize;
}

template<class T>
T* Array<T>::getArr()
{
    return arr;
}

template<class T>
int Array<T>::getLogical()
{
    return logicalSize;
}

#endif //PLEASEFINAL_ARRAY_H
