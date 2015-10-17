// bin_search.h

#ifndef BIN_SEARCH_H_
#define BIN_SEARCH_H_

// BinSearch -> int :
//      二分查找：查找范围A[lo, hi), 查找元素e,适用于顺序序列
//      返回元素位置，当找不到元素时返回-1
template <typename T>
int BinSearch(const T *A, T e, int lo, int hi)
{
    while(hi - lo > 1){
        int mi = (lo + hi) / 2;
        (e < A[mi]) ? hi = mi : lo = mi;  //选择深入[lo, mi)或[mi, hi)
    }
    return (e == A[lo]) ? lo : -1;
}

#endif
