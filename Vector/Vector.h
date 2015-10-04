#ifndef VECTOR_H
#define VECTOR_H

typedef		int					Rank;						//定义秩
#define		DEFAULT_CAPACITY	3							//定义默认初始容量

template <typename T> class Vector{
protected:													//基本数据部分
	Rank	_size;											//规模
	int		_capacity;										//容量
	T*		_elem;											//数据区
		
protected:													//内置函数部分
	void	copyFrom(const T *A, Rank lo, Rank hi);			//复制数据区间A[lo, hi)
	void	expand();										//空间不足时扩容
	void	shrink();										//装载因子过小时缩容
	bool	bubble(Rank lo, Rank hi);						//扫描交换
	void	bubbleSort(Rank lo, Rank hi);					//冒泡排序
	Rank	max(Rank lo, Rank hi);							//选取[lo, hi)内最大元素
	void	selectionSort(Rank lo, Rank hi);				//选择排序
	void	merge(Rank lo, Rank mi, Rank hi);				//归并算法
	void	mergeSort(Rank lo, Rank hi);					//归并排序
	Rank	partition(Rank lo, Rank hi);					//轴点构造算法
	void	quickSort(Rank lo, Rank hi);					//快速排序
	void	heapSort(Rank lo, Rank hi);						//堆排序

public:														//外部接口部分
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) :	//容量为c，规模为s，初始值为v
		_capacity(c), _size(s){
		_elem = new T[_capacity];
		for (auto &e : _elem)	e = v;
	}
	Vector(const T *A, Rank n){								//数组整体复制
		copyFrom(A, 0, n);		
	}
	Vector(const T *A, Rank lo, Rank hi){					//数组区间复制
		copyFrom(A, lo, hi);
	}
	Vector(const Vector<T> *V){								//向量整体复制
		copyFrom(V._elem, 0, V._size);
	}
	Vector(const Vector<T> *V, Rank lo, Rank hi){			//向量区间复制
		copyFrom(V.elem, lo, hi);
	}
	//析构函数
	~Vector(){ delete _elem[]; }							//释放内存空间
	//只读访问接口
	Rank	size() const;									//规模
	bool	empty() const;									//判断是否为空
	int		disordered() const;								//判断是否有序（非降序）
	Rank	find(const T &e) const;							//无序向量整体查找
	Rank	find(const T &e, Rank lo, Rank hi) const;		//无序向量区间查找
	Rank	search(const T &e) const;						//有序向量整体查找
	Rank	search(const T &e, Rank lo, Rank hi) const;		//有序向量区间查找
	//可写访问接口
	T&		operator [](Rank r) const;						//重载下标操作符，使用类似数组的形式读写数据
	Vector<T> &operator = (const Vector<T> &);				//重载等号运算符，用于拷贝
	T		remove(Rank r);									//删除秩为r的元素，返回删除的值
	int     remove(Rank lo, Rank hi);						//删除[lo, hi)区间的元素，返回删除个数
	Rank	insert(const T &e);								//以末元素插入
	Rank	insert(Rank r, const T &e);						//特别位置插入
	void	sort();											//整体排序
	void	sort(Rank lo, Rank hi);							//区间排序
	void	unsort();										//整体置乱
	void    unsort(Rank lo, Rank hi);						//区间置乱
	int		deduplicate();									//无序去重
	int     uniquify();										//有序去重
	//遍历
	void	traverse(void(*) (T &));						//遍历，使用函数指针（只读，或局部性修改）
	template <typename VST> void traverse(VST&);			//遍历，使用函数对象（可全局修改）
};//Vector

#endif

