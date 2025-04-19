/*
法力水量

描述

在《黑神话：悟空》的神秘世界里，齐天大圣携带着能够借助天罡神力的神秘法器——水镜。在这片天、地、水、火交织的战场上，每一条直立的神木就像天宫中矗立的神柱，记录着悟空曾经战斗的痕迹。
给定一个长度为 n 的整数数组，数组中的每个数字 height[i] 代表第 i 根神木的高度。悟空需要选择其中两根神木作为支撑，并利用它们以及大地（x 轴）构成一面神秘水镜，捕捉天地精华。
请帮助悟空找出能构成最大水镜的两根神木，使得它们与大地共同承载的神秘法力最大。
返回能储存的最大“法力水量”。

注意：不得倾斜水镜，否则天地之力将溢散！

输入

一个长度为 n 的整数数组

输出

一个整数，储存的最大“法力水量”

QQ截图20250413084514.png (./f3d1f5fb5d.png)

输入样例 1

1 8 6 2 5 4 8 3 7

输出样例 1

49

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5297_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;

inline valT getMax_S(const vector<valT> &A)
{
    valT res=0;
    if(!A.empty())
    {
        auto it1=A.begin(),it2=A.end()-1;
        while(it1<it2)
        {
            res=max(res,(it2-it1)*max(min(*it1,*it2),0ll));
            auto it=it1;
            if(*it1>*it2)
            {
                for(it=it2; (it>it1)&&(*it<=*it2); --it);
                it2=it;
            }
            else
            {
                for(; (it<it2)&&(*it<=*it1); ++it);
                it1=it;
            }
        }
    }
    return res;
}

int main()
{
    valT val=0;
    vector<valT> height;
    while(cin>>val)
        height.push_back(val);
    cout<<getMax_S(height)<<endl;
    return 0;
}
