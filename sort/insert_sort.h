// insert_sort.h

#ifndef INSERT_SORT_H_
#define INSERT_SORT_H_

template <typename T>
void InsertSort(T *A, int lo, int hi)
{
    for(int i = lo+1; i < hi; i++){
        int pos = i; // 使用pos来存储当前需要插入元素的位置
        for(int j = i-1; j >= 0; --j){
            if(A[pos] < A[j]){
                std::swap(A[pos], A[j]);
                pos = j;
            }
        }
    }
}

#endif
