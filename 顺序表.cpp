#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define OVERFLOW -1
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int Status;
typedef char ElemType;

typedef struct SqList {
	ElemType* elem; //存储空间地址
	//ElemType* newbase;
	int length; //当前长度
	int listsize; //当前分配的存储容量
} SqList;

Status InintList_Sq(SqList & L)
{
	L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)exit(OVERFLOW); //存储分配失败
	L.length = 0; //空表长度为0
	L.listsize = LIST_INIT_SIZE; //初始存储容量
	return OK;
}

Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	ElemType* newbase;
	ElemType* q;
	ElemType* p;
	if (i<1 || i>L.length + 1) return ERROR; //i值不合法
	if (L.length >= L.listsize) { //当前存储空间已满，增加分配
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW); //存储分配失败
		L.elem = newbase; //新地址
		L.listsize += LISTINCREMENT; //增加存储容量
	}
	q = &(L.elem[i - 1]); //q为插入位置
	for (p = &(L.elem[L.length - 1]); p >= q; --p) { 
		*(p + 1) = *p;  //插入位置及以后的元素右移
	}
	*q = e; //插入e
	++L.length; //表长增加1
	return OK;
}

Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	ElemType* p;
	ElemType* q;
	if ((i < 1) || (i > L.length - 1)) return ERROR; //i值不合法
	p = &(L.elem[i - 1]); //p为被删除元素的位置
	e = *p; //被删除元素的值赋给e
	q = L.elem + L.length - 1; //表尾元素的位置
	for (++q; p <= q; ++p) *(p - 1) = *p; //被删除元素之后位置左移
	--L.length;
	return OK;
}

/*int LocateRlem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	int i;
	ElemType* p;
	i = 1;
	p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}

Status DispSqlist( const SqList& L)
{
	for (int i = 0; i < L.length; i++)
	{
		cout << L.elem[i] << endl;
	}
	return  0;
}*/

ElemType GetElem(SqList L, int i) {
	for (int j = 0; j < L.length; j++) {
		cout << j + 1 << " . " << L.elem[j] << endl;
	}
	cout << endl;
	return OK;
}

int main()
{
	SqList l;	
	InintList_Sq(l);
	int i, j;
	ElemType e;
	cout << "please input numbers:";
	cin >> i;
	cout << "please input :";
	for ( j = 1; j <= i; j++) {
		cin >> e;
		ListInsert_Sq(l, j, e);
	} //顺序表插入
	GetElem(l, i);
	cout << "please input numbers:";
	cin >> j;
	ListDelete_Sq(l, j, e); //顺序表删除
	cout << "delete : " << e << endl;
	GetElem(l, i);
	return 0;
}