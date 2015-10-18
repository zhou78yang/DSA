//  lcs.cpp
//  longest common subsequence:最长功能子序列（非递归版）
//
#include <iostream>
#include <cstring>
using namespace std;

int lcs(char *a, int an, char *b, int bn)
{
	int **table = new int*[an+1];
	for(int i = 0; i <= an; i++)
		table[i] = new int[bn+1];
	for(int i = 0; i <= an; i++)
		table[i][0] = 0;

	cout << "lcs rect:" << endl << "  ";
	for(int i = 0; i <= bn; i++){
		table[0][i] = 0;
		cout << b[i] << " ";
	}
	cout << endl;		

	for(int i = 0; i < an; i++){
		cout << a[i] << " ";
		for(int j = 0; j < bn; j++){
			if(a[i] == b[j])
				table[i+1][j+1]  = table[i][j] + 1;
			else
				table[i+1][j+1] = table[i][j+1] > table[i+1][j] ?
					table[i][j+1] : table[i+1][j];
			cout << table[i][j] << " " ;
		}
		cout << endl;
	}
	return table[an][bn];
}

int main(void)
{
	char str1[] = "helloworld";
	char str2[] = "program";
	cout << "please input string:";
	cin >> str1;
	cout << "please input another string:";
	cin >> str2;
        cout << "the length of longest common subsequence is "
        	<< lcs(str1, strlen(str1), str2, strlen(str2)) << endl;
    return 0;
}
