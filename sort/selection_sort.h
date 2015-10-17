// selection_sort.h

#ifndef SELECTION_SORT_H_
#define SELECTION_SORT_H_

template <typename T>
void SelectionSort(T *A, int lo, int hi)
{
    while(hi - lo > 1){
        int min = lo; 
        for(int i = lo+1; i < hi; i++){
            if(A[min] > A[i]){
                min = i;
            }
        }
        // 最小元素与最低位元素交换，然后lo自增1
        std::swap(A[min], A[lo++]); 
    }
}

#endif
