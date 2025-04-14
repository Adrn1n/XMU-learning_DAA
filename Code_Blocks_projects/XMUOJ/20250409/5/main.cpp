/*
移除数字

描述

​在《王者荣耀》的世界中，您作为战队的指挥官，拥有一个由数字组成的战术编号。​为了制定最佳战略，您需要从该编号中移除 K 位数字，使得剩下的数字组成的战术编号最小。​请注意，战术编号不能包含前导零。

输入

    第一行包含一个整数 K，表示需要移除的数字位数（0 <= K < 编号的长度）。​

    第二行是一个由数字组成的字符串，表示战术编号，长度不超过 1000 且不包含前导零。

输出

移除 K 位数字后能够得到的最小战术编号。

输入样例 1

3
1432219

输出样例 1

1219

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5273_test_cases.zip)
*/

#include <iostream>
#include <string>
#include <algorithm>

#define N_MAX 1000

using namespace std;

typedef short idxT;

inline bool isStrNO(const string &s)
{
    if(s.empty())
        return false;
    else
    {
        for(auto &c:s)
            if((c<'0')||(c>'9'))
                return false;
        return s[0]!='0';
    }
}

inline string getMinVal_rmKDigs(const string &NO,const idxT k)
{
    string res;
    if((isStrNO(NO))&&(k>=0)&&((size_t)k<NO.size()))
    {
        auto l=(idxT)(NO.size()-k);
        auto End=NO.rend();
        while(l-->0)
        {
            auto tmp=min_element(NO.rbegin()+l,End);
            for(auto it=tmp+1; it<End; ++it)
                if(*it==*tmp)
                    tmp=it;
            if((!res.empty())||(*tmp!='0'))
                res.push_back(*tmp);
            End=tmp;
        }
        if(res.empty())
            res.push_back('0');
    }
    return res;
}

int main()
{
    idxT k=0;
    cin>>k;
    bool flag=true;
    if((k>=0)&&(k<N_MAX))
    {
        string NO;
        cin>>NO;
        if(isStrNO(NO)&&((size_t)k<NO.size()))
            cout<<getMinVal_rmKDigs(NO,k)<<endl,flag=false;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
