// quick_sort
#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "swap.h"

template <typename T>
int partition(T *A, int lo, int hi)
{
	int mi = lo;
	for(int i = lo+1; i < hi; i++){
		if(A[i] < A[lo]){
			swap(A[i], A[++mi]);
		}
	}
	swap(A[lo], A[mi]);
	return mi;//return the pivot
}

template <typename T>
void quick_sort(T *A, int lo, int hi)
{
	//quick sort: Array range [lo, hi)
	if(hi - lo < 2) return ;

	int mi = partition(A, lo, hi);
	quick_sort(A, lo, mi);
	quick_sort(A, mi+1, hi);
}

#endif
