// sort test:

#include <iostream>
#include <ctime>
#include "????_sort.h"

using namespace std;

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n; // 获取数组长度
    int *A = new int[n];
    srand(time(NULL));

    // 获取一个长度为n的随机数组
    cout << "befort: " ;
    for(int i = 0; i < n; i++){
        A[i] = rand() % 100;
        cout << A[i] << ", " ;
    }
    cout << endl;

    ????Sort<int>(A, 0, n);

    cout << "sorted: " ;
    for(int i = 0; i < n; i++){
        cout << A[i] << ", " ;
    }
    cout << endl;

    return 0;
}
