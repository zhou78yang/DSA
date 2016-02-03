#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <cstdlib>
#include "listnode.h"


typedef int             Rank;                               // 列表的秩

template <typename T>
class List
{
protected:
    int _size;                                              // 列表长度
    Posi<T> header, trailer;                                // 头结点和尾结点

protected:
    void init();                                            // 列表初始化
    int  clear();                                           // 清除所有结点
    void copyNodes(Posi<T> p, int n);                       // 复制某串结点
    void merge(Posi<T> &p, int n, List<T> &L,           \
                Posi<T> q, int m);                          // 归并
    void mergeSort(Posi<T> &p, int n);                      // 归并排序
    int  partition(Posi<T> &p, int n, Posi<T> &q);          // 快排分段
    void quickSort(Posi<T> &p, int n);                      // 快速排序
    void selectionSort(Posi<T> &p, int n);                  // 选择排序
    void insertionSort(Posi<T> &p, int n);                  // 插入排序

public:
    // 构造函数
    List(){ init(); }                                       // 默认构造函数
    List(const List<T> &L){ copyNodes(L.first(), L._size); }// 列表整体复制
    List(const List<T> &L, Rank r, int n){
        copyNodes(L.getNode(r), n); }                       // 列表区间复制
    List(Posi<T> p, int n){ copyNodes(p, n); }              // 结点形式构造
    // 析构函数
    ~List(){ clear(); delete header; delete trailer; }      // 清除列表

    // 只读访问接口
    Rank size() const{ return _size; }                      // 规模
    bool empty() const{ return _size <= 0; }                // 判空
    Posi<T> first() const{ return header->succ; }           // 首结点位置
    Posi<T> last() const{ return trailer->pred; }           // 末结点位置
    bool valid(Posi<T> p) const{
        return p && (trailer != p) && (header != p); }      // 判断ｐ是否合法
    int disordered() const;                                 // 判断是否有序
    Posi<T> find(const T &e) const;                         // 无序列表查找
    Posi<T> find(const T &e, Posi<T> p, int n) const;       // 无序顺次查找
    Posi<T> find(const T &e, int n, Posi<T> p) const;       // 无序逆向查找
    Posi<T> search(const T &e) const;                       // 有序列表查找
    Posi<T> search(const T &e, Posi<T> p, int n) const;     // 有序顺次查找
    Posi<T> search(const T &e, int n, Posi<T> p) const;     // 有序逆向查找
    Posi<T> selectMax(Posi<T> p, int n);                    // 区间最大值
    Posi<T> selectMax(){ return selectMax(first(), _size); }// 列表最大值

    // 可写访问接口
    T &operator [] (Rank r);                                // 重载下标运算符
    Posi<T> &getNode(Rank r);                               // 获取列表结点
    Posi<T> insertAsFirst(const T &e);                      // 首结点插入
    Posi<T> insertAsLast(const T &e);                       // 尾结点插入
    Posi<T> insert(Posi<T> p, const T &e);                  // 将ｅ插入到ｐ后
    Posi<T> insert(const T &e, Posi<T> p);                  // 将ｅ插入到ｐ前
    T remove(Posi<T> p);                                    // 删除结点ｐ
    void merge(List<T> &L){
        merge(header->succ, _size, L, L.first(), L._size); }// 全列表归并
    void sort(Posi<T> p, int n);                            // 列表区间排序
    void sort(){ sort(first(), _size); }                    // 列表整体排序
    int  deduplicate();                                     // 无序去重
    int  uniquify();                                        // 有序去重
    void reverse();                                         // 前后倒置
    void traverse(void(*)(T &));                            // 函数指针遍历
    template <typename VST> void traverse(VST &);           // 函数引用遍历

};// List


/////////////////////////////////////////////////////////////////////////
// Protected部分内容：
//      仅供列表内部使用
//


// init:
//      初始化列表
template <typename T>
void List<T>::init()
{
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->pred = NULL; header->succ = trailer;
    trailer->pred = header; trailer->succ = NULL;
    _size = 0;
}


// clear:
//      清空列表中的所有元素，并返回元素个数
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while(0 < _size) remove(header->succ);
    return oldSize;
}


// copyNodes:
//      复制结点串
template <typename T>
void List<T>::copyNodes(Posi<T> p, int n)
{
    init(); // 初始化列表
    while(0 < n--)
    {
        insertAsLast(p->data);  // 顺次插入
        p = p->succ;
    }
}


// partition:
//      实现列表分段，参数ｐ表示列表起点，ｎ表示列表长度
//      最终ｐ指向前半段起点，ｑ指向后半段起点
template <typename T>
int List<T>::partition(Posi<T> &p, int n, Posi<T> &q)
{
    int m = 0;  // 记录比ｐ小的结点数
    Posi<T> head = p->pred; // 记录头结点
    q = p->succ;
    for(int i = 1; i < n; i++)
    {
        // 进行n-1次比对，将比ｐ小的结点依次插入ｐ前
        q = q->succ;
        if(p->data > q->pred->data)
        {
            insert(remove(q->pred), p);
            m++;
        }
    }
    q = p->succ;    // ｑ为后半段起点
    p = head->succ; // ｐ恢复为前半段起点即列表起点
    return m;       // 返回前半段列表长度
}


// quickSort:
//      快速排序，对从ｐ（包括ｐ）开始的ｎ个结点进行排序
//      要求ｐ最终指向有序列表的起点
template <typename T>
void List<T>::quickSort(Posi<T> &p, int n)
{
    if(n < 2) return;
    Posi<T> q;  // 由于List访问的不便性，故用ｑ来获取后半段起点
    int m = partition(p, n, q);  // m存储前半段长度
    quickSort(p, m);
    quickSort(q, n - m - 1);
}


// merge:
//      归并函数，实现两段列表的归并
//      p为当期List的某个结点，ｎ为ｐ开头列表段长度
//      ｑ为列表L的某个结点，ｍ为ｑ开头列表段长度
template <typename T>
void List<T>::merge(Posi<T> &p, int n, List<T> &L, Posi<T> q, int m)
{
    Posi<T> head = p->pred; // 记录归并区间的头结点
    Posi<T> r = p;          // p的值拷贝
    while(0 < m)
    {
        if(0 < n && (r->data <= q->data))
        {
            r = r->succ; n--;
            if(r == q) break;   // 针对ｑ元素结尾的情况处理
        }
        else
        {
            q = q->succ; m--;
            insert(L.remove(q->pred), r);   // 插入到r前
        }
    }
    p = head->succ; // 将ｐ移回归并区间的首结点
}


// mergeSort:
//      归并排序
template <typename T>
void List<T>::mergeSort(Posi<T> &p, int n)
{
    if(n < 2) return;
    int m = n / 2;
    Posi<T> q = p;
    for(int i = 0; i < m; i++) q = q->succ; // 均分列表
    mergeSort( p, m); mergeSort( q, n - m); // 划分两段排序
    merge( p, m, *this, q, n - m);          // 归并
}


// selectionSort:
//      选择排序
template <typename T>
void List<T>::selectionSort(Posi<T> &p, int n)
{
    Posi<T> head = p->pred; Posi<T> tail = p;   // 头、尾结点
    for(int i = 0; i < n; i++) tail = tail->succ;   // 待排区间(head, tail)
    while(1 < n)
    {
        Posi<T> q = selectMax(head->succ, n);   // 待排区间中的最大值
        insert(remove(q), tail);    // 将最大值插入到为排序部分末尾
        tail = tail->pred; n--;     // 收缩未排序部分
    }
}


// insertionSort:
//      插入排序
template <typename T>
void List<T>::insertionSort(Posi<T> &p, int n)
{
    Posi<T> head = p->pred, tail = p;   // 头、尾结点
    for(int i = 0; i < n; i++) tail = tail->succ;
    p = p->succ;
    while(p != tail)
    {
        Posi<T> r = p->pred;
        while(r != head && r->data > p->data) r = r->pred;  // 找到插入位置
        p = p->succ; insert(r, remove(p->pred)); // 插入到ｒ后
    }
}




//////////////////////////////////////////////////////////////////////////////
// 只读访问接口
//


// disoredered: 查看是否有序，返回逆序数
template <typename T>
int List<T>::disordered() const
{
    int c = 0;
    Posi<T> p = first();
    while(trailer != (p = p->succ))
    {
        if(p->pred->data > p->data) c++;
    }
    return c;
}


// find:
//      无序列表查找函数，ｅ为查找的值，ｐ为查找的端点，ｎ为查找长度
//      ｎ在ｐ前则表示从ｐ向前查找ｎ个结点，同理，ｎ在ｐ后则表示向后查找
//      注意：查找的元素不包含ｐ
template <typename T>
Posi<T> List<T>::find(const T &e) const
{
    return find(e, _size, trailer);
}

template <typename T>
Posi<T> List<T>::find(const T &e, Posi<T> p, int n) const
{
    while(0 < n--)
    {
        if(e == (p = p->succ)->data) return p;
    }
    return NULL;    // 查找失败返回NULL
}

template <typename T>
Posi<T> List<T>::find(const T &e, int n, Posi<T> p) const
{
    while(0 < n--)
    {
        if(e == (p = p->pred)->data) return p;
    }
    return NULL;
}


// search:
//      有序列表查找函数，ｅ为查找的值，ｐ为查找的端点，ｎ为查找长度
//      ｎ在ｐ前则表示从ｐ向前查找ｎ个结点，同理，ｎ在ｐ后则表示向后查找
//      注意：查找的元素不包含ｐ
template <typename T>
Posi<T> List<T>::search(const T &e) const
{
    return search(e, _size, trailer);
}

template <typename T>
Posi<T> List<T>::search(const T &e, Posi<T> p, int n) const
{
    while(0 < n-- && (p = p->succ)->data < e) ;
    return p->data == e ? p : NULL;
}

template <typename T>
Posi<T> List<T>::search(const T &e, int n, Posi<T> p) const
{
    while(0 < n-- && (p = p->pred)->data > e) ;
    return p->data == e ? p : NULL;
}


// selectMax:
//      挑选从ｐ开始的ｎ个结点中的最大值
template <typename T>
Posi<T> List<T>::selectMax(Posi<T> p, int n)
{
    Posi<T> max = p;
    while(1 < n--)
    {
        if((p = p->succ)->data > max->data) max = p;
    }
    return max;
}




////////////////////////////////////////////////////////////////////////
// 可写访问接口
//


// 重载[]运算符，返回的是第ｒ个结点的值
// 注意：效率低下，尽量少用
template <typename T>
T &List<T>::operator [] (Rank r)
{
    Posi<T> p = first();
    while(0 < r--) p = p->succ;
    return p->data;
}

template <typename T>
Posi<T> &List<T>::getNode(Rank r)
{
    Posi<T> p = first();
    while(0 < r--) p = p->succ;
    return p;
}


// insertAsFirst: 首结点插入
template <typename T>
Posi<T> List<T>::insertAsFirst(const T &e)
{
    _size++;
    return header->insertAsSucc(e);
}


// insertAsLast: 末结点插入
template <typename T>
Posi<T> List<T>::insertAsLast(const T &e)
{
    _size++;
    return trailer->insertAsPred(e);
}


// insert: 插入函数
//      值ｅ在ｐ前时表示插入在ｐ前面，ｅ在ｐ后时表示插入在ｐ后
template <typename T>
Posi<T> List<T>::insert(Posi<T> p, const T &e)
{
    // insert after
    _size++;
    return p->insertAsSucc(e);
}


template <typename T>
Posi<T> List<T>::insert(const T &e, Posi<T> p)
{
    // insert before
    _size++;
    return p->insertAsPred(e);
}


// remove: 删除结点
//      删除结点ｐ，并返回其内容
template <typename T>
T List<T>::remove(Posi<T> p)
{
    T e = p->data;      // 数据备份
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}


// sort:
//      对列表进行排序，随机选择排序算法
template <typename T>
void List<T>::sort(Posi<T> p, int n)
{
    int kinds = 4;
    switch(rand() % kinds)
    {
    case 1: insertionSort( p, n); break;
    case 2: selectionSort( p, n); break;
    case 3: quickSort( p, n); break;
    default: mergeSort( p, n); break;
    }
}


// deduplicate:
//      无序列表去重操作
template <typename T>
int List<T>::deduplicate()
{
    if(_size < 2) return 0;
    int oldSize = _size;
    Posi<T> p = header; Rank r = 0;
    while(trailer != (p = p->succ))
    {
        Posi<T> q = find(p->data, r, p);    // 查找ｐ前的ｒ个元素
        q ? remove(q) : r++;    // 若ｑ存在则删除ｑ
    }
    return oldSize - _size; // 返回删掉的结点数
}


// reverse: 列表反转函数
/*
 *数值交换版本
 *
template <typename T>
void List<T>::reverse()
{
    Posi<T> p = header; Posi<T> q = trailer;
    for(int i = 0; i < _size; i += 2)
    {
        std::swap((p = p->succ)->data, (q = q->pred)->data);
    }
}
*/
template <typename T>
void List<T>::reverse()
{
    if( _size < 2) return;
    for(auto p = header; p; p = p->pred)
    {
        std::swap(p->pred, p->succ);// 交换每个结点的前驱和后继
    }
    std::swap(header, trailer);  // 头尾结点交换
}


// uniquify:
//      有序列表去重操作
template <typename T>
int List<T>::uniquify()
{
    if(_size < 2) return 0;
    int oldSize = _size;
    Posi<T> p = header->succ; Posi<T> q;
    while(trailer != (q = p->succ))
    {
        // 反复考查相邻结点对ｐ和ｑ
        if(p->data == q->data) remove(q);
        else p = q;
    }
    return oldSize - _size;
}


// traverse: 遍历函数
template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for(auto p = first(); p != trailer; p = p->succ) visit(p->data);
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit)
{
    for(auto p = first(); p != trailer; p = p->succ) visit(p->data);
}





#endif
