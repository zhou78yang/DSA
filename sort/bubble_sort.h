// bubble_sort
#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

// Bubble -> int :
//      return the last of the unsorted section
template <typename T>
int Bubble(T *A, int lo, int hi)
{
    int last = lo;
    while(++lo < hi){
        if(A[lo] < A[lo-1]){
            std::swap(A[lo], A[lo-1]);
            last = lo;
        }
    }
    return last;
}


// bubble_sort : 
//      sort A[lo, hi)
template <typename T>
void BubbleSort(T *A, int lo, int hi)
{
    while(lo < hi){
        hi = Bubble(A, lo, hi);
    }
}

#endif
