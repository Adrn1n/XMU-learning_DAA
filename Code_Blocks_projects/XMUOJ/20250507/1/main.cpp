/*
离心机挑战

描述

王者峡谷实验室正在进行一项重要的魔法研究。小明作为一名实验助手，负责操作一台特殊的魔法离心机，该离心机只有两个槽位。实验台上摆放着一个n行m列的魔法样品架，每个位置可能有一个完好的魔法样品（用1表示）或被魔道污染的样品（用-1表示）。

为了高效地完成实验，小明必须遵循以下规则：

    每次只能从魔法样品架上取出相邻的两个完好样品（上下左右相邻）放入离心机
    已被魔道污染的样品不能使用
    由于小明非常懒惰，他不会处理单独剩下的样品（必须成对处理）

小明想知道，在遵循上述规则的情况下，最多能处理多少个魔法样品？

输入

第一行包含两个用一个空格分隔的整数 n 和 m，分别代表魔法样品架的行数和列数（1 ≤ n, m ≤ 100）。接下来的 n 行，每行包含 m 个整数，相邻两个整数之间由一个空格分隔。第i行第j列的元素为aij。若aij为1则表明该位置的样品完好可用，若aij为-1则表示该位置的样品已被魔道污染。

输出

输出共一行，包含一个非负整数，表示可被处理的样品的最大数量。

输入样例 1

3 4
1 1 1 -1
1 1 -1 1
-1 1 1 1

输出样例 1

8

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5333_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>

#define MAX_IDX 100
#define MOV_DIM 2
#define MOV_N 2

using namespace std;

typedef long long idxT;
typedef short valT1;
typedef bool valT2;
typedef short movIdxT;

typedef pair<idxT,idxT> PII;
typedef vector<valT2> valT2Vec;

struct stakNode
{
    PII loc;
    movIdxT idx;
};

enum search_state {stop,init,extend};

const idxT Mov[MOV_DIM][MOV_N]= {{0,1},{1,0}};

inline search_state extendLoc(vector<valT2Vec> &A,stakNode &node)
{
    search_state state=stop;
    auto &loc=node.loc;
    if((loc.first>=0)&&((size_t)(loc.first)<(A.size()))&&(loc.second>=0)&&((size_t)(loc.second)<(A[loc.first].size())))
        for(movIdxT i=node.idx; i<MOV_N; ++i)
        {
            loc.first+=Mov[0][i],loc.second+=Mov[1][i];
            bool flag=false;
            if((loc.first>=0)&&((size_t)(loc.first)<A.size())&&(loc.second>=0)&&((size_t)(loc.second)<(A[loc.first].size()))&&A[loc.first][loc.second])
                flag=true;
            loc.first-=Mov[0][i],loc.second-=Mov[1][i];
            if(flag)
            {
                A[loc.first][loc.second]=A[loc.first+Mov[0][i]][loc.second+Mov[1][i]]=false,node.idx=i,state=init;
                break;
            }
        }
    return state;
}

inline idxT getMax_cntProc(vector<valT2Vec> &A)
{
    idxT res=0;
    search_state state=init;
    stakNode firstNode= {{0,0},0};
    bool flag0=true;
    idxT ext_size=1;
    while(state!=stop)
    {
        stack<stakNode> Stak;
        idxT cnt=0;
        do
        {
            stakNode node= {{0,-1},0};
            auto &nodeLoc=node.loc;
            bool flag1=false;
            if((state==extend)&&(Stak.size()<=(size_t)ext_size)&&(Stak.empty()||(!A[((Stak.top()).loc).first][((Stak.top()).loc).second])))
            {
                node=firstNode;
                if(Stak.size()<(size_t)ext_size)
                {
                    node.idx=0;
                    for(auto i=firstNode.idx+1;; ++i)
                        if(i<MOV_N)
                        {
                            if(A[nodeLoc.first+Mov[0][i]][nodeLoc.second+Mov[1][i]])
                            {
                                auto tmp=node;
                                (tmp.loc).first+=Mov[0][i],(tmp.loc).second+=Mov[1][i],tmp.idx=0;
                                if(extendLoc(A,tmp)!=stop)
                                    Stak.push(tmp),cnt+=2,flag1=true;
                                if(!flag0)
                                    ++ext_size;
                                break;
                            }
                        }
                        else
                        {
                            if(!flag0)
                                --ext_size,flag0=flag1=true;
                            break;
                        }
                    if(flag1)
                        continue;
                    else
                        break;
                }
                else
                    flag1=true;
            }
            if(!flag1)
            {
                if(!Stak.empty())
                    node=Stak.top();
                flag1=true;
            }
            if((Stak.empty())||(!A[(node.loc).first][(node.loc).second]))
            {
                for(++(nodeLoc.second),(node.idx)=0; flag1&&((size_t)(nodeLoc.first)<A.size()); nodeLoc.second=0,++(nodeLoc.first))
                    for(; (size_t)(nodeLoc.second)<(A[nodeLoc.first].size()); ++(nodeLoc.second))
                        if((A[nodeLoc.first][nodeLoc.second])&&(extendLoc(A,node)!=stop))
                        {
                            if(flag0)
                                firstNode=node,flag0=false;
                            Stak.push(node),cnt+=2,flag1=false;
                            break;
                        }
            }
            else
            {
                ++node.idx;
                if(extendLoc(A,node)!=stop)
                    Stak.top()=node,flag1=false;
            }
            if(flag1)
            {
                if(res<cnt)
                    res=cnt;
                if(Stak.empty())
                    state=stop;
                else
                {
                    if(A[((Stak.top()).loc).first][((Stak.top()).loc).second])
                        cnt-=2,Stak.pop();
                    if(!Stak.empty())
                    {
                        auto &tmp=(Stak.top()).loc;
                        A[tmp.first+Mov[0][(Stak.top()).idx]][tmp.second+Mov[1][(Stak.top()).idx]]=A[tmp.first][tmp.second]=true;
                    }
                }
            }
        }
        while(!Stak.empty());
        if((state==init)&&(!flag0))
            state=extend;
        else
            break;
    }
    return res;
}

int main()
{
    idxT n=0,m=0;
    cin>>n>>m;
    if((n>0)&&(n<=MAX_IDX)&&(m>0)&&(m<=MAX_IDX))
    {
        vector<valT2Vec> A(n,valT2Vec(m));
        valT1 val=0;
        for(auto &vec:A)
            for(auto a:vec)
            {
                cin>>val;
                switch(val)
                {
                case 1:
                {
                    a=true;
                    break;
                }
                case -1:
                {
                    a=false;
                    break;
                }
                default:
                    cout<<"ERROR!"<<endl;
                }
            }
        cout<<getMax_cntProc(A)<<endl;
    }
    return 0;
}
