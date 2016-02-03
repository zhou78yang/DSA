#include <cstdlib>
#include "listnode.h"

#ifndef LIST_H_
#define LIST_H_

typedef int				Rank;								// �б����

template <typename T>
class List
{
protected:
	int  _size;												// ��ģ
	Posi<T> header, trailer;								// ͷ�ڱ���β�ڱ�

protected:
	void init();											// �б��ʼ��
	int  clear();											// ������н��
	void copyNodes(Posi<T>, int);							// ����ĳ�����
	void merge(Posi<T> &, int, List<T> &, Posi<T>, int);	// �鲢
	void mergeSort(Posi<T> &, int);							// �鲢����
	void selectionSort(Posi<T> &, int);						// ѡ������
	void insertionSort(Posi<T> &, int);						// ��������
	int partition(Posi<T> &, int, Posi<T> &);				// ���ŷֶ�
	void quickSort(Posi<T> &, int);							// ��������

public:
	// ���캯��
	List(){ init(); }										// Ĭ��
	List(const List<T> &L){	copyNodes(L.first(), L._size); }// �б��ƹ���
	List(const List<T> &L, Rank r, int n){ copyNodes(L.getNode(r), n); }
	List(Posi<T> p, int n){ copyNodes(p, n); }				// �����ʽ����
	// ��������
	~List(){ clear(); delete header, trailer; }		
	
	// ֻ�����ʽӿ�
	Rank size() const{ return _size; }						// ��ģ
	bool empty() const{ return _size <= 0; }				// �ж��Ƿ�Ϊ��
	Posi<T> first() const{ return header->succ; }			// �׽��λ��
	Posi<T> last() const{ return trailer->pred; }			// ĩ���λ��
	bool valid(Posi<T> p) const
	{
		return p && (trailer != p) && (header != p);		// �ж�p�Ƿ�Ϸ�
	}
	int  disordered() const;								// �ж��Ƿ�����
	Posi<T> find(const T &e) const;							// �����б����
	Posi<T> find(const T &e, Posi<T> p, int n) const;		// ����˳�β���
	Posi<T> find(const T &e, int n, Posi<T> p) const;		// �����������
	Posi<T> search(const T &e) const;						// �����б����
	Posi<T> search(const T &e, Posi<T> p, int n) const;		// ����˳�β���
	Posi<T> search(const T &e, int n, Posi<T> p) const;		// �����������
	Posi<T> selectMax(Posi<T> p, int n);					// �������ֵ
	Posi<T> selectMax(){ return selectMax(header->succ, _size); }// �б����ֵ

	// ��д���ʽӿ�
	T &operator [] (Rank r) const;							// �����±������
	Posi<T> &getNode(Rank r) const;							// ��ȡ�б���
	Posi<T> insertAsFirst(const T &e);						// ��Ϊ�׽�����
	Posi<T> insertAsLast(const T &e);						// ��Ϊĩ������
	Posi<T> insertA(Posi<T> p, const T &e);					// ��e���뵽p��
	Posi<T> insertB(Posi<T> p, const T &e);					// ��e���뵽pǰ
	T remove(Posi<T> p);									// ɾ�����p
	void merge(List<T> &L)
	{
		merge(header->succ, _size, L, L.first(), L._size);	// ȫ�б�鲢
	}
	void sort(Posi<T> p, int n);							// �б���������
	void sort(){ sort(first(), _size); }					// �б�ȫ������
	int  deduplicate();										// ����ȥ��
	int  uniquify();										// ����ȥ��
	void reverse();											// ǰ����

	// ����
	void traverse(void(*)(T &));							// ����ָ�����
	template <typename VST> void traverse(VST &);			// �������ñ���

};// List


///////////////////////////////////////////////////////////////////////////
// protected����

template <typename T>
void List<T>::init()
{
	// ���б���г�ʼ��
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
	init();	// ��ʼ���б�
	while (0 < n--)
	{
		insertAsLast(p->data);	// ˳�β���
		p = p->succ;
	}
}

template <typename T>
int List<T>::partition(Posi<T> &p, int n, Posi<T> &q)
{
	// pΪδ������������㣬nΪ�����г���
	// ����pָ��ǰ�����㣬qָ��������
	int m = 0;	// �����pС�Ľ�����
	Posi<T> head = p->pred;	// ��¼ͷ���
	q = p->succ;
	for (int i = 1; i < n; i++)
	{
		// ����n-1�αȶԣ�����pС�Ľ����뵽pǰ
		q = q->succ;
		if (p->data > q->pred->data)
		{
			insertB(p, remove(q->pred));
			m++;
		}
	}
	q = p->succ;	// qΪ�������
	p = head->succ;	// p�ָ�Ϊ���б����
	return m;	// ���غ�һ�����б�ĳ���
}

template <typename T>
void List<T>::quickSort(Posi<T> &p, int n)
{
	// �������򣬶Դ�p��ʼ��n������������
	// Ҫ��p����ָ�������б�����
	if (n < 2) return;
	Posi<T> q;	// ����List���ʵĲ����ԣ�����q����ȡ�������
	int m = partition(p, n, q);	// m�洢ǰ��γ���
	quickSort(p, m); 
	quickSort(q, n - m - 1);
}

template <typename T>
void List<T>::merge(Posi<T> &p, int la, List<T> &L, Posi<T> b, int lb)
{
	// pΪ�б��е�ĳ����㣬laΪ���б���
	// bΪ�б�L�е�ĳ����㣬lbΪ���б���
	Posi<T> head = p->pred;	// ��¼�鲢�����ǰ���
	Posi<T> a = p;	// p��ֵ����
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
			insertB(a, L.remove(b->pred));	// ���뵽aǰ
		}			
	}
	p = head->succ;	// ��p�ָ�Ϊ�鲢������׽��
}

template <typename T>
void List<T>::mergeSort(Posi<T> &p, int n)
{
	// �鲢����ʵ�ִ�p��ʼ��n����������
	if (n < 2) return;
	int m = n / 2;
	Posi<T> q = p;
	for (int i = 0; i < m; i++) q = q->succ;// �����б�
	mergeSort(p, m); mergeSort(q, n - m);	// ������������
	merge(p, m, *this, q, n - m);	// �鲢
}

template <typename T>
void List<T>::selectionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred; Posi<T> tail = p;	// ͷ��β���
	for (int i = 0; i < n; i++) tail = tail->succ;	// ��������[p, tail)
	while (1 < n)
	{
		Posi<T> q = selectMax(head->succ, n);// ���������е����ֵ
		insertB(tail, remove(q));	// �����ֵ���뵽δ���򲿷�ĩβ
		tail = tail->pred; n--;		// ����δ���򲿷�
	}
}

template <typename T>
void List<T>::insertionSort(Posi<T> &p, int n)
{
	Posi<T> head = p->pred, tail = p, q = p->succ;	// ͷ��β����������
	for (int i = 0; i < n; i++) tail = tail->succ;	// tailΪĩ���ĺ��
	while (q != tail)
	{
		Posi<T> r = q->pred;
		while (r != head && r->data > q->data) r = r->pred;	// �ҵ�����λ��
		insertA(r, q->data);	// ���뵽r�ĺ���
		q = q->succ; remove(q->pred);	// qָ����һ������ɾ��֮ǰ������
	}
}


///////////////////////////////////////////////////////////////////////////
// ֻ�����ʽӿ�

template <typename T>
int List<T>::disordered() const
{
	int c = 0;	// ��������¼
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
	// �������
	return find(e, _size, trailer);
}

template <typename T>
Posi<T> List<T>::find(const T &e, Posi<T> p, int n) const
{
	// ����p��n�����棩��̣���p��Ϊheader������
	while (0 < n--)
	{
		if (e == (p = p->succ)->data) return p;
	}
	return NULL;;
}

template <typename T>
Posi<T> List<T>::find(const T &e, int n, Posi<T> p) const
{
	// ����p��n�����棩ǰ������p��Ϊtrailer������
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e) const
{
	return search(e, _size, trailer);	// ��������
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
	// ��ѡ��p��ʼ��n��Ԫ�ص����ֵ
	Posi<T> max = p;
	while (1 < n--)
	{
		if ((p = p->succ)->data > max->data) max = p;
	}
	return max;
}


/////////////////////////////////////////////////////////////////////////
// ��д���ʽӿ�

template <typename T>
T &List<T>::operator [] (Rank r) const
{
	// �б��н���ֵ��ӳ�䣬Ч�ʵ��£���������
	Posi<T> p = first();	// ���׽�����
	while (0 < r--) p = p->succ;	// ˳����r�����
	return p->data;	// ���ؽ������
}

template <typename T>
Posi<T> &List<T>::getNode(Rank r) const
{
	// �����б�Ľ��
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
	T e = p->data;	// ���ݱ���
	p->pred->succ = p->succ;	// pǰ���ĺ�̱�Ϊp�ĺ��
	p->succ->pred = p->pred;	// p��̵�ǰ����Ϊp��ǰ��
	delete p;	// �ͷ�p�Ŀռ�
	_size--;	// ��ģ��С
	return e;
}

template <typename T>
void List<T>::sort(Posi<T> p, int n)
{
	// ����ʼλ��Ϊp��n��Ԫ�ؽ�������
	quickSort(p, n); return;
	switch (rand() % 3)
	{
	// ���ѡ������ʽ
	case 1: insertionSort(p, n); break;
	case 2: selectionSort(p, n); break;
	case 3: quickSort(p, n); break;
	default: mergeSort(p, n); break;
	}

}

template <typename T>
int List<T>::deduplicate()
{
	// �����б��ȥ�ز���
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header; Rank r = 0;
	while (trailer != (p = p->succ))
	{
		Posi<T> q = find(p->data, r, p);// ����pǰ��r��Ԫ��
		q ? remove(q) : r++;	// ��q������ɾ��q
	}
	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
	// �����б��ȥ�ز���
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi<T> p = header->succ; Posi<T> q;
	while (trailer != (q = p->succ))
	{
		// �����������ڽ���p��q
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