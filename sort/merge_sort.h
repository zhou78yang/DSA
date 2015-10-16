// merge_sort
#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

// merge :
//      merge A[lo, mi) and A[mi, hi)
template <typename T>
void Merge(T *A, int lo, int mi, int hi)
{
    int lb = mi - lo, lc = hi - mi;
    T *B = new T[lb];                   // B = A[lo, mi)
    T *C = A + mi;                      // C = A[mi, hi)
    int ia = lo, ib = 0, ic = 0;
    
    // copy A[lo, mi) to B[0, lb)
    for(int i = 0; i < lb; i++) B[i] = A[ia+i];

    while(ib < lb && ic < lc){
        if(B[ib] < C[ic]){
            A[ia++] = B[ib++];
        }
        else{
            A[ia++] = C[ic++];
        }
    }
    while(ib < lb) A[ia++] = B[ib++];   

	delete[] B;
}	

// merge_sort:
//      sort A[lo, hi)
template <typename T>
void MergeSort(T *A, int lo, int hi)
{
    if(hi - lo < 2) return ;

    int mi = (lo + hi) / 2;
    MergeSort(A, lo, mi);
    MergeSort(A, mi, hi);
    Merge(A, lo, mi, hi);
}

#endif
