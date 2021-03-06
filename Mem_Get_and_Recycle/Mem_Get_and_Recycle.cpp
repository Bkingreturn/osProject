// Mem_Get_and_Recycle.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MemGetRecycle.h"
#include <iostream>

using namespace std;

int main()
{
	int n;
	int id, x;
	cout << "请输入想要划分区域的个数：";
	cin >> n;
	CMemGetRecycle cmem(n);
	cmem.show();
	cout << "请输入你想要分配进程的id和想要分配的内存量：";
	cin >> id >> x;
	cmem.GetMem(id, x);
	cmem.show();
	cout << "请输入你想要回收的进程：";
	cin >> id;
	cmem.RecycleMem(id);
	cmem.show();
    return 0;
}

