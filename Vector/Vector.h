#ifndef VECTOR_H
#define VECTOR_H

typedef		int					Rank;						//������
#define		DEFAULT_CAPACITY	3							//����Ĭ�ϳ�ʼ����

template <typename T> class Vector{
protected:													//�������ݲ���
	Rank	_size;											//��ģ
	int		_capacity;										//����
	T*		_elem;											//������
		
protected:													//���ú�������
	void	copyFrom(const T *A, Rank lo, Rank hi);			//������������A[lo, hi)
	void	expand();										//�ռ䲻��ʱ����
	void	shrink();										//װ�����ӹ�Сʱ����
	bool	bubble(Rank lo, Rank hi);						//ɨ�轻��
	void	bubbleSort(Rank lo, Rank hi);					//ð������
	Rank	max(Rank lo, Rank hi);							//ѡȡ[lo, hi)�����Ԫ��
	void	selectionSort(Rank lo, Rank hi);				//ѡ������
	void	merge(Rank lo, Rank mi, Rank hi);				//�鲢�㷨
	void	mergeSort(Rank lo, Rank hi);					//�鲢����
	Rank	partition(Rank lo, Rank hi);					//��㹹���㷨
	void	quickSort(Rank lo, Rank hi);					//��������
	void	heapSort(Rank lo, Rank hi);						//������

public:														//�ⲿ�ӿڲ���
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) :	//����Ϊc����ģΪs����ʼֵΪv
		_capacity(c), _size(s){
		_elem = new T[_capacity];
		for (auto &e : _elem)	e = v;
	}
	Vector(const T *A, Rank n){								//�������帴��
		copyFrom(A, 0, n);		
	}
	Vector(const T *A, Rank lo, Rank hi){					//�������临��
		copyFrom(A, lo, hi);
	}
	Vector(const Vector<T> *V){								//�������帴��
		copyFrom(V._elem, 0, V._size);
	}
	Vector(const Vector<T> *V, Rank lo, Rank hi){			//�������临��
		copyFrom(V.elem, lo, hi);
	}
	//��������
	~Vector(){ delete _elem[]; }							//�ͷ��ڴ�ռ�
	//ֻ�����ʽӿ�
	Rank	size() const;									//��ģ
	bool	empty() const;									//�ж��Ƿ�Ϊ��
	int		disordered() const;								//�ж��Ƿ����򣨷ǽ���
	Rank	find(const T &e) const;							//���������������
	Rank	find(const T &e, Rank lo, Rank hi) const;		//���������������
	Rank	search(const T &e) const;						//���������������
	Rank	search(const T &e, Rank lo, Rank hi) const;		//���������������
	//��д���ʽӿ�
	T&		operator [](Rank r) const;						//�����±��������ʹ�������������ʽ��д����
	Vector<T> &operator = (const Vector<T> &);				//���صȺ�����������ڿ���
	T		remove(Rank r);									//ɾ����Ϊr��Ԫ�أ�����ɾ����ֵ
	int     remove(Rank lo, Rank hi);						//ɾ��[lo, hi)�����Ԫ�أ�����ɾ������
	Rank	insert(const T &e);								//��ĩԪ�ز���
	Rank	insert(Rank r, const T &e);						//�ر�λ�ò���
	void	sort();											//��������
	void	sort(Rank lo, Rank hi);							//��������
	void	unsort();										//��������
	void    unsort(Rank lo, Rank hi);						//��������
	int		deduplicate();									//����ȥ��
	int     uniquify();										//����ȥ��
	//����
	void	traverse(void(*) (T &));						//������ʹ�ú���ָ�루ֻ������ֲ����޸ģ�
	template <typename VST> void traverse(VST&);			//������ʹ�ú������󣨿�ȫ���޸ģ�
};//Vector

#endif

