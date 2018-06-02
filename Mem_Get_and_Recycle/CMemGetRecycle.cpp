#include "stdafx.h"
#include "MemGetRecycle.h"
#include<iostream>
using namespace std;

CMemGetRecycle::CMemGetRecycle(int size)
{
	num = n;
	head = new FreeZone;
	head->previous = NULL;
	head->next = NULL;
	head->length = 0;
	head->id = 0;
	head->status = false;
	FreeZone *pnew, *ptem;
	ptem = head;
	for (int i = 0; i < num; i++) {
		pnew = new FreeZone;
		cout << "请输入第" << i + 1 << "个空闲分区的长度：";
		cin >> (pnew->length);
		pnew->length = sizeof(pnew->length)*pnew->length/4;
		pnew->status = false;
		pnew->next = NULL;
		pnew->previous = ptem;
		pnew->id = 0;
		ptem->next = pnew;
		ptem = pnew;
	}
}

CMemGetRecycle::~CMemGetRecycle()
{
	delete	head;
	num = 0;
}

void CMemGetRecycle::GetMem(FreeZone *fz) {
	FreeZone *ptem,*pnew;  //工作指针
	ptem = head->next;
	int i;
	pnew = new FreeZone;
	pnew->id = id;
	pnew->length = x;
	pnew->status = true;
	for (i = 0; i < num; i++) {
		//空闲区域大于进程申请的内存
		if (ptem->length > x) {
			//将空闲区链一分为二
			pnew->previous = ptem->previous;
			ptem->previous->next = pnew;
			pnew->next = ptem;
			ptem->previous = pnew;
			ptem->length = ptem->length - x;
			num++;
			break;
		}
		//空闲区域等于进程申请的内存
		else if (ptem->length ==x) {
			//将空闲区链一分为二
			ptem->id = id;
			ptem->status = true;
			break;
		}
		ptem = ptem->next;
	}
	if (i == num) cout << "没有满足进程需求的空闲区，请稍后重试！" << endl;
}

void CMemGetRecycle::RecycleMem(int id) {
	//找到进程名为id的节点
	FreeZone *ptem=head;
	FreeZone *pltem=head;
	FreeZone *phtem=head;
	while (ptem->next) {
		if (ptem->next->id == id) {
			ptem = ptem->next;
			pltem = phtem = ptem;
			break;
		}
		else {
			ptem = ptem->next;
		}
	}
	if (!ptem->next) cout << "找不到该进程！" << endl;
	//ptem所在的区域为想要回收的区域

	//x的上邻和下邻都已经分配
	if (ptem->previous->status == true && ptem->next->status == true) {
		ptem->id = 0;
		ptem->status = false;
		delete ptem;
		delete pltem;
		delete phtem;
	}
	
	//x的上邻已分配，下邻未分配
	else if (ptem->previous->status == true||!ptem->next){
		int i = 0;
		while (pltem->next->status==false&&pltem->next) {
			pltem->length = pltem->length + pltem->next->length;
			pltem = pltem->next;
			i++;
		}
		ptem->previous->next = pltem->next;
		pltem->previous = ptem->previous;
		num -= i;
		delete ptem;
		delete pltem;
		delete phtem;
	}
	

	//x的上邻未分配，下邻已分配
	else if (ptem->next->status == true||!ptem->next) {
		int i=0;
		while (phtem->previous&&phtem->previous->status == false) {
			phtem->length = phtem->length + phtem->previous->length;
			phtem = phtem->previous;
			i++;
		}
		phtem->next = ptem->next;
		ptem->next->previous = phtem;
		num-=i;
		delete ptem;
		delete pltem;
		delete phtem;
	}
	//x的上邻和下邻都未分配
	else if(ptem->previous&&ptem->next){
		int i=0;
		while (phtem->previous&&phtem->previous->status == false) {
			phtem->length = phtem->length + phtem->previous->length;
			phtem = phtem->previous;
			i++;
		}
		while (pltem->next->status == false && pltem->next) {
			pltem->length = pltem->length + pltem->next->length;
			pltem = pltem->next;
			i++;
		}
		phtem->length = phtem->length + pltem->length - ptem->length;
		phtem->previous->next = pltem->next;
		if (pltem->next) {
			pltem->next->previous = phtem->previous;
		}
		num -= i;
		delete ptem;
		delete pltem;
		delete phtem;
	}
}

void CMemGetRecycle::show() {
	FreeZone *ptem=head;
	while (ptem->next) {
		cout << "空闲区进程id为（0表示没有进程）:" << ptem->next->id << endl;
		cout << "空闲区长度为：" << ptem->next->length << endl;
		cout << "空闲区状态为：" << ptem->next->status << endl;
		ptem = ptem->next;
	}

}