// list.hpp

#ifndef LIST_H_
#define LIST_H_

#include "list_node.h"
typedef  int    Rank;               // 结点的秩


// 列表模板类
template <typename T>
class List
{
protected:
    int _size;                      // 规模
    ListNodePosi header;            // 头哨兵
    ListNodePosi trailer;           // 尾哨兵

protected:
    void init();                    // 列表初始化
    int  clear();                   // 清除所有结点
    void copyNodes(ListNodePosi, int);// 复制列表中自位置P起的n项
    void merge(ListNodePosi&, int, List<T>&, ListNodePosi, int); // 归并
    void mergeSort(ListNodePosi&, int); // 对从p开始的n个结点进行归并排序
    void selectionSort(ListNodePosi, int); // 对从p开始的n个结点进行选择排序
    void insertionSort(ListNodePosi, int); // 对从p开始的n个结点进行插入排序

public:
    // 构造函数
    List() { init(); }                  // 默认构造函数
    List(const List<T> &L);             // 整体复制列表L
    List(const List<T> &L, Rank r, int n);// 复制列表L中自r开始的n个结点
    List(ListNodePosi p, int n);        // 复制列表中自位置p起的n项
    // 析构函数
    ~List();

    // 只读访问接口
    Rank size() const { return _size; } // 规模
    bool empty() const { return _size <= 0; } // 判断是否为空
    T &operator [](Rank r) const;// 重载，支持寻秩访问
    ListNodePosi first() const { return header->next; }
    ListNodePosi last() const { return trailer->pre; }
    bool valid(ListNodePosi p) const    // 判断p结点是否可用
    { return p && (p != header) && (p != trailer); }
    int disordered() const; // 判断是否有序
    ListNodePosi find(const T &e) const;// 无序列表整体查找
    ListNodePosi find(const T &e, ListNodePosi p, int n) const;// 无序列表区间查找
    ListNodePosi search(const T &e) const;// 有序列表整体查找
    ListNodePosi search(const T &e, ListNodePosi p, int n) const;// 有序列表区间查找
    ListNodePosi max() const;// 获取整体最大值
    ListNodePosi max(ListNodePosi p, int n) const;// 在p后的n个结点中选取最大值

    // 可写访问接口
    ListNodePosi insertAsFirst(const T &e);     // 将e作为首结点插入
    ListNodePosi insertAsLast(const T &e);      // 将e作为尾结点插入
    ListNodePosi insertA(ListNodePosi p, const T &e);// 将e作为p的后继插入
    ListNodePosi insertB(ListNodePosi p, const T &e);// 将e作为p的前驱插入
    T remove(ListNodePosi p);                   // 删除结点p
    void merge(List<T> &L);                     // 插入一个列表
    void sort();                                // 列表排序
    void sort(ListNodePosi p, int n);           // 列表区间排序
    int  deduplicate();                         // 无序去重
    int  uniquify();                            // 有序去重
    void reverse();                             // 反转列表

    // 遍历
    void traverse(void (*)(T&));                // 函数指针传入遍历
    template <typename VST> void traverse(VST&);// 函数引用传入遍历

};


template <typename T>
void List<T>::init()
{
    header = new ListNode();
    trailer = new ListNode();
    header->pre = NULL; header->next = trailer;
    trailer->pre = header; trailer->next = NULL;
    _size = 0;
}

template <typename T>
int List<T>::clear()
{
    while(header->next != trailer)
    {
        ListNodePosi tmp = header->next->next;
        delete header->next;
        header->next = tmp;
    }
    trailer->pre = header;
}

template <typename T>
void copyNodes(ListNodePosi p, int n)
{
    init();// 初始化列表
    while(n--)
    {
        insertAsLast(p->data);
        p = p->next;
    }
}


#endif
