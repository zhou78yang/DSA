#ifndef LIST_NODE_H_
#define LIST_NODE_H_

template <typename T> struct ListNode;
template <typename T> using Posi = ListNode<T>*;		// 列表结点位置

template <typename T>
struct ListNode
{
	T data;												// 结点数据
	Posi<T> pred, succ;									// 前驱和后继

	// 构造函数
	ListNode(){}										// 针对头尾结点构造
	ListNode(T e, Posi<T> p, Posi<T> s)
		:data(e), pred(p), succ(s){}					// 默认构造器
	
	// 操作接口
	Posi<T> insertAsPred(const T &e);					// 插入为前驱
	Posi<T> insertAsSucc(const T &e);					// 插入为后继
};


template <typename T>
Posi<T> ListNode<T>::insertAsPred(const T &e)
{
	Posi<T> n = new ListNode(e, pred, this);	// 创建新结点
	pred->succ = n; pred = n;	// 修改链接
	return n;
}

template <typename T>
Posi<T> ListNode<T>::insertAsSucc(const T &e)
{
	Posi<T> n = new ListNode(e, this, succ);	// 创建新结点
	succ->pred = n; succ = n;	// 修改链接
	return n;
}

#endif 