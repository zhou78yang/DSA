// quick_sort
#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

// partition() -> int :
//      return the pivot
//      partition range A[lo, hi)
template <typename T>
int Partition(T *A, int lo, int hi)
{
    int mi = lo;
    for(int i = lo+1; i < hi; i++){
        if(A[i] < A[lo]){
            std::swap(A[i], A[++mi]);
        }
    }
    std::swap(A[lo], A[mi]);
    return mi;
}

// partition: version_B, range A[lo, hi)
template <typename T>
int Partition_B(T *A, int lo, int hi)
{
    T pivot = A[lo];
    while(lo < hi){
        while(lo < hi && A[--hi] >= pivot) ;
        A[lo] = A[hi];
        while(lo < hi && A[++lo] <= pivot) ;
        A[hi] = A[lo];
    }
    A[lo] = pivot;
    return lo;
}

// quick_sort:
//      sort range A[lo, hi)
template <typename T>
void QuickSort(T *A, int lo, int hi)
{
    if(hi - lo < 2) return ;

    int mi = Partition(A, lo, hi);
    QuickSort(A, lo, mi);
    QuickSort(A, mi+1, hi);
}

#endif
