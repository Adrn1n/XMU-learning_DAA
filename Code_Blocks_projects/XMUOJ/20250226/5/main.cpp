/*
攀登组合

描述

在提瓦特大陆的璃月港外，隐藏着一座传说中的「元素殿堂」，据说殿堂中蕴藏着远古元素的神秘力量，只有真正的冒险者才能开启其秘密。殿堂前有一段台阶，共计 N 级，每级台阶都仿佛闪烁着微弱的元素光芒。传说中，勇敢的旅行者（或冒险者）可以选择两种方式来攀登：

    每次迈一步，或
    每次迈两步。

每一种不同的攀登组合都可能引发不同的元素奇遇。请问，为了抵达这座神秘殿堂，旅行者总共有多少种不同的攀登方式？

输入

第一行是整数q表示测试实例的个数。

然后是Q行数据，每行包含一个整数N（1<=N<=40）,表示台阶的级数。

输出

一共q行，每行表示不同的走法总数。

输入样例 1

3
20
30
40

输出样例 1

10946
1346269
165580141

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_4885_test_cases.zip)
*/

#include <iostream>
#include <vector>

#define N_MAX 40

using namespace std;

typedef short idxT;
typedef int valT;
typedef int cntT;

int main()
{
    cntT q=0;
    cin>>q;
    vector<valT> A= {1,2};
    while(q-->0)
    {
        idxT N=0;
        cin>>N;
        if((N>0)&&(N<=N_MAX))
        {
            if(A.size()<(size_t)(N))
                for(idxT i=(idxT)(A.size()); i<N; ++i)
                    A.push_back(A[i-1]+A[i-2]);
            cout<<A[N-1]<<endl;
        }
        else
            cout<<"ERROR"<<endl;
    }
    return 0;
}
