/*
密码判断

描述

在王者峡谷的战术传送台中，每串战术密码是由一串纯数字构成的神秘字符串。真正的“荣耀战术密码”遵循一种特殊规律：

    该字符串由至少三个数字构成；

    从第三个数字开始，每个数字必须是它前两个数字之和（如 1, 1, 2, 3, 5, 8）；

    除了数字 0 本身外，所有数字不能以 0 开头。

你的任务是判断给定的字符串是否为“荣耀累加数”。

输入

一个只包含数字0-9的字符串s，表示荣耀战术密码。

输出

若s是合法的累加数，输出true，否则输出false。

示例 1：

输入："112358"输出：true
解释：累加序列为: 1, 1, 2, 3, 5, 8 。1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

示例 2：

输入："199100199"输出：true
解释：累加序列为: 1, 99, 100, 199。1 + 99 = 100, 99 + 100 = 199

输入样例 1

112358

输出样例 1

true

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5362_test_cases.zip)
*/

#include <iostream>
#include <string>

using namespace std;

inline bool couldNumStrIs_generFibo(const string &S)
{
    if(S.empty())
        return true;
    else
    {
        for(auto it=S.begin(); it<S.end(); ++it)
            if((*it<'0')||(*it>'9'))
                return false;
        for(auto it1=S.begin()+1; it1<(S.end()-1); ++it1)
            for(auto it2=it1+1; it2<S.end(); ++it2)
            {
                string s1=string(S.begin(),it1),s2=string(it1,it2),str=string(it2,S.end()),s;
                for(auto val1=stoll(s1),val2=stoll(s2),val=val1+val2; s=to_string(val),str.rfind(s,0)==0; val1=val2,val2=val,val=val1+val2)
                {
                    str=str.substr(s.size());
                    if(str.empty())
                        return true;
                }
            }
        return false;
    }
}

int main()
{
    string s;
    char c;
    while(cin>>c)
        if((c>='0')&&(c<='9'))
            s.push_back(c);
        else
            break;
    if(couldNumStrIs_generFibo(s))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    return 0;
}
