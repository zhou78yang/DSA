#include <iostream>
#include <ctime>
#include <cstdlib>

#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

using namespace std;

int *getArray(int);
void showArray(int*, int);

int main(int argc, char **argv)
{
	cout << "this is bubble_sort test:" << endl;
	cout << "input n:" ;
	int n;
	cin >> n;
	int *A = getArray(n);
	showArray(A, n);
	bubble_sort<int>(A, 0, n);
	showArray(A, n);
	cout << "bubble_sort end......" << endl;

	cout << "this is merge_sort test:" << endl;
	cout << "input n:" ;
	cin >> n;
	A = getArray(n);
	showArray(A, n);
	merge_sort<int>(A, 0, n);
	showArray(A, n);
	cout << "merge_sort end......" << endl;

	cout << "this is quick_sort test:" << endl;
	cout << "input n:" ;
	cin >> n;
	A = getArray(n);
	showArray(A, n);
	quick_sort<int>(A, 0, n);
	showArray(A, n);
	cout << "quick_sort end......" << endl;

	return 0;
}

int *getArray(int n)
{
	int *ret = new int[n];
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		ret[i] = rand() % 100;
	}
	return ret;
}

void showArray(int *A, int n)
{
	for(int i = 0; i < n; i++){
		cout << A[i] << ", ";
	}
	cout << endl;
}
