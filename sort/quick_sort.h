// quick_sort
#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "swap.h"

// partition: version_A, range A[lo, hi)
// return -> int : pivot
template <typename T>
int partition_A(T *A, int lo, int hi)
{
	int mi = lo;
	for(int i = lo+1; i < hi; i++){
		if(A[i] < A[lo]){
			swap(A[i], A[++mi]);
		}
	}
	swap(A[lo], A[mi]);
	return mi;
}

// partition: version_B, range A[lo, hi)
template <typename T>
int partition_B(T *A, int lo, int hi)
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

// quick_sort: range A[lo, hi)
template <typename T>
void quick_sort(T *A, int lo, int hi)
{
	if(hi - lo < 2) return ;

	int mi = partition_A(A, lo, hi);
	quick_sort(A, lo, mi);
	quick_sort(A, mi+1, hi);
}

#endif
