#pragma once

struct FreeZone
{
	int id;			//������
	bool status;     //״̬λ����0����ʾ�������У���1����ʾ�����ѷ��䡣
	int length;      //�����Ĵ�С�����ֽڻ���Ϊ��λ����
	FreeZone *previous; //ָ��ǰһ��������
	FreeZone *next;		//ָ����һ������ȥ
};

class CMemGetRecycle
{
private:
	FreeZone * head,*rear;    //ͷָ��
	int num;   //���������Ľڵ����
	int size;
public:
	CMemGetRecycle(int size);   //��ʼ��������
	~CMemGetRecycle();
	void GetMem(FreeZone *fz);     //���������
	void RecycleMem(int id); //���տ�����
	void show();        //��ʾ��������״̬
};

