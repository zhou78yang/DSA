#include <iostream>
#include <deque>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

#define N   25

bool vis[N][N][N];  // 状态遍历情况集合
int cap[3], vol[3]; // 杯子的容积，杯中水的体积
string op[3][3];
string name[3] = {"A", "B", "C" };

struct State
{
    int b[3];
    int step = 0;
};


bool bfs(State start)
{
    queue<State> q;
    q.push(start);
    State cur, tmp; // 当前杯子状态和临时状态
    vis[start.b[0]][start.b[1]][start.b[2]] = true;

    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        for(int i = 0; i < 3; i++) vol[i] = cur.b[i];

        for(int i = 0; i < 3; i++)
        {
            if(0 == vol[i]) continue; // 当杯子为空时跳过
            for(int j = 0; j < 3; j++)
            {
                tmp = cur;
                if(i == j)
                {
                    // 倒空操作
                    tmp.b[i] = 0;
                }
                else
                {
                    if(vol[i] >= (cap[j] - vol[j]))
                    {
                        // ｉ可以倒满ｊ
                        tmp.b[j] = cap[j];
                        tmp.b[i] -= (cap[j] - vol[j]);
                    }
                    else
                    {
                        // ｉ不可以倒满ｊ
                        tmp.b[j] += vol[i];
                        tmp.b[i] = 0;
                    }
                }
                tmp.step++;
                if(!vis[tmp.b[0]][tmp.b[1]][tmp.b[2]])
                {
                    q.push(tmp);
                    vis[tmp.b[0]][tmp.b[1]][tmp.b[2]] = true;

                    // test output
                    cout << "step[" << tmp.step << "]: ";
                    cout << op[i][j] << "\t\t< ";
                    for(int i = 0; i < 3; i++) cout << vol[i] << ", ";
                    cout << "> to < ";
                    for(int i = 0; i < 3; i++) cout << tmp.b[i] << ", ";
                    cout << ">" << endl;
                }
                for(int i = 0; i < 3; i++)
                {
                    if(2 == tmp.b[i])
                    {
                        cout << endl << ">>>>>>Congradulation<<<<<<" << endl;
                        return true;
                    }
                }
            }// inner for
        }// outer for
    }// while
    return false;
}
                    

int main()
{    
    State start;
    start.step = 0;
    for(int i = 0; i < 3; i++)
    {
        cin >> cap[i] >> vol[i];
        start.b[i] = vol[i];
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
            {
                op[i][j] = name[i] + "倒掉 ";
            }
            else
            {
                op[i][j] = name[i] + "倒向" + name[j];
            }
        }
    }

    if(!bfs(start))
    {
        cout << "solution no found!" << endl;
    }

    return 0;
}

