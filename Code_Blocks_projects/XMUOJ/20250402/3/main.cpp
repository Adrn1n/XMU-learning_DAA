/*
最大利润2
描述

暖暖是一位时尚搭配师，她每天都在服装市场买卖服装单品。已知市场每天的某件限量单品价格随时间变化，暖暖最多可以进行两次交易（一次买入，一次卖出）。

请设计一个算法，帮助暖暖在最多两次买卖的情况下获得最大的金币利润。

规则：

暖暖不能同时持有多件同一单品（即买入前必须先卖出）。

暖暖最多只能交易两次。

给定数组prices，其中prices[i]表示第i天市场上该单品的价格，计算暖暖的最大收益。


输入

一个整数数组prices，其中prices[i]表示第i天时装的价格


输出

一个整数，表示暖暖能够从这笔交易中获得的最大利润。如果没有任何利润可图，返回0



示例 1:

输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。


示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。


示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这个情况下, 没有交易完成, 所以最大利润为 0。

输入样例 1

3 3 5 0 0 3 1 4
输出样例 1

6
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;
typedef vector<valT>::const_iterator valVec_cIt;

inline valT getMin_Delta(const valVec_cIt Start,const valVec_cIt End)
{
    valT minDelta=0,maxVal=0;
    if((End-Start)>1)
    {
        minDelta=Start[1]-Start[0],maxVal=*Start;
        for(auto it=Start+2; it<End; ++it)
            maxVal=max(maxVal,*(it-1)),minDelta=min(minDelta,*it-maxVal);
    }
    return minDelta;
}

inline valT getMax_2NOvrlapDelta(const vector<valT> &A)
{
    valT res=0;
    if(A.size()>1)
    {
        valT MaxDelta_cur=res=A[1]-A[0],MaxDelta_min=0;
        auto Start=A.begin(),End=A.begin()+2,minIt=A.begin();
        for(auto it=A.begin()+2; it<A.end(); ++it)
        {
            auto tmp=*(it-1);
            if(*minIt>=tmp)
            {
                if(*minIt>tmp)
                    minIt=it-1;
                MaxDelta_min=MaxDelta_cur;
            }
            if((*it-(*minIt))>=MaxDelta_cur)
            {
                if((*it-(*minIt))>MaxDelta_cur)
                    Start=minIt;
                MaxDelta_cur=*it-(*minIt),End=it+1;
            }
            res=max({res,*it-(*minIt),MaxDelta_min+(*it)-(*minIt)});
        }
        res=max(res,MaxDelta_cur-getMin_Delta(Start,End));
    }
    return res;
}

int main()
{
    valT val=0;
    vector<valT> A;
    while(cin>>val)
        A.push_back(val);
    cout<<max(getMax_2NOvrlapDelta(A),(valT)0)<<endl;
    return 0;
}
