// bubble_sort test:

#include <iostream>
#include <ctime>
#include "bubble_sort.h"
using namespace std;

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n; // get array's length
    int *A = new int[n];
    srand(time(NULL));

    // get an array consist of random integers
    cout << "before: ";
    for(int i = 0; i < n; i++){
        A[i] = rand() % 100;
        cout << A[i] << ", " ;
    }
    cout << endl;

    BubbleSort<int>(A, 0, n);
    
    cout << "sorted: ";
    for(int i = 0; i < n; i++){
        cout << A[i] << ", ";
    }
    cout << endl;
    
    return 0;
}
