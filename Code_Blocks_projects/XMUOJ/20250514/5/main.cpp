/*
时间校准

描述

罗德岛的一台源石能量终端需要你使用 4 个数字模块校准出一个有效的24 小时制时间。每个模块上有一个数字（0-9），你必须使用所有 4 个数字，组合成合法的时间格式HH:MM。

    有效小时范围为00到23

    有效分钟范围为00到59

你的任务是：从给定的 4 个数字中构造出最大可能的合法时间（离午夜 00:00 最远）。若无法构造出合法时间，返回空字符串""。

输入

4 个数字（空格分隔），例如：1 2 3 4

输出

一个字符串，表示最大时间（格式如23:41）；若无合法时间，返回空字符串。

示例 1：

输入：arr = [1,2,3,4]
输出："23:41"
解释：有效的 24 小时制时间是 "12:34"，"12:43"，"13:24"，"13:42"，"14:23"，"14:32"，"21:34"，"21:43"，"23:14" 和 "23:41" 。这些时间中，"23:41" 是最大时间。

示例 2：

输入：arr = [5,5,5,5]
输出：""
解释：不存在有效的 24 小时制时间，因为 "55:55" 无效。

示例 3：

输入：arr = [0,0,0,0]
输出："00:00"

示例 4：

输入：arr = [0,0,1,0]
输出："10:00"

输入样例 1

 1 2 3 4

输出样例 1

23:41

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5365_test_cases.zip)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>
#include <functional>

#define time24h_N 2
#define MAX_N 4

using namespace std;

typedef short idxT;
typedef short cntT;
typedef short valT;

const cntT time24hN_digsLen[time24h_N]= {2,2};
const valT Tab_maxVal24hTime[time24h_N]= {23,59};

struct stakNode
{
    vector<bool>::iterator it;
};

inline bool isValid_24hTime(const vector<valT> &Time)
{
    if(Time.size()==time24h_N)
    {
        for(idxT i=0; i<time24h_N; ++i)
            if((Time[i]<0)||(Time[i]>Tab_maxVal24hTime[i]))
                return false;
        return true;
    }
    return false;
}

inline vector<valT> parse24hTime_digs(const vector<valT> &Digs)
{
    vector<valT> Time;
    auto it=Digs.begin();
    for(auto len:time24hN_digsLen)
    {
        valT t=0;
        for(cntT j=0; j<len; ++j,++it)
            if(it<Digs.end())
                if(t)
                    t*=10,t+=*it;
                else
                    t=*it;
            else
                return Time;
        Time.push_back(t);
    }
    return Time;
}

inline vector<valT> buildMax_24hTime(vector<valT> &Digs)
{
    vector<valT> Tmp;
    sort(Digs.begin(),Digs.end(),greater<valT>());
    vector<bool> Used(Digs.size());
    stack<stakNode> Stak;
    Stak.push({Used.begin()});
    idxT i=0;
    cntT j=0;
    while(!Stak.empty())
    {
        bool flag=true;
        if(i==time24h_N)
        {
            auto Time=parse24hTime_digs(Tmp);
            if(isValid_24hTime(Time))
                return Time;
        }
        else
        {
            auto &node=Stak.top();
            if((node.it)>Used.begin())
                Tmp.pop_back(),*(node.it-1)=false;
            for(auto it=node.it; it<Used.end(); ++it)
                if(!*it)
                {
                    Tmp.push_back(Digs[it-Used.begin()]),*it=true,Stak.push({Used.begin()}),node.it=it+1,flag=false;
                    if(++j==time24hN_digsLen[i])
                        ++i,j=0;
                    break;
                }
        }
        if(flag)
        {
            Stak.pop();
            if(--j==-1)
            {
                --i;
                if(i>=0)
                    j=(cntT)(time24hN_digsLen[i]-1);
            }
        }
    }
    return Tmp;
}

int main()
{
    vector<valT> Digs;
    while(Digs.size()<MAX_N)
    {
        valT a=0;
        cin>>a,Digs.push_back(a);
    }
    auto max24hTime=buildMax_24hTime(Digs);
    for(auto it=max24hTime.begin(); it<max24hTime.end(); ++it)
    {
        cout<<setfill('0')<<setw(time24hN_digsLen[it-max24hTime.begin()])<<*it;
        if(it<(max24hTime.end()-1))
            cout<<':';
        else
            cout<<endl;
    }
    return 0;
}
