/*
星海信息序列

描述

在遥远的星海中，两种古老的能量——星辰之力“S”与暗影之力“D”，交织成了一种独特的宇宙语言。这种语言的构建规则神秘而深邃，遵循着如下的创生法则：

最初，星辰之力以其纯净的形式展现，仅由一个符号“S”构成。随着宇宙的演化，每当星辰之力想要传递更深邃的信息时，它便会融合之前的信息序列S(n−1)，附加一个“S”，然后增添一段经过神秘变换的序列：将S(n−1)中的每个符号进行反转，即“S”变为“D”，“D”变为“S”，随后将这段新的序列进行倒置。因此，新的信息序列S(n)可以如此构建：
S(n) = S(n−1) + S + reverse(flip(S(n−1)))

其中，reverse(s)代表将字符串倒置，例如reverse(SSD) = DSS；flip(s)则表示将字符串中的“S”与“D”互换，例如flip(SSD) = DDS。

你的任务是在这个由“S”与“D”编织的无限长宇宙信息序列中，探寻从第L位到第R位（包含两端，位数从1开始计数）中“S”的数量。由于这个序列可以无限延伸，你需要针对每一次询问，给出精确的答案。

输入

第一行输入一个整数T，表示有T(1≤T≤1000)组询问。
每组询问包含两个数L和R(1≤L≤R≤10^18)，代表需要查询的序列区间。

输出

对于每组询问，输出S（2^64）所代表的宇宙信息序列的第L位到第R位中“S”的数量。

输入样例 1

3
1 3
1 7
4 8

输出样例 1

2
4
3

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_4919_test_cases.zip)
*/

#include <iostream>

#define T_MAX 1000
#define idx_MAX 1000000000000000000
#define N_MAX FFFFFFFFFFFFFFFF

using namespace std;

typedef long long idxT;
typedef short cntT;

idxT getN_S(const idxT &L,const idxT &R)
{
    idxT cnt=0;
    idxT l=L,r=R;
    while(l<r)
    {
        idxT len=r-l,oddN=(len>>1)+(len%2)*((l+1)%2);
        cnt+=((oddN>>1)+(oddN%2)*(((l+1)%2)*(((l+2)%4)>>1)+(l%2)*((l%4)>>1))),l>>=1,r>>=1;
    }
    return cnt;
}

int main()
{
    cntT T=0;
    cin>>T;
    if((T>0)&&(T<=T_MAX))
        while(T--)
        {
            idxT L=0,R=0;
            cin>>L>>R;
            if((L<=R)&&(L>=1)&&(R<=idx_MAX))
                cout<<getN_S(L-1,R)<<endl;
            else
                cout<<"ERROR!"<<endl;
        }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
