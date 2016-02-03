// numerial convertion
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../stack/stack.h"

using namespace std;

void convert(Stack<char> &S, long long n, int base)
{
    if(base < 2 || base > 16) 
    {
        cerr << "base out of range(2-16)!" << endl;
        return ;
    }

    const char Base[16] = { '0', '1', '2', '3', 
        '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F' };

    while( 0 < n)
    {
        S.push(Base[n % base]);
        n /= base;
    }
}


int main()
{
    Stack<char> S;
    cout << "input num:  ";
    long long n; cin >> n;
    cout << "input base: ";
    int base; cin >> base;

    convert(S, n, base);

    cout << "converted: ";
    while(!S.empty()) cout << S.pop();
    cout << endl;

    return 0;
}

