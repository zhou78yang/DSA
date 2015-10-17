#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <cstdlib>
#include "../sort/bubble_sort.h"
#include "../sort/quick_sort.h"
#include "../sort/merge_sort.h"
#include "../sort/selection_sort.h"
#include "../sort/heap_sort.h"
#include "../search/bin_search.h"


typedef     int                 Rank;           // 元素的秩
#define     DEFAULT_CAPACITY    3               // 初始向量容量

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
    Rank _size;                             // 元素个数
    int  _capacity;                         // 向量容量
    T*   _elem;                             // 元素数组

};

//////////////////////////////////////////////////////
// 只读接口

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

// 查看序列是否有序，返回序列的逆序数
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

// find：查找指定元素，适用于乱序序列
//      返回元素的rank，如果没有找到，则返回-1
template <typename T>
Rank Vector<T>::find(const T &e) const
{
    return find(e, 0, _size);
}

// 范围find
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

// search：查找指定元素，适用于顺序序列
//      返回查找元素的rank，如果没有找到，则返回-1
template <typename T>
Rank Vector<T>::search(const T &e) const
{
    return search(e, 0, _size);
}

// 范围search
template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const
{
    return BinSearch(_elem, e, lo, hi);
}


/////////////////////////////////////////////////
// 可写接口

// 重载运算符 [] 
template <typename T>
T& Vector<T>::operator [](Rank r) const
{
    return _elem[r];
}

// 重载运算符 =
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

// remove：删除制定rank所在的元素
//      返回删除元素的值
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

// 删除一段序列，并返回删除元素个数
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

// 向指定位置插入元素e，默认插入到序列最后
template <typename T>
Rank Vector<T>::insert(const T &e)
{
    return insert(_size, e);
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
    expand();// 插入前，先检查是否需要扩容

    for(int i = _size; i > r; i--){
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size++;

    return r;
}

// sort：给向量排序，随机选择排序算法
template <typename T>
void Vector<T>::sort()
{
    sort(0, _size);
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    // 随机选择排序算法
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

// unsort：使向量元素乱序，可选全局或者区域
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

// deduplicate：无序向量唯一化，删除重复的元素
//      返回删除元素个数
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

// uniquify：有序向量唯一化，删除重复的元素
//      返回删除元素个数
template <typename T>
int Vector<T>::uniquify()
{
    int old_size = _size;
    int j = 0;// 新序列的索引,通过此方式使时间复杂度降到O(n)
    for(int i = 0; i < _size; i++){
        if(_elem[i] != _elem[j]){
            _elem[++j] = _elem[i];
        }
    }
    _size = j + 1;
    shrink();// 结束时，检查缩容

    return old_size - _size;
}

// traverse：遍历函数
//      参数：visit，遍历单个元素所用的函数，可传入函数指针或函数引用
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

////////////////////////////////////////////////////
// protected methods

// copyFrom：将数组复制到向量
//      参数：传入一个数组A,复制范围A[lo, hi)
//      将向量内容改为A[lo, hi)
template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi)
{
    _size = 0;
    _capacity = (hi - lo) * 2;// 新建空间为传入数组长度的两倍
    _elem = new T[_capacity];

    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

// expand：扩容函数，空间不够是扩容
template <typename T>
void Vector<T>::expand()
{
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    if(_size < _capacity) return ;
    
    T *old_elem = _elem;
    _capacity *= 2;// 空间变为原来的两倍
    _elem = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _elem[i] = old_elem[i];
    }

    delete[] old_elem;
}

// shrink：缩容函数，当空间利用率低于25%时缩容
template <typename T>
void Vector<T>::shrink()
{
    if(_size * 4 > _capacity) return ;
    T *old_elem = _elem;
    _capacity /= 2;// 空间变为原来的一半
    _elem = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _elem[i] = old_elem[i];
    }

    delete[] old_elem;
}

// bubbleSort：冒泡排序
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    BubbleSort<T>(_elem, lo, hi);
}

// max：返回[lo, hi)中的最大值
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

// selectionSort：选择排序
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
    SelectionSort<T>(_elem, lo, hi);
}

// mergeSort：归并排序
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    MergeSort<T>(_elem, lo, hi);
}

// quickSort：快速排序
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{
    QuickSort<T>(_elem, lo, hi);
}

// heapSort：希尔排序
template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
    HeapSort<T>(_elem, lo, hi);
}


#endif
