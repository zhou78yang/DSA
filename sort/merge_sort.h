// merge_sort
#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include "swap.h"

template <typename T>
void merge(T *A, int lo, int mi, int hi)
{
	int lb = mi - lo;
	int lc = hi - mi;
	T *a = A + lo;
	T *b = new T[lb];
	T *c = A + mi;
	int ia = 0;
	int ib = 0; 
	int ic = 0;

	for(int i = 0; i < lb; i++) b[i] = a[i];
	while(ib < lb && ic < lc){
		if(c[ic] < b[ib]){
			a[ia++] = c[ic++];
		}
		else{
			a[ia++] = b[ib++];
		}
	}
	while(ib < lb) a[ia++] = b[ib++];

	delete[] b;
}	

template <typename T>
void merge_sort(T *A, int lo, int hi)
{
	//merge sort: Array range [lo, hi)
	if(hi - lo < 2) return;

	int mi = (lo + hi) / 2;
	merge_sort(A, lo, mi);
	merge_sort(A, mi, hi);
	merge(A, lo, mi, hi);
}

#endif
