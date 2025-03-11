/*
魔法符文
描述

在巫师仓库中，数百个附魔物品正发出危险的红光。每个物品都刻着代表魔法符文的数字id，当某个符文出现的次数超过物品总数的一半时，就会引发元素失控。

见习法师赫敏挥动魔杖，空中立刻浮现出不断流动的符文序列（如[3,2,3]），她必须在符文完全暴走前，找到那个即将主导整个魔法矩阵的危险符文。你能帮她写出这道救命咒语吗？


输入

第一行为符文数组长度

第二行为符文数组，长度为n（1 <= n < 10^7）。

符文数组中一定存在危险符文。


输出

输出危险符文。


输入样例 1

5
3 2 2 3 2
输出样例 1

2
*/

#include <iostream>
#include <vector>
#include <queue>

#define N_MAX 10000000

using namespace std;

typedef int idxT;
typedef long long valT;

typedef struct freqNode_
{
    valT val;
    idxT cnt;
    vector<valT>::iterator Start,End;
} freqNode;

valT getMoreHalf_freq(vector<valT> A)
{
    freqNode node= {0};
    if(!A.empty())
    {
        queue<idxT> divdQue;
        divdQue.push((idxT)(A.size()));
        for(idxT tmp=0; (tmp=divdQue.front())>1; divdQue.pop(),divdQue.push(tmp>>1),divdQue.push(tmp-(tmp>>1)));
        queue<freqNode> freqQue;
        for(auto it=A.begin(); !divdQue.empty(); divdQue.pop())
        {
            idxT tmp=divdQue.front();
            if(tmp>1)
                if(*it==*(it+1))
                    freqQue.push({*it,tmp,it,it+=2});
                else
                    freqQue.push({0,0,it,it+=2});
            else
                freqQue.push({*it,1,it,++it});
        }
        for(freqNode tmp= {0}; node=freqQue.front(),freqQue.pop(),!freqQue.empty(); freqQue.pop())
        {
            tmp=freqQue.front();
            if((node.cnt>0)&&(tmp.cnt>0))
            {
                if(node.val==tmp.val)
                {
                    freqQue.push({node.val,node.cnt+tmp.cnt,node.Start,tmp.End});
                    continue;
                }
                else
                {
                    if(node.cnt>tmp.cnt)
                        tmp.cnt=0;
                    else if(node.cnt<tmp.cnt)
                        node.cnt=0;
                    else
                        node.cnt=tmp.cnt=0;
                }
            }
            if(node.cnt>0)
            {
                for(auto it=tmp.Start; it<tmp.End; ++it)
                    if(*it==node.val)
                        ++node.cnt;
                if(node.cnt>((tmp.End-node.Start)>>1))
                {
                    freqQue.push({node.val,node.cnt,node.Start,tmp.End});
                    continue;
                }
            }
            else if(tmp.cnt>0)
            {
                for(auto it=node.Start; it<node.End; ++it)
                    if(*it==tmp.val)
                        ++tmp.cnt;
                if(tmp.cnt>((tmp.End-node.Start)>>1))
                {
                    freqQue.push({tmp.val,tmp.cnt,node.Start,tmp.End});
                    continue;
                }
            }
            freqQue.push({0,0,node.Start,tmp.End});
        }
    }
    return node.val;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n<=N_MAX)
    {
        vector<valT> A(n);
        for(auto &a:A)
            cin>>a;
        cout<<getMoreHalf_freq(A)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
