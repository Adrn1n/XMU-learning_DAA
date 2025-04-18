/*
最长操作序列

描述

在《金铲铲之战》的战场上，你拥有两名英雄，他们的技能连招分别可以表示为字符串A（长度为N）和字符串B（长度为M）。你希望找到一个最长的连续操作序列，这个序列既能在英雄A的技能连招中按顺序出现，又能在英雄B的技能连招中按顺序出现。

你的任务是计算出这个最长公共子序列的长度，以帮助你制定最优的战斗策略！

输入

第一行包含两个整数N和M。

第二行包含一个长度为N的字符串，表示字符串A。

第三行包含一个长度为M的字符串，表示字符串B。

字符串均由小写字母构成。

输出

输出一个整数，表示最大长度。

输入样例 1

4 5
acbd
abedc

输出样例 1

3


*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef vector<idxT> idxVec;

inline idxT get_LCS(string &A,string &B)
{
    idxT LCS=0;
    if((!A.empty())&&(!B.empty()))
    {
        auto len1=A.size(),len2=B.size();
        vector<idxVec> Tmp(2,idxVec(len1));
        for(idxT i=0; (size_t)i<len2; ++i)
            for(idxT j=0; (size_t)j<len1; ++j)
            {
                if(A[j]==B[i])
                    LCS=1;
                else
                    LCS=0;
                if(j)
                    Tmp[i%2][j]=max({Tmp[(i+1)%2][j-1]+LCS,Tmp[(i+1)%2][j],Tmp[i%2][j-1]});
                else
                    Tmp[0][0]=LCS;
            }
        LCS=Tmp[(len2-1)%2].back();
    }
    return LCS;
}

int main()
{
    idxT N=0,M=0;
    cin>>N>>M;
    if((N>0)&&(M>0))
    {
        string A,B;
        cin>>A>>B;
        cout<<get_LCS(A,B)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
