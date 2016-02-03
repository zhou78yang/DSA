#include <cstdlib>
#include "listnode.h"

#ifndef LIST_H_
#define LIST_H_

typedef int				Rank;								// 列表的秩

template <typename T>
class List
{
protected:
	int  _size;												// 规模
	Posi<T> header, trailer;								// 头哨兵和尾哨兵

protected:
	void init();											// 列表初始化
	int  clear();											// 清除所有结点
	void copyNodes(Posi<T>, int);							// 复制某串结点
	void merge(Posi<T> &, int, List<T> &, Posi<T>, int);	// 归并
	void mergeSort(Posi<T> &, int);							// 归并排序
	void selectionSort(Posi<T> &, int);						// 选择排序
	void insertionSort(Posi<T> &, int);						// 插入排序
	int partition(Posi<T> &, int, Posi<T> &);				// 快排分段
	void quickSort(Posi<T> &, int);							// 快速排序

public:
	// 构造函数
	List(){ init(); }										// 默认
	List(const List<T> &L){	copyNodes(L.first(), L._size); }// 列表复制构造
	List(const List<T> &L, Rank r, int n){ copyNodes(L.getNode(r), n); }
	List(Posi<T> p, int n){ copyNodes(p, n); }				// 结点形式构造
	// 析构函数
	~List(){ clear(); delete header, trailer; }		
	
	// 只读访问接口
	Rank size() const{ return _size; }						// 规模
	bool empty() const{ return _size <= 0; }				// 判断是否为空
	Posi<T> first() const{ return header->succ; }			// 首结点位置
	Posi<T> last() const{ return trailer->pred; }			// 末结点位置
	bool valid(Posi<T> p) const
	{
		return p && (trailer != p) && (header != p);		// 判断p是否合法
	}
	int  disordered() const;								// 判断是否有序
	Posi<T> find(const T &e) const;							// 无序列表查找
	Posi<T> find(const T &e, Posi<T> p, int n) const;		// 无序顺次查找
	Posi<T> find(const T &e, int n, Posi<T> p) const;		// 无序逆向查找
	Posi<T> search(const T &e) const;						// 有序列表查找
	Posi<T> search(const T &e, Posi<T> p, int n) const;		// 有序顺次查找
	Posi<T> search(const T &e, int n, Posi<T> p) const;		// 有序逆向查找
	Posi<T> selectMax(Posi<T> p, int n);					// 区间最大值
	Posi<T> selectMax(){ return selectMax(header->succ, _size); }// 列表最大值

	// 可写访问接口
	T &operator [] (Rank r) const;							// 重载下标运算符
	Posi<T> &getNode(Rank r) const;							// 获取列表结点
	Posi<T> insertAsFirst(const T &e);						// 作为首结点插入
	Posi<T> insertAsLast(const T &e);						// 作为末结点插入
	Posi<T> insertA(Posi<T> p, const T &e);					// 将e插入到p后
	Posi<T> insertB(Posi<T> p, const T &e);					// 将e插入到p前
	T remove(Posi<T> p);									// 删除结点p
	void merge(List<T> &L)
	{
		merge(header->succ, _size, L, L.first(), L._size);	// 全列表归并
	}
	void sort(Posi<T> p, int n);							// 列表区间排序
	void sort(){ sort(first(), _size); }					// 列表全局排序
	int  deduplicate();										// 无序去重
	int  uniquify();										// 有序去重
	void reverse();											// 前后倒置

	// 遍历
	void traverse(void(*)(T &));							// 函数指针遍历
	template <typename VST> void traverse(VST &);			// 函数引用遍历

};// List


///////////////////////////////////////////////////////////////////////////
// protected部分

template <typename T>
void List<T>::init()
{
	// 对列表进行初始化
	header = new ListNode<T>();
	trailer = new ListNode<T>();
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ);
	return oldSize;
}

template <typename T>
void List<T>::copyNodes(Posi<T> p, int n)
{
	init();	// 初始化列表
	while (0 < n--)
	{
		insertAsLast(p->data);	// 顺次插入
		p = p->succ;
	}
}

template <typename T>
int List<T>::partition(Posi<T> &p, int n, Posi<T> &q)
{
	// p为未排序子序列起点，n为子序列长度
	// 最终p指向前半段起点，q指向后半段起点
	int m = 0;	// 计算比p小的结点个数
	Posi<T> head = p->pred;	// 记录头结点
	q = p->succ;
	for (int i = 1; i < n; i++)
	{
		// 进行n-1次比对，将比p小的结点插入到p前
		q = q->succ;
		if (p->data > q->pred->data)
		{
			insertB(p, remove(q->pred));
			m++;
		}
	}
	q = p->succ;	// q为后半段起点
	p = head->succ;	// p恢复为子列表起点
	return m;	// 返回后一段子列表的长度
}

template <typename T>
void List<T>::quickSort(Posi<T> &p, int n)
{
	// 快速排序，对从p开始的n个结点进行排序
	// 要求p最终指向有序列表的起点
	if (n < 2) return;
	Posi<T> q;	// 由于List访问的不便性，故用q来获取后半段起点
	int m = partition(p, n, q);	// m存储前半段长度
	quickSort(p, m); 
	quickSort(q, n - m - 1);
}

template <typename T>
void List<T>::merge(Posi<T> &p, int la, List<T> &L, Posi<T> b, int lb)
{
	// p为列表中的某个结点，la为子列表长度
	// b为列表L中的某个结点，lb为子列表长度
	Posi<T> head = p->pred;	// 记录归并区间的前结点
	Posi<T> a = p;	// p的值拷贝
	while (lb > 0)
	{
		if (la > 0 && (a->data <= b->data))
		{
			a = a->succ; la--;
			if (a == b) break;
		}
		else
		{
			b = b->succ; lb--;
			insertB(a, L.remove(b->pred));	// 插入到a前
		}			
	}
	p = head->succ;	// 将p恢复为归并区间的首结点
}

template <typename T>
void List<T>::mergeSort(Posi<T> &p, int n)
{
	// 归并排序，实现从p开始的n个结点的排序
	if (n < 2) return;
	int m = n / 2;
	Posi<T> q = p;
	for (int i = 0; i < m; i++) q = q->succ;// 均分列表
	mergeSort(p, m); mergeSort(q, n - m);	// 划分两段排序
	merge(p, m, *this, q, n - m);	// 归并
}

template <typename T>
void List<T>::selectionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred; Posi<T> tail = p;	// 头、尾结点
	for (int i = 0; i < n; i++) tail = tail->succ;	// 待排区间[p, tail)
	while (1 < n)
	{
		Posi<T> q = selectMax(head->succ, n);// 待排区间中的最大值
		insertB(tail, remove(q));	// 将最大值插入到未排序部分末尾
		tail = tail->pred; n--;		// 收缩未排序部分
	}
}

template <typename T>
void List<T>::insertionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred, tail = p, q = p->succ;	// 头、尾、待插入结点
	for (int i = 0; i < n; i++) tail = tail->succ;	// tail为末结点的后继
	while (q != tail)
	{
		Posi<T> r = q->pred;
		while (r != head && r->data > q->data) r = r->pred;	// 找到插入位置
		insertA(r, q->data);	// 插入到r的后面
		q = q->succ; remove(q->pred);	// q指向下一个，并删除之前插入结点
	}
}


///////////////////////////////////////////////////////////////////////////
// 只读访问接口

template <typename T>
int List<T>::disordered() const
{
	int c = 0;	// 逆序数记录
	Posi<T> p = first();
	while (trailer != p->succ)
	{
		if (p->data > p->succ->data) c++;
	}
	return c;
}

template <typename T>
Posi<T> List<T>::find(const T &e) const
{
	// 逆向查找
	return find(e, _size, trailer);
}

template <typename T>
Posi<T> List<T>::find(const T &e, Posi<T> p, int n) const
{
	// 查找p的n个（真）后继，即p作为header的链表
	while (0 < n--)
	{
		if (e == (p = p->succ)->data) return p;
	}
	return NULL;;
}

template <typename T>
Posi<T> List<T>::find(const T &e, int n, Posi<T> p) const
{
	// 查找p的n个（真）前驱，即p作为trailer的链表
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e) const
{
	return search(e, _size, trailer);	// 逆向搜索
}

template <typename T>
Posi<T> List<T>::search(const T &e, Posi<T> p, int n) const
{
	while (0 < n-- && (p = p->succ)->data < e);
	return p->data == e ? p : NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e, int n, Posi<T> p) const
{
	while (0 < n-- && (p = p->pred)->data > e);
	return p->data == e ? p : NULL;
}

template <typename T>
Posi<T> List<T>::selectMax(Posi<T> p, int n)
{
	// 挑选从p开始的n个元素的最大值
	Posi<T> max = p;
	while (1 < n--)
	{
		if ((p = p->succ)->data > max->data) max = p;
	}
	return max;
}


/////////////////////////////////////////////////////////////////////////
// 可写访问接口

template <typename T>
T &List<T>::operator [] (Rank r) const
{
	// 列表中结点的值的映射，效率低下，尽量少用
	Posi<T> p = first();	// 从首结点出发
	while (0 < r--) p = p->succ;	// 顺数第r个结点
	return p->data;	// 返回结点内容
}

template <typename T>
Posi<T> &List<T>::getNode(Rank r) const
{
	// 返回列表的结点
	Posi<T> p = first();
	while (0 < r--) p = p->succ;
	return p;
}

template <typename T>
Posi<T> List<T>::insertAsFirst(const T &e)
{ 
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
Posi<T> List<T>::insertAsLast(const T &e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template <typename T>
Posi<T> List<T>::insertA(Posi<T> p, const T &e)
{
	// insert after
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
Posi<T> List<T>::insertB(Posi<T> p, const T &e)
{
	// insert before
	_size++;
	return p->insertAsPred(e);
}

template <typename T>
T List<T>::remove(Posi<T> p)
{
	T e = p->data;	// 数据备份
	p->pred->succ = p->succ;	// p前驱的后继变为p的后继
	p->succ->pred = p->pred;	// p后继的前驱变为p的前驱
	delete p;	// 释放p的空间
	_size--;	// 规模减小
	return e;
}

template <typename T>
void List<T>::sort(Posi<T> p, int n)
{
	// 对起始位置为p的n个元素进行排序
	quickSort(p, n); return;
	switch (rand() % 3)
	{
	// 随机选择排序方式
	case 1: insertionSort(p, n); break;
	case 2: selectionSort(p, n); break;
	case 3: quickSort(p, n); break;
	default: mergeSort(p, n); break;
	}

}

template <typename T>
int List<T>::deduplicate()
{
	// 无序列表的去重操作
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header; Rank r = 0;
	while (trailer != (p = p->succ))
	{
		Posi<T> q = find(p->data, r, p);// 查找p前的r个元素
		q ? remove(q) : r++;	// 若q存在则删除q
	}
	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
	// 有序列表的去重操作
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header->succ; Posi<T> q;
	while (trailer != (q = p->succ))
	{
		// 反复考查相邻结点对p和q
		if (p->data == q->data) remove(q);
		else p = q;
	}
	return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void(*visit)(T &))
{
	for (auto p = first(); p != trailer; p = p->succ) visit(p->data);
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit)
{
	for (auto p = first(); p != trailer; p = p->succ) visit(p->data);
}


#endif