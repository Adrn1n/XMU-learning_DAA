/*
最长递增队伍

描述

在《明日方舟》中，干员们按照一定的战斗力值排列。博士需要从中选择一些干员组成一个队伍，要求队伍的战斗力值严格递增。求最长的严格递增队伍的长度。

输入

    第一行包含一个整数N，表示干员的数量。
    第二行包含N个整数，表示每个干员的战斗力值。

输出

输出一个整数，表示最长严格递增队伍的长度。

输入样例 1

7
3 1 2 1 8 5 6

输出样例 1

4


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef long long valT;

idxT getMax_incrsSubArrLen(vector<valT> &A)
{
    if(!A.empty())
    {
        vector<idxT> Len(A.size());
        Len.front()=1;
        for(idxT i=1; (size_t)i<A.size(); ++i)
        {
            idxT maxLen=1;
            for(idxT j=0; j<i; ++j)
                if(A[i]>A[j])
                    maxLen=max(maxLen,Len[j]+1);
            Len[i]=maxLen;
        }
        return *max_element(Len.begin(),Len.end());
    }
    return 0;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        vector<valT> A(n);
        for(auto &a:A)
            cin>>a;
        cout<<getMax_incrsSubArrLen(A)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
