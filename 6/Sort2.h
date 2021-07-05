#include<iostream>
#include<fstream>
using namespace std;
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 20000
#define MAX_SPACE 20000
#define MAX_NUM_OF_KEY 8  //关键字项数的最大值，基数排序
#define RADIX 10
int d[]={16383,8191,4095,2047,1023,511,255,127,63,31,15,7,3,1};
typedef int KeyType;
typedef int KeysType;
typedef int Status;
typedef struct{
	KeyType key;
}RcdType,RcdTypes[MAXSIZE+1];
typedef struct{
	RcdType r[MAXSIZE+1];//r[0]闲置
	int length;
}SqList;
typedef struct{
	KeysType keys[MAX_NUM_OF_KEY];//关键字
	int next;
}SLCell,SLCells[MAX_SPACE+1];//静态链表的结点类型
typedef struct{
	SLCell r[MAX_SPACE+1];//静态链表的可利用空间，r[0]为头结点
	int keynum;//记录当前关键字个数
	int recnum;//静态链表的当前长度
}SLList;//静态链表类型
typedef int ArrType[RADIX];
typedef SqList HeapType;
Status InitList(SqList &L,string a)
{
	fstream in;
	char filename[81];
	for(int i=0;i<a.length();i++)
	{
		filename[i]=a[i];
	}
	filename[a.length()]='\0';
	in.open(filename,ios::in);
	if(!in)
	{
		cout<<"文件打开失败."<<endl;
		exit(0);
	}
	L.r[0].key=0;
	for(int i=1;i<=20000;i++)
	{
		in>>L.r[i].key;
	}
	L.length=20000;
	in.close();
	return OK;
}
void ShellInsert(SqList &L, int dk)
{
	int i,j;
	for(i=dk+1;i<=L.length;++i)
	{
		if(L.r[i].key<L.r[i-dk].key)
		{
			L.r[0]=L.r[i];
			for(j=i-dk;j>0&&(L.r[0].key<L.r[j].key);j=j-dk)
			{
				L.r[j+dk]=L.r[j];
			}
			L.r[j+dk]=L.r[0];
		}
	}
}
void ShellSort(SqList &L, int dlta[], int t)
{
	for(int k=0;k<t;++k)
	{
		ShellInsert(L,dlta[k]);
	}
}
void InsertSort(SqList &L)
{
	int n=L.length;
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(L.r[i].key<L.r[i-1].key)
		L.r[0]=L.r[i];
		for(j=i-1;(L.r[j].key>L.r[0].key);--j)
		{
			L.r[j+1]=L.r[j];
		}
		L.r[j+1]=L.r[0];
	}
}
int Patition(SqList &L,int low, int high)
{
	KeyType pivotkey;
	L.r[0].key=L.r[low].key;//用表的第一个空间记录作枢轴记录
	pivotkey=L.r[low].key;
	while(low<high)
	{
		while(low<high&&L.r[high].key>=pivotkey)	--high;
		L.r[low].key=L.r[high].key;
		while(low<high&&L.r[low].key<=pivotkey)	++low;
		L.r[high].key=L.r[low].key;
	}
	L.r[low].key=L.r[0].key;
	return low;
}
void QSort(SqList &L,int low, int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=Patition(L,low,high);
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}
}
Status QuickSort(SqList &L)
{
	QSort(L,1,L.length);
	return OK;
}
Status BubbleSort(SqList &L)
{
	int LastPos,temp,j;
	LastPos=L.length;
	j=LastPos;
	while(j>1)
	{
		LastPos=1;
		for(int i=1;i<j;++i)
		{
			if(L.r[i].key>L.r[i+1].key)
			{
				temp=L.r[i].key;
				L.r[i].key=L.r[i+1].key;
				L.r[i+1].key=temp;
				LastPos=i;
			}
		}
		j=LastPos; 
	}
	return OK;
}
Status SelectSort(SqList &L)
{
	int min;
	for(int i=1;i<=L.length;++i)
	{
		min=i;
		for(int j=i+1;j<=L.length;++j)
		{
			if(L.r[j].key<L.r[min].key)
			{
				min=j;
			}
		}
		if(i!=min)
		{
			L.r[0].key=L.r[i].key;
			L.r[i].key=L.r[min].key;
			L.r[min].key=L.r[0].key;
		}
	}
	return OK;
}
void Merge(RcdType A[],int p,int q,int r)
{
    int i,j,k;
    int n1=q-p+1;
    int n2=r-q;
    RcdType *L=new RcdType[n1+1]; //开辟临时存储空间
    RcdType *R=new RcdType[n2+1];
    for(i=0;i<n1;i++)
        L[i]=A[i+p];      //数组下标从0开始时，这里为i+p
    for(j=0;j<n2;j++)
        R[j]=A[j+q+1];    //数组下标从0开始时，这里为就j+q+1
    L[n1].key=INT_MAX;        //"哨兵"设置为整数的最大值，INT_MAX包含在limits.h头文件中
    R[n2].key=INT_MAX;
    i=0;
    j=0;
    for(k=p;k<=r;k++)     //开始合并
    {
        if(L[i].key<=R[j].key)
            A[k].key=L[i++].key;
        else
            A[k].key=R[j++].key;
    }
}
void MSort(RcdType A[],int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        MSort(A,p,q);
        MSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
Status MergeSort(SqList &L)
{
	MSort(L.r,1,L.length);
}
void HeapAdjust(HeapType &H, int s, int m)
{
	RcdType rc=H.r[s];
	int i;
	for(i=2*s; i<=m; i*=2)
	{
		if(i<m&&H.r[i].key<H.r[i+1].key)
			++i;
		if(!(rc.key<H.r[i].key))
			break;
		H.r[s]=H.r[i];
		s=i;
	}
	H.r[s]=rc;
}
Status HeapSort(SqList &L)
{
	RcdType temp;
	int i;
	for(i=L.length/2;i>0;--i)
	{
		HeapAdjust(L,i,L.length);
	}
	for(i=L.length;i>1;--i)
	{
		temp=L.r[1];
		L.r[1]=L.r[i];
		L.r[i]=temp;
		HeapAdjust(L,1,i-1);
	}
	return OK;
}
Status ListTraverse(SqList L)
{
	for(int i=1;i<=L.length;++i)
	{
		cout<<L.r[i].key<<" ";
	}
	cout<<endl;
	return OK;
}
Status InitSLList(SLList &L,string a)
{
	int key;
	fstream in;
	char filename[81];
	for(int i=0;i<a.length();i++)
	{
		filename[i]=a[i];
	}
	filename[a.length()]='\0';
	in.open(filename,ios::in);
	if(!in)
	{
		cout<<"文件打开失败."<<endl;
		exit(0);
	}
	L.keynum=3;
	for(int i=1;i<=20000;i++)
	{
		in>>key;
		for(int j=L.keynum-1;j>=0;--j)
		{
			L.r[i].keys[j]=key%10;
			key=key/10;
		}
	}
	L.recnum=20000;
	return OK;
}
void Distribute(SLCell *r, int i, ArrType &f, ArrType &e)
{
	int p,j;
	for(j=0;j<RADIX;j++)
	{
		f[j]=0;
		e[j]=0;
	}
	for(p=r[0].next;p;p=r[p].next)
	{
		j=r[p].keys[i];
		if(!f[j])
		{
			f[j]=p;
			e[j]=p;
		}
		else
		{
			r[e[j]].next=p;
			e[j]=p;
		}
	}
}
void Collect(SLCell *r, int i, ArrType f,ArrType e)
{
	int j,t,p;
	for(j=0;!f[j];j++)
		;
	r[0].next=f[j];
	t=e[j];
	while(j<RADIX)
	{
		for(j++;j<(RADIX-1)&&!f[j];j++)
			;
		if(f[j]&&j<RADIX)
		{
			r[t].next=f[j];
			t=e[j];
		}
	}
	r[t].next=0;
}
void RadixSort(SLList &L)//基数排序
{
	int i,p;
	ArrType f;
	ArrType e;
	for(i=0; i<L.recnum;++i)
	{
		L.r[i].next=i+1;
	}
	L.r[L.recnum].next=0;
	for(i=0;i<L.keynum;++i)
	{
		Distribute(L.r,i,f,e);
		Collect(L.r,i,f,e);
	}
}
void PrintRadixSort(SLList &L)
{
	int p;
	for(p=L.r[0].next;p;p=L.r[p].next)
	{
		for(int j=L.keynum-1;j>=0;j--)
		{
			cout<<L.r[p].keys[j];
		}
		cout<<" ";
	}
	cout<<endl;
}
