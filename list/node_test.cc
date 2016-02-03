// node test

#include <iostream>
#include "list_node.h"

using namespace std;


int main(int argc, char **argv)
{
    ListNodePosi<int> header = new ListNode<int>();
    ListNodePosi<int> trailer = new ListNode<int>();
    header->pre = NULL;
    header->next = trailer;
    trailer->next = NULL;
    trailer->pre = header;

    int A[5] = { 12, 24, 44, 52, 13 };
    for(int i = 0; i < 5; i++)
    {
        header->insertAsNext(A[i]);// 逆序插入
    }

    cout << "print: ";
    for(auto p = header->next; p != trailer; p = p->next)
    {
        cout << p->data << ", " ;
    }
    cout << endl;

    return 0;
}
