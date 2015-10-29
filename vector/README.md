#[向量（Vector）](./vector.hpp)

Vector是C++标准模板库中的部分内容，中文偶尔译作“容器”，但并不准确。它是一个多功能的，能够操作多种数据结构和算法的模板类和函数库。Vector之所以被认为是一个容器，是因为它能够像容器一样存放各种类型的对象，简单地说，vector是一个能够存放任意类型的动态数组，能够增加和压缩数据。

###接口内容

```cpp
typedef     int                 Rank;           // 元素的秩
#define     DEFAULT_CAPACITY    3               // 初始向量容量

template <typename T> class Vector
{
public:
    // 构造函数：
    //      除了默认构造函数，还包含数组整体复制构造，数组区间复制构造，向量整体复制构造，向量区间复制构造等方式。
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) :
        _capacity(c), _size(s){
            _elem = new T[_capacity];
            for(int i = 0; i < _size; i++) _elem[i] = v;
        }
    Vector(const T *A, Rank n){
        copyFrom(A, 0, n);
    }
    Vector(const T *A, Rank lo, Rank hi){
        copyFrom(A, lo, hi);
    }
    Vector(const Vector<T> &V){
        copyFrom(V._elem, 0, V._size);
    }
    Vector(const Vector<T> &V, Rank lo, Rank hi){
        copyFrom(V._elem, lo, hi);
    }
    // 析构函数
    ~Vector(){ delete[] _elem; }

    // 只读访问接口
    Rank size() const;                          // 规模            
    bool empty() const;                         // 判断是否为空
    int  disordered() const;                    // 判断是否有序
    Rank find(const T &e) const;                // 无序向量整体查找
    Rank find(const T &e, Rank lo, Rank hi) const;// 无序向量区间查找
    Rank search(const T &e) const;              // 有序向量整体查找
    Rank search(const T &e, Rank lo, Rank hi) const;// 有序向量区间查找

    // 可写访问接口
    T&      operator [](Rank r) const;          // 重载'[]'运算符，用于访问元素
    Vector<T> &operator = (const Vector<T> &);  // 重载‘=’运算符，用于拷贝
    T       remove(Rank r);                     // 删除[r]元素
    int     remove(Rank lo, Rank hi);           // 删除[lo, hi)区间元素，返回删除个数
    Rank    insert(const T &e);                 // 末位插入元素
    Rank    insert(Rank r, const T &e);         // 指定位置插入
    void    sort();                             // 整体排序
    void    sort(Rank lo, Rank hi);             // 区间排序
    void    unsort();                           // 整体置乱
    void    unsort(Rank lo, Rank hi);           // 区间置乱
    int     deduplicate();                      // 无序去重
    int     uniquify();                         // 有序去重
    void    traverse(void(*) (T &));            // 遍历，使用函数指针（只读，或部分修改）
    template <typename VST> void traverse(VST&);// 遍历，使用函数对象（可全局修改）

protected:                                      // 内置函数部分
    void copyFrom(const T *A, Rank lo, Rank hi);// 复制数据区间A[lo, hi)
    void expand();                              // 空间不足时扩容
    void shrink();                              // 装载因子过小时缩容
    void bubbleSort(Rank lo, Rank hi);          // 冒泡排序
    Rank max(Rank lo, Rank hi);                 // 获取[lo, hi)内最大值
    void selectionSort(Rank lo, Rank hi);       // 选择排序
    void mergeSort(Rank lo, Rank hi);           // 归并排序
    void quickSort(Rank lo, Rank hi);           // 快速排序
    void heapSort(Rank lo, Rank hi);            // 堆排序

protected:                                      // 成员变量部分
    Rank _size;                                 // 元素个数
    int  _capacity;                             // 向量容量
    T*   _elem;                                 // 元素数组

};
```
