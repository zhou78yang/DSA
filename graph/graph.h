#ifndef GRAPH_H_
#define GRAPH_H_

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; // 顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;    // 边在遍历树中所属的类型

template <typename Tv, typename Te> // 顶点类型， 边类型
class Graph
{
private:
    void reset() {
        for(int i = 0; i < n; i++)
        {
            status(i) = UNDISCOVERED;   // 状态标记
            dTime(i) = fTime(i) = -1;   // 时间标记
            parent(i) = -1;             // 在遍历树中的父节点
            priority(i) = INT_MAX;      // 优先级数
            for(int j = 0; j < n; j++)
            {
                if(exists(i, j))
                {
                    type(i, j) = UNDETERMINED;  // 类型
                }
            }// 所有边的
        }// 所有顶点的
    }// reset
    
    void BFS( int, int&);               // 广度优先搜索算法
    void DFS( int, int&);               // 深度优先搜索算法
    void BCC( int, int&, Stack<int>& ); // 基于DFS的双联通分量分解算法
    bool TSort( int, int&, Stack<Tv>* );// 基于DFS的拓扑排序算法
    template <typename PU> void PFS(int PU);    // 优先搜索框架


#endif
