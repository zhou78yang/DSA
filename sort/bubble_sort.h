// bubble_sort
#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include "swap.h"

// bubble_sort : 
//      sort range A[lo, hi)
template <typename T>
void bubble_sort(T *A, int lo, int hi)
{
	bool is_ordered = true;
	while(lo < --hi){
		is_ordered = true;
		for(int i = lo; i < hi; i++){
			if(A[i] > A[i+1]){
				swap(A[i], A[i+1]);
				is_ordered = false;
			}
		}
		if(is_ordered) break;
	}
}

#endif
