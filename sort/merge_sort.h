// merge_sort
#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include "swap.h"

// merge A[lo, mi) and A[mi, hi)
template <typename T>
void merge(T *A, int lo, int mi, int hi)
{
	int lb = mi - lo;
	int lc = hi - mi;
	T *a = A + lo;
	T *b = new T[lb];		// part [lo, mi)
	T *c = A + mi;			// part [mi, hi)
	int ia = 0;
	int ib = 0; 
	int ic = 0;

	// copy a[0:lb] to b
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

// merge_sort: range A[lo, hi)
template <typename T>
void merge_sort(T *A, int lo, int hi)
{
	if(hi - lo < 2) return;

	int mi = (lo + hi) / 2;
	merge_sort(A, lo, mi);
	merge_sort(A, mi, hi);
	merge(A, lo, mi, hi);
}

#endif
