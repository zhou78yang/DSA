#ifndef LIST_NODE_H_
#define LIST_NODE_H_

template <typename T> struct ListNode;
template <typename T> using Posi = ListNode<T>*;		// �б���λ��

template <typename T>
struct ListNode
{
	T data;												// �������
	Posi<T> pred, succ;									// ǰ���ͺ��

	// ���캯��
	ListNode(){}										// ���ͷβ��㹹��
	ListNode(T e, Posi<T> p, Posi<T> s)
		:data(e), pred(p), succ(s){}					// Ĭ�Ϲ�����
	
	// �����ӿ�
	Posi<T> insertAsPred(const T &e);					// ����Ϊǰ��
	Posi<T> insertAsSucc(const T &e);					// ����Ϊ���
};


template <typename T>
Posi<T> ListNode<T>::insertAsPred(const T &e)
{
	Posi<T> n = new ListNode(e, pred, this);	// �����½��
	pred->succ = n; pred = n;	// �޸�����
	return n;
}

template <typename T>
Posi<T> ListNode<T>::insertAsSucc(const T &e)
{
	Posi<T> n = new ListNode(e, this, succ);	// �����½��
	succ->pred = n; succ = n;	// �޸�����
	return n;
}

#endif 