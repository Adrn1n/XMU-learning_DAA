/*
最受欢迎的颜色

描述

在古老的神话森林中，居住着各种各样的精灵，每种精灵都有其独特的颜色。这些精灵们每年都会举行一次盛大的集会，选出这一年中最受欢迎的颜色。为了公平公正，他们制定了一条规则：只有在所有精灵的颜色中，出现次数超过半数的颜色才能被选为最受欢迎的颜色。

输入

给定一个大小为 n 的数组 colors，数组中的每个元素代表一个精灵的颜色，你需要找出并返回那个出现次数超过 ⌊n/2⌋ 的颜色。

输出

返回在数组 colors 中出现次数超过半数的颜色。你可以假设数组是非空的，并且给定的数组总是存在这样的颜色。

输入样例 1

3 2 3

输出样例 1

3

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_4921_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long idxT;
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
    valT val=0;
    vector<valT> A;
    while(cin>>val)
        A.push_back(val);
    if(A.empty())
        cout<<"ERROR"<<endl;
    else
        cout<<getMoreHalf_freq(A)<<endl;
    return 0;
}
