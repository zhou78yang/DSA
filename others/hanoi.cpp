//  hanoi.cpp
//  汉诺塔问题
//
#include <iostream>
using namespace std;

void move(char src, char dest)
{
	cout << src << "-->" << dest << endl;
}

void hanoi(int n, char src, char medium, char dest)
{
	if(n < 1) return;
	if(1 == n)
		move(src, dest);
	else{
		hanoi(n-1, src, dest, medium);
		move(src, dest);
		hanoi(n-1, medium, src, dest);
	}
}

int main(void)
{
	int n;
	do{
		cin >> n;
		cout << "hanoi begin..." << endl;
		hanoi(n, 'A', 'B', 'C');
		cout << "hanoi end..." << endl;
	}while(n > 0);
	
	return 0;
}    
