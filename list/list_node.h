// list_node.h

#ifndef LIST_NODE_H_
#define LIST_NODE_H_

template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*;

// 列表结点类
template <typename T>
struct ListNode
{
    // 成员
    T data;
    ListNodePosi<T> pre;
    ListNodePosi<T> next;

    // 构造函数
    ListNode() {} // 针对header和trailer的构造
    ListNode(T e, ListNodePosi<T> p = nullptr, ListNodePosi<T> n = nullptr)
        :data(e), pre(p), next(n) {} // 默认构造器

    // 操作接口
    ListNodePosi<T> insertAsPre(const T &e);
    ListNodePosi<T> insertAsNext(const T &e);

};

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsPre(const T &e)
{
    ListNodePosi<T> new_node = new ListNode(e, pre, this); // 创建新节点
    pre->next = new_node;
    pre = new_node;
    return new_node; // 返回新结点位置
}

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsNext(const T &e)
{
    ListNodePosi<T> new_node = new ListNode(e, this, next); // 创建新结点
    next->pre = new_node;
    next = new_node;
    return new_node; // 返回新结点的位置
}



#endif 
