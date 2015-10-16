#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <cstdlib>

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

#endif
