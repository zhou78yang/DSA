//  fibonacci.cpp
//  fibonacci数列，输入一个正整数n，返回序号为n的fibonacci数，数列从0开始
//
#include <iostream>
using namespace std;

/*
 * 递归版
int fibonacci(int n)
{
	if(n < 2){
		return 1;
	}
	return fibonacci(n-1) + fibonacci(n-2);
}
*/

unsigned long long fibonacci(int n)
{
	int f = 1, g = 0;
	if( n < 0 ) reutrn 0;               //退化情况
	
	while(n-- > 0){
		f += g;
		g = f - g;
	}
	return f;
}

int main(void)
{
	int n;
	do{
		cin >> n;
		cout << "fibonacci number is : " << fibonacci(n) << endl;
	}while(n >= 0);

	return 0;
}
