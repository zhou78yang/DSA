// quick_sort
#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

// partition() -> int :
//      return the pivotkey
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
    int left = lo, right = hi-1;
    while(left < right){
        while(left < right && A[right] >= pivot) right--;
        while(left < right && A[left] <= pivot) left++;
        if(left < right) swap(A[left], A[right]);
    }
    swap(A[lo], A[left]);
    return left;
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
