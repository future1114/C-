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
	ElemType* elem; //�洢�ռ��ַ
	//ElemType* newbase;
	int length; //��ǰ����
	int listsize; //��ǰ����Ĵ洢����
} SqList;

Status InintList_Sq(SqList & L)
{
	L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)exit(OVERFLOW); //�洢����ʧ��
	L.length = 0; //�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE; //��ʼ�洢����
	return OK;
}

Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	ElemType* newbase;
	ElemType* q;
	ElemType* p;
	if (i<1 || i>L.length + 1) return ERROR; //iֵ���Ϸ�
	if (L.length >= L.listsize) { //��ǰ�洢�ռ����������ӷ���
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW); //�洢����ʧ��
		L.elem = newbase; //�µ�ַ
		L.listsize += LISTINCREMENT; //���Ӵ洢����
	}
	q = &(L.elem[i - 1]); //qΪ����λ��
	for (p = &(L.elem[L.length - 1]); p >= q; --p) { 
		*(p + 1) = *p;  //����λ�ü��Ժ��Ԫ������
	}
	*q = e; //����e
	++L.length; //������1
	return OK;
}

Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	ElemType* p;
	ElemType* q;
	if ((i < 1) || (i > L.length - 1)) return ERROR; //iֵ���Ϸ�
	p = &(L.elem[i - 1]); //pΪ��ɾ��Ԫ�ص�λ��
	e = *p; //��ɾ��Ԫ�ص�ֵ����e
	q = L.elem + L.length - 1; //��βԪ�ص�λ��
	for (++q; p <= q; ++p) *(p - 1) = *p; //��ɾ��Ԫ��֮��λ������
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
	} //˳������
	GetElem(l, i);
	cout << "please input numbers:";
	cin >> j;
	ListDelete_Sq(l, j, e); //˳���ɾ��
	cout << "delete : " << e << endl;
	GetElem(l, i);
	return 0;
}