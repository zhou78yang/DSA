#ifndef STACK_H_
#define STACK_H_

#include "../vector/vector.hpp"

template <typename T>
class Stack: public Vector<T>
{
    // 通过继承Vector来实现栈
    // Vector的前端表示栈底，后端表示栈顶
    // size,empty等其他开放接口可直接沿用
    //
public:
    void push(const T &e){ 
        Vector<T>::insert(e); } // 压栈：直接将元素存入末端
    T pop(){ 
        return Vector<T>::remove(Vector<T>::size() - 1); }  // 弹栈：直接删除末端元素
    T &top(){ 
        return (*this)[Vector<T>::size() - 1]; }    // 取顶：直接返回末端元素

};// stack

#endif
