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
		cout << "�������" << i + 1 << "�����з����ĳ��ȣ�";
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
	FreeZone *ptem,*pnew;  //����ָ��
	ptem = head->next;
	int i;
	pnew = new FreeZone;
	pnew->id = id;
	pnew->length = x;
	pnew->status = true;
	for (i = 0; i < num; i++) {
		//����������ڽ���������ڴ�
		if (ptem->length > x) {
			//����������һ��Ϊ��
			pnew->previous = ptem->previous;
			ptem->previous->next = pnew;
			pnew->next = ptem;
			ptem->previous = pnew;
			ptem->length = ptem->length - x;
			num++;
			break;
		}
		//����������ڽ���������ڴ�
		else if (ptem->length ==x) {
			//����������һ��Ϊ��
			ptem->id = id;
			ptem->status = true;
			break;
		}
		ptem = ptem->next;
	}
	if (i == num) cout << "û�������������Ŀ����������Ժ����ԣ�" << endl;
}

void CMemGetRecycle::RecycleMem(int id) {
	//�ҵ�������Ϊid�Ľڵ�
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
	if (!ptem->next) cout << "�Ҳ����ý��̣�" << endl;
	//ptem���ڵ�����Ϊ��Ҫ���յ�����

	//x�����ں����ڶ��Ѿ�����
	if (ptem->previous->status == true && ptem->next->status == true) {
		ptem->id = 0;
		ptem->status = false;
		delete ptem;
		delete pltem;
		delete phtem;
	}
	
	//x�������ѷ��䣬����δ����
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
	

	//x������δ���䣬�����ѷ���
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
	//x�����ں����ڶ�δ����
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
		cout << "����������idΪ��0��ʾû�н��̣�:" << ptem->next->id << endl;
		cout << "����������Ϊ��" << ptem->next->length << endl;
		cout << "������״̬Ϊ��" << ptem->next->status << endl;
		ptem = ptem->next;
	}

}