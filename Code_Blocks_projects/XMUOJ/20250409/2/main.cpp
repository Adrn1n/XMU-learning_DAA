/*
能量需求

描述

在《三角洲行动》中，你作为特种部队指挥官，需要为每位士兵分配一块能量补给（饼干），以便他们能在任务中保持战斗力。

    每个士兵有一个最低能量需求值（即胃口g[i]），只有能量值大于或等于需求的补给品，才能让他被激活。

    每块补给品（饼干）有一个能量值s[j]。

    每块补给品最多只能给一名士兵。

    你需要尽可能多地激活士兵。

输入

第一行为士兵数量N和饼干数量M。第二行为士兵的胃口值g，第三行为饼干大小s。

输出

吃到士兵的孩子的数量

输入样例 1

3 2
1 2 3
1 1

输出样例 1

1

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5270_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef long long valT;

inline idxT getMax_feed(vector<valT> &g,vector<valT> &s)
{
    idxT res=0;
    sort(g.begin(),g.end(),greater<valT>()),sort(s.begin(),s.end(),greater<valT>());
    for(auto it1=s.begin(),it2=g.begin(); it1<s.end(); ++it1)
    {
        while((it2<g.end())&&(*it1<*it2))
            ++it2;
        if(it2<g.end())
            ++res,++it2;
        else
            break;
    }
    return res;
}

int main()
{
    idxT N=0,M=0;
    cin>>N>>M;
    if((N>=0)&&(M>=0))
    {
        vector<valT> g(N),s(M);
        for(auto &val:g)
            cin>>val;
        for(auto &val:s)
            cin>>val;
        cout<<getMax_feed(g,s)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
