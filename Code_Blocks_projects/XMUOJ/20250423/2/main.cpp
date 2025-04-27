/*
课程列表

描述

在《王者荣耀》的世界中，召唤师需要完成一系列技能训练课程，编号从 0 到 numCourses - 1。​

某些课程有先修要求，必须在学习特定课程之前完成。​

给定课程总数 numCourses 和先修课程列表 prerequisites，其中 prerequisites[i] = [ai, bi] 表示要学习课程 ai，必须先完成课程 bi。​

请判断召唤师是否可以完成所有课程的学习？如果可以，返回 true；否则，返回 false。

输入

每个输入文件包含：​

    第一行一个整数 numCourses，表示课程总数。

    接下来的若干行，每行两个整数 ai 和 bi，表示课程 ai 的先修课程为 bi

输出

每个输出文件包含一个布尔值：​

    true：可以完成所有课程的学习。

    false：无法完成所有课程的学习。


示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。

示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

输入样例 1

2
1 0

输出样例 1

true

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5307_test_cases.zip)
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
