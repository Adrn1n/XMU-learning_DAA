/*
传送费用

描述

​在《王者荣耀》的世界中，您作为战队的领队，需要派遣 2N 名英雄前往两座城市（A 城和 B 城）参加比赛。​每位英雄前往 A 城的传送费用为costs[i][0]，前往 B 城的传送费用为costs[i][1]。​您的任务是安排每座城市恰好接收 N 名英雄，并使总的传送费用最小化。

输入

    第一行包含一个整数 N，表示每座城市需要派遣的英雄数量（1 <= N <= 100）。​

    接下来的 2N 行，每行包含两个整数，分别表示一位英雄前往 A 城和 B 城的传送费用。

输出

一个整数，表示最小的总传送费用。

输入样例 1

2
10 20
30 200
400 50
30 20

输出样例 1

110

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5272_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define k 2
#define N_MAX 100

using namespace std;

typedef short idxT;
typedef long long valT;
typedef vector<valT> valVec;

inline valT getMin_assign2Cost(vector<valVec> &Costs)
{
    valT res=0;
    if(!Costs.empty())
    {
        sort(Costs.begin(),Costs.end(),[](const valVec &vec1,const valVec &vec2)
        {
            return abs(vec1[1]-vec1[0])>abs(vec2[1]-vec2[0]);
        });
        auto it=Costs.begin();
        idxT cnt1=0,cnt2=0,len=(idxT)(Costs.size()>>1);
        for(; (it<Costs.end())&&(cnt1<len)&&(cnt2<len); ++it)
            if((*it)[0]<(*it)[1])
                res+=(*it)[0],++cnt1;
            else
                res+=(*it)[1],++cnt2;
        while(it<Costs.end())
            if(cnt1<len)
                res+=(*it++)[0];
            else
                res+=(*it++)[1];
    }
    return res;
}

int main()
{
    idxT N=0;
    cin>>N;
    if((N>0)&&(N<=N_MAX))
    {
        vector<valVec> costs(k*N,valVec(k));
        for(auto &vec:costs)
            for(auto &val:vec)
                cin>>val;
        cout<<getMin_assign2Cost(costs)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
