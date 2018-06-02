#pragma once

struct FreeZone
{
	int id;			//进程名
	bool status;     //状态位，“0”表示分区空闲，“1”表示分区已分配。
	int length;      //分区的大小（以字节或字为单位）。
	FreeZone *previous; //指向前一个空闲区
	FreeZone *next;		//指向下一个空闲去
};

class CMemGetRecycle
{
private:
	FreeZone * head,*rear;    //头指针
	int num;   //空闲区链的节点个数
	int size;
public:
	CMemGetRecycle(int size);   //初始化空闲区
	~CMemGetRecycle();
	void GetMem(FreeZone *fz);     //分配空闲区
	void RecycleMem(int id); //回收空闲区
	void show();        //显示空闲区链状态
};

