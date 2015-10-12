#include <iostream>
using namespace std;

template <typename T>
class Vector
{
protected:
	T* _elem;
	int _size;
	int _capacity;
	void merge(int lo, int mi, int hi);
	int partition(int lo, int hi);
public:
	Vector(const T* array, int n)
	{
		_elem = new T[n];
		for(int i = 0; i < n; i++)
		{
			_elem[i] = array[i]
		}
	}
	void merge_sort(int lo, int hi);
	void quick_sort(int lo, int hi);
};

template <typename T>
void Vector<T>::merge_sort(int lo, int hi)
{
	while(lo < hi){
		int mi = (hi + lo) / 2;
		merge_sort(lo, mi);
		merge_sort(mi, hi);
		merge(lo, mi, hi);
	}
}

template <typename T>
void Vector<T>::merge(int lo, int mi, int hi)
{
	int limit1 = mi;
	while(lo < limit1 && mi < hi){
		if(_elem[mi] < _elem[lo]){
			swap(_elem[mi], _elem[lo]);
		}
	}
}

template <typename T>
int partition(int lo, int hi)
{
	int x = _elem[lo];
	int i = lo;
	int j = hi;
	while(i < j){
		if(_elem[++i] > _elem[--j]){
			swap(_elem[i], _elem[j]);
		}

