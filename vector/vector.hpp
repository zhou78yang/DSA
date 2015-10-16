#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <cstdlib>
#include "../sort/bubble_sort.h"
#include "../sort/quick_sort.h"
#include "../sort/merge_sort.h"
#include "../sort/selection_sort.h"
#include "../sort/heap_sort.h"


typedef     int                 Rank;
#define     DEFAULT_CAPACITY    3

template <typename T> class Vector
{
public:
    // constructor
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) :
        _capacity(c), _size(s){
            _elem = new T[_capacity];
            for(int i = 0; i < _size; i++) _elem[i] = v;
        }
    Vector(const T *A, Rank n){
        copyFrom(A, 0, n);
    }
    Vector(const T *A, Rank lo, Rank hi){
        copyFrom(A, lo, hi);
    }
    Vector(const Vector<T> &V){
        copyFrom(V._elem, 0, V._size);
    }
    Vector(const Vector<T> &V, Rank lo, Rank hi){
        copyFrom(V._elem, lo, hi);
    }
    // destructor
    ~Vector(){ delete[] _elem; }

    // read-only methods
    Rank size() const;
    bool empty() const;
    int  disordered() const;
    Rank find(const T &e) const; // find in unsorted sequence
    Rank find(const T &e, Rank lo, Rank hi) const;
    Rank search(const T &e) const; // search in sorted sequence
    Rank search(const T &e, Rank lo, Rank hi) const;

    // read-write methods
    T&      operator [](Rank r) const;
    Vector<T> &operator = (const Vector<T> &);
    T       remove(Rank r);
    int     remove(Rank lo, Rank hi);
    Rank    insert(const T &e);
    Rank    insert(Rank r, const T &e);
    void    sort();
    void    sort(Rank lo, Rank hi);
    void    unsort();
    void    unsort(Rank lo, Rank hi);
    int     deduplicate();
    int     uniquify();
    void    traverse(void(*) (T &));
    template <typename VST> void traverse(VST&);

protected:
    void copyFrom(const T *A, Rank lo, Rank hi);
    void expand();
    void shrink();
    void bubbleSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);

protected:
    Rank _size;
    int  _capacity;
    T*   _elem;

};

// implements

template <typename T>
Rank Vector<T>::size() const
{
    return _size;
}

template <typename T>
bool Vector<T>::empty() const
{
    return _size == 0;
}

template <typename T>
int Vector<T>::disordered() const
{
    int res = 0;
    for(int i = 1; i < _size; i++){
        if(_elem[i] < _elem[i-1]){
            res++;
        }
    }
    return res;
}

template <typename T>
Rank Vector<T>::find(const T &e) const
{
    return find(e, 0, _size);
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{
    for(int i = lo; i < hi; i++){
        if(_elem[i] == e){
            return i;
        }
    }
    return -1;
}

template <typename T>
Rank Vector<T>::search(const T &e) const
{
    return search(e, 0, _size);
}

template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const
{
    return -1;
}

template <typename T>
T& Vector<T>::operator [](Rank r) const
{
    return _elem;
}

template <typename T>
Vector<T> &Vector<T>::operator = (const Vector<T> &v)
{
    _capacity = v._capacity;
    _size = v._size;
    if(_elem) delete[] _elem;
    _elem = new T[_capacity];
    copyFrom(v._elem, 0, _size);

    return *this;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T ret = _elem[r];
    for(int i = r; i < _size; i++){
        _elem[i] = _elem[i+1];
    }
    _size--;
    shrink();

    return ret;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    int new_size = lo;
    for(int i = hi; i < _size; i++){
        _elem[new_size++] = _elem[i];
    }
    _size = new_size;
    shrink();

    return hi - lo;
}

template <typename T>
Rank Vector<T>::insert(const T &e)
{
    return insert(_size, e);
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
    expand();

    for(int i = _size; i > r; i--){
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size++;

    return r;
}

template <typename T>
void Vector<T>::sort()
{
    sort(0, _size);
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    switch(rand() % 3)
    {
    case 0:
        bubbleSort(lo, hi); break;
    case 1:
        quickSort(lo, hi); break;
    case 2:
        mergeSort(lo, hi); break;
    case 3:
        selectionSort(lo, hi); break;
    case 4:
        heapSort(lo, hi); break;
    }
}

template <typename T>
void Vector<T>::unsort()
{
    unsort(0, _size);
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    int l = hi - lo;
    while(--l > 0){
        std::swap(_elem[lo+l], _elem[lo+rand()%l]);
    }
}

template <typename T>
int Vector<T>::deduplicate()
{
    int old_size = _size;
    for(int i = 1; i < _size; i++){
        if(find(0, i)){
            remove(i);
        }
    }

    return old_size - _size;
}

template <typename T>
int Vector<T>::uniquify()
{
    int old_size = _size;
    int j = 0;
    for(int i = 0; i < _size; i++){
        if(_elem[i] != _elem[j]){
            _elem[++j] = _elem[i];
        }
    }
    _size = j + 1;
    shrink();

    return old_size - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for(int i = 0; i < _size; i++){
        visit(_elem[i]);
    }
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for(int i = 0; i < _size; i++){
        visit(_elem[i]);
    }
}

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi)
{
    _size = 0;
    _capacity = (hi - lo) * 2;
    _elem = new T[_capacity];

    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::expand()
{
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    if(_size < _capacity) return ;
    
    T *old_elem = _elem;
    _capacity *= 2;
    _elem = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _elem[i] = old_elem[i];
    }

    delete[] old_elem;
}

template <typename T>
void Vector<T>::shrink()
{
    if(_size * 4 > _capacity) return ;
    T *old_elem = _elem;
    _capacity /= 2;
    _elem = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _elem[i] = old_elem[i];
    }

    delete[] old_elem;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    BubbleSort<T>(_elem, lo, hi);
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{
    int max = 0;
    for(int i = 1; i < _size; i++){
        if(_elem[i] > _elem[max]){
            max = i;
        }
    }
    return max;
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
    SelectionSort<T>(_elem, lo, hi);
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    MergeSort<T>(_elem, lo, hi);
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{
    QuickSort<T>(_elem, lo, hi);
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
    HeapSort<T>(_elem, lo, hi);
}


#endif
