// order_search.h

#ifndef ORDER_SEARCH_H_
#define ORDER_SEARCH_H_

// OrderSearch -> int :
//      顺序查找：查找范围A[lo, hi)，查找元素e,适用与乱序数组
//      返回元素位置，当找不到元素时返回-1
template <typename T>
int OrderSearch(const T *A, T e, int lo, int hi)
{
    for(int i = lo; i < hi; i++){
        if(A[i] == e){
            return i; // 找到该元素时返回元素所在位置
        }
    }
    return -1;  // 找不到元素的时候返回-1
}

#endif
