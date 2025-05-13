/*
N皇后

描述

在鸣潮的世界中，天赋超群的觉醒者「吟霄」发现了来自古代文明的智力试炼棋盘。这个棋盘是一个n×n的战术模拟器，需要将每个皇后型元灵分别安放在棋盘上，使得它们无法互相感知或攻击。吟霄需要你的帮助来计算所有可能的布阵方式，以通过试炼获得远古知识。

输入

一个整数n，表示棋盘的边长，同时也是皇后的数量。

输出

输出所有合法的皇后放置方案，每种方案表示为一组字符串，其中'Q'表示皇后，'.'表示空位。每种方案输出一行，每一行将方案的每一行拼接后用空格隔开。

QQ截图20250505211856.png (./c76b2ac276.png)

输入样例 1

4

输出样例 1

[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5337_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>

using namespace std;

typedef long long idxT;

typedef vector<idxT> idxVec;

struct stakNode
{
    idxT idx;
    bool isOver;
};

inline bool isDiag(const idxVec &A,const idxT a,const idxT b)
{
    return abs(A[a]-A[b])==abs(a-b);
}

inline bool isVaild_nQueens_i(const idxVec &A,const idxT i)
{
    if(A.size()>(size_t)i)
    {
        for(idxT j=0; j<i; ++j)
            if((A[i]==A[j])||isDiag(A,i,j))
                return false;
        return true;
    }
    else
        return false;
}

inline vector<idxVec> build_nQueens(const idxT n)
{
    vector<idxVec> Res;
    if(n>0)
    {
        idxVec A;
        stack<stakNode> Stak;
        do
        {
            stakNode node= {-1,false};
            if(!Stak.empty())
                node=Stak.top();
            bool flag=true;
            if(node.isOver)
            {
                auto &tmp=Stak.top();
                for(++A[tmp.idx]; A[tmp.idx]<n; ++A[tmp.idx])
                    if(isVaild_nQueens_i(A,tmp.idx))
                    {
                        tmp.isOver=flag=false;
                        break;
                    }
                if(flag)
                {
                    A.pop_back(),Stak.pop();
                    if(!Stak.empty())
                        (Stak.top()).isOver=true;
                }
            }
            else
            {
                if(A.size()==(size_t)n)
                    Res.push_back(A);
                else
                {
                    ++(node.idx);
                    for(idxT i=0; i<n; ++i)
                    {
                        A.push_back(i);
                        if(isVaild_nQueens_i(A,node.idx))
                        {
                            Stak.push(node),flag=false;
                            break;
                        }
                        A.pop_back();
                    }
                }
                if(flag&&(!Stak.empty()))
                    (Stak.top()).isOver=true;
            }
        }
        while(!Stak.empty());
    }
    return Res;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        auto Res=build_nQueens(n);
        cout<<'[';
        for(auto it1=Res.begin(); it1<Res.end(); ++it1)
        {
            cout<<'[';
            for(auto it2=(*it1).begin(); it2<(*it1).end(); ++it2)
            {
                cout<<'"';
                for(idxT i=0; i<n; ++i)
                    if(i==(*it2))
                        cout<<'Q';
                    else
                        cout<<'.';
                cout<<'"';
                if(it2<((*it1).end()-1))
                    cout<<',';
            }
            cout<<']';
            if(it1<(Res.end()-1))
                cout<<','<<endl;
        }
        cout<<']'<<endl;
    }
    return 0;
}
