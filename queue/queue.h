#ifndef QUEUE_H_
#define QUEUE_H_

#include "../list/list.hpp"

template <typename T>
class Queue: public List<T>
{
    // 队列模板类，继承自List
    // size, empty等开放接口可以直接沿用
    // 
public:
    void enqueue(const T &e){
        List<T>::insertAsLast(e); }                 // 入队：插入末尾
    T dequeue(){ 
        return List<T>::remove(List<T>::first()); } // 出队：首部删除
    T &front(){ 
        return List<T>::first()->data; }            // 取首
};// Queue


#endif 
