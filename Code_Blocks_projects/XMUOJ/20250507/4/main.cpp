/*
括号秘语

描述

在提瓦特大陆的一次冒险中，旅行者与派蒙在古代遗迹中发现了一块刻有“括号密语”的神秘石碑。派蒙惊讶地发现，这些密语由成对括号组成，只有完全匹配的括号组合才会揭示真正的线索。

派蒙请你帮忙，给定一个数字n，代表括号对数，请你列出所有可能的有效括号组合，以便破解密语内容。

输入

一个正整数n，表示要生成的括号对数。

输出

所有由n对括号组成的有效括号组合（任意顺序），用空格分隔输出。

输入样例 1

1

输出样例 1

()

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5336_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef long long idxT;

enum valT2 {val_a,val_b};

typedef vector<valT2> valT2_Vec;

struct stakNode
{
    idxT cnt_a,cnt_b;
    bool chose_a,isOver;
};

inline vector<valT2_Vec> enum_allLoc_a_Ge_b(const idxT n)
{
    vector<valT2_Vec> Res;
    valT2_Vec A;
    stack<stakNode> Stak;
    do
    {
        stakNode node= {0,0,true,false};
        if(!Stak.empty())
            node=Stak.top();
        if(node.isOver)
            if((node.chose_a)&&(node.cnt_a>(node.cnt_b+1)))
            {
                auto &tmp=Stak.top();
                A.back()=val_b,--(tmp.cnt_a),++(tmp.cnt_b),tmp.chose_a=tmp.isOver=false;
            }
            else
            {
                A.pop_back(),Stak.pop();
                if(!Stak.empty())
                    (Stak.top()).isOver=true;
            }
        else
        {
            if(node.cnt_a<n)
                A.push_back(val_a),++(node.cnt_a),node.chose_a=true,Stak.push(node);
            else if(node.cnt_b<n)
                A.push_back(val_b),++(node.cnt_b),node.chose_a=false,Stak.push(node);
            else
                Res.push_back(A),(Stak.top()).isOver=true;
        }
    }
    while(!Stak.empty());
    return Res;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        auto A=enum_allLoc_a_Ge_b(n);
        for(auto &a:A)
        {
            for(auto &val:a)
                switch(val)
                {
                case val_a:
                {
                    cout<<'(';
                    break;
                }
                case val_b:
                {
                    cout<<')';
                    break;
                }
                default:
                    cout<<"ERROR!"<<endl;
                }
            cout<<' ';
        }
        cout<<endl;
    }
    return 0;
}
