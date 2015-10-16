// vector test:

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "vector.hpp"

using namespace std;

int *getArray(int n)
{
    srand(time(NULL));
    int *A = new int[n];
    for(int i = 0; i < n; i++){
        A[i] = rand() % 100;
    }
    return A;
}

void visit(int &i)
{
    cout << i << ", ";
}

void show(Vector<int> v)
{
    cout << "Vector: " ;
    v.traverse(visit);
    cout << endl;
}

int main(int argc, char **argv)
{
    int n = 0;
    cout << "input n: " ;
    cin >> n;
    int *A = getArray(n);

    Vector<int> v(A, n);

    cout << "the initialize sequence:" << endl;
    show(v);

    cout << "sort test......" << endl;
    v.sort();
    show(v);

    cout << "unsort test......" << endl;
    v.unsort();
    show(v);

    cout << "find test......" << endl;
    cout << "input num: " ;
    int e;
    cin >> e;
    cout << "the result: " << v.find(e) << endl;

    cout << "insert test......" << endl;
    cout << "input item: " ;
    cin >> e;
    cout << "input post: " ;
    int r;
    cin >> r;
    v.insert(r, e);
    cout << "show result:" << endl;
    show(v);


    return 0;
}


