#pragma once


#include <algorithm> 
#include <stdexcept> 

template<typename T>
class TArray
{
public:
    TArray(int initialCapacity = 5);
    ~TArray();
    void AddElement(const T& NewElement);
    T& GetElement(int Index);
    void RemoveElement(int Index);
    bool IsValidIndex(int Index) const;
    bool Contains(const T& Element) const;
    int Num() const;
private:
    void Resize();
    T* Data;
    int Capacity;
    int Size;
};

template<typename T>
TArray<T>::TArray(int initialCapacity)
    : Capacity(initialCapacity), Size(0)
{
    Data = new T[Capacity];
}

template<typename T>
TArray<T>::~TArray()
{
    delete[] Data;
}

template<typename T>
void TArray<T>::AddElement(const T& NewElement)
{
    if (Size >= Capacity)
    {
        Resize();
    }
    Data[Size++] = NewElement;
}

template<typename T>
T& TArray<T>::GetElement(int Index)
{
    if (!IsValidIndex(Index))
    {
        throw std::out_of_range("Index out of range");
    }
    return Data[Index];
}

template<typename T>
void TArray<T>::RemoveElement(int Index)
{
    if (!IsValidIndex(Index))
    {
        throw std::out_of_range("Index out of range");
    }
    for (int i = Index; i < Size - 1; ++i)
    {
        Data[i] = Data[i + 1];
    }
    --Size;
}

template<typename T>
bool TArray<T>::IsValidIndex(int Index) const
{
    return Index >= 0 && Index < Size;
}

template<typename T>
bool TArray<T>::Contains(const T& Element) const
{
    for (int i = 0; i < Size; ++i)
    {
        if (Data[i] == Element)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
int TArray<T>::Num() const
{
    return Size;
}

template<typename T>
void TArray<T>::Resize()
{
    int newCapacity = Capacity * 2;
    T* newData = new T[newCapacity];

    std::copy(Data, Data + Size, newData);

    delete[] Data;
    Data = newData;
    Capacity = newCapacity;
}
