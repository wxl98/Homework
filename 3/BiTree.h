#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW -2
#define INFEASIBLE -1
#define ERROR 0
#define OK 1
#define INIT_STACK_SIZE 100
#define INCREMENT_SIZE 10
#define N 100
typedef int Status;
typedef char Elem;
typedef struct BiTNode{
	Elem data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;
typedef struct{
	char tag;
	BiTNode *ptr;
}StackNode;
typedef struct Stack{
	StackNode *Elem;
	int top;
	int stacksize;
}Stack;
typedef struct QNode{
	BiTree data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct LinkQueue{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	Q.front=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);
	Q.rear=Q.front;
	Q.front->next=NULL;
}
Status EnQueue(LinkQueue &Q, BiTree &e)
{
	QNode *p=(QNode*)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data=e;
	Q.rear->next=p;
	p->next=NULL;
	Q.rear=p;
	return OK;
}
Status DeQueue(LinkQueue &Q, BiTree &e)
{
	if(Q.rear==Q.front)
	{
		return ERROR;
	}
	QNode *p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK;
}
Status EmptyQueue(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return OK;
	else
		return ERROR;
}
Status DestroyQueue(LinkQueue &Q)
{
	if(Q.front!=NULL)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}
Status InitStack(Stack &S)
{
	S.Elem=(StackNode*)malloc(sizeof(StackNode)*INIT_STACK_SIZE);
	if(!S.Elem)
		exit(OVERFLOW);
	S.top=0;
	S.stacksize=INIT_STACK_SIZE;
	return OK;
}
Status EmptyStack(Stack S)
{
	if(S.top==0&&S.Elem)
		return OK;
	else
		return ERROR;
}
Status Push(Stack &S, StackNode x)
{
	if(S.top>=S.stacksize)
	{
		S.Elem=(StackNode*)realloc(S.Elem,sizeof(StackNode)*(S.stacksize+INCREMENT_SIZE));
		if(!S.Elem)
			exit(OVERFLOW);
		S.stacksize=S.stacksize+INCREMENT_SIZE;
	}
	S.Elem[S.top]=x;
	S.top++;
	return OK;
}
Status Pop(Stack &S, StackNode &x)
{
	if(S.top==0)
		return ERROR;
	x=S.Elem[S.top-1];
	S.top--;
	return OK; 
}
Status DestroyBiTree(BiTree &T)
{
	if(T!=NULL)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
	return OK;
}
Status CreateBiTree(BiTree &T)//按照先序顺序创造二叉树,以空格为空树。 
{
	char temp;
	scanf("%c",&temp);
	if(temp!=' ')
	{
		T=(BiTNode*)malloc(sizeof(BiTNode));
		if(!T)
			exit(OVERFLOW);
		T->data=temp;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	else
		T=NULL;
	return OK;
}
int Search(char S[],char t)
{
	for(int i=0;S[i]!='\0';i++)
	{
		if(S[i]==t)
			return i;
	}
	return -1;
}
void CrtBT(BiTree &T,char pre[],char ino[],int ps,int is,int n)//通过先序序列跟中序序列建立一颗二叉树
{
	if(n==0)
		T=NULL;
	else
	{
		int k=Search(ino,pre[ps]);
		if(k==-1)
			T=NULL;
		else
		{
			T=(BiTNode*)malloc(sizeof(BiTNode));
			if(!T)
				exit(OVERFLOW);
			T->data=pre[ps];
			if(k==is)
				T->lchild=NULL;
			else
			{
				CrtBT(T->lchild,pre,ino,ps+1,is,k-is);
			}
			if(k==n-1+is)
				T->rchild=NULL;
			else
			{
				CrtBT(T->rchild,pre,ino,ps+1+k-is,k+1,n-k+is-1);
			}
		}
	}
	return;
}
Status CreateBiTree_File(BiTree &T) 
{
	FILE *fp;
	char filename[81],pre[N],ino[N];
	printf("please input the filename of the Tree's infomation:\n");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(!fp)
	{
		printf("Can not find file!\n");
		exit(ERROR);
	}
	fgets(pre,N,fp);
	fgets(ino,N,fp);
	CrtBT(T,pre,ino,0,0,strlen(pre));
	fclose(fp);
	return OK;
}
Status PreOrderTraverse(BiTree T,Status (*Visit)(Elem e))
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}
Status InOrderTraverse(BiTree T, Status (*Visit)(Elem e))
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return OK;
		else
			return ERROR;
	}
	return OK;
}
Status PostOrderTraverse(BiTree T, Status (*Visit)(Elem e))
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
					return OK;
		else
			return ERROR;
	}
	return OK;
}
Status Visit(Elem e)
{
	printf("%c",e);
	return OK;
}
Status LevelOrderTraverse(BiTree T, Status (*Visit)(Elem e))
{
	BiTree p;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,T);
	while(!EmptyQueue(Q))
	{
		DeQueue(Q,p);
		if(p)
		{
			Visit(p->data);
			EnQueue(Q,p->lchild);
			EnQueue(Q,p->rchild);
		}
	}
	printf("\n");
	return OK;
}
Status PreOrderTraverse_S(BiTree T,Status (*Visit)(Elem e))
{
	Stack S;
	InitStack(S);
	BiTree t=T;
	StackNode x;
	while(t||!EmptyStack(S))
	{
		while(t)
		{
			Visit(t->data);
			x.ptr=t;
			Push(S,x);
			t=t->lchild;
		}
		if(!EmptyStack(S))
		{
			Pop(S,x);
			t=x.ptr->rchild;
		}
	}
	printf("\n");
	return OK;
}
Status InOrderTraverse_S(BiTree T, Status (*Visit)(Elem e))
{
	Stack S;
	InitStack(S);
	BiTree t=T;
	StackNode x;
	while(t||!EmptyStack(S))
	{
		while(t)
		{
			x.ptr=t;
			Push(S,x);
			t=t->lchild;
		}
		if(!EmptyStack(S))
		{
			Pop(S,x);
			t=x.ptr;
			Visit(t->data);
			t=t->rchild;
		}
	}
	printf("\n");
	return OK;
}
Status PostOrderTraverse_S(BiTree T)
{
	Stack S;
	InitStack(S);
	StackNode x;
	BiTree t=T;
	do
	{
		while(t)
		{
			x.tag='L';
			x.ptr=t;
			Push(S,x);
			t=t->lchild;
		}
		while(!EmptyStack(S)&&S.Elem[S.top-1].tag=='R')
		{
			Pop(S,x);
			t=x.ptr;
			printf("%c",t->data);
		}
		if(!EmptyStack(S))
		{
			S.Elem[S.top-1].tag='R';
			t=S.Elem[S.top-1].ptr->rchild;
		}
	}while(!EmptyStack(S));
	printf("\n");
	return OK;
}
int Height(BiTree T)
{
	int Hei_l,Hei_r,Hei;
	if(T)
	{
		Hei_l=Height(T->lchild);
		Hei_r=Height(T->rchild);
		Hei=((Hei_l>Hei_r)?Hei_l:Hei_r)+1;
		return Hei;
	}
	return 0;
}
void CountNodes(BiTree T,int &num)
{
	if(T)
	{
		num++;
		CountNodes(T->lchild,num);
		CountNodes(T->rchild,num);
	}
}
int BiTreeWidth(BiTree T)//求数的宽度即求每一层结点的多少，使用乒乓算法将结点最多的数保留下来即宽度 
{
	LinkQueue Q1,Q2;
	InitQueue(Q1);
	InitQueue(Q2);
	int num,max=0,d;
	if(!T)
	{
		return 0;
	}
	EnQueue(Q1,T);
	d=Height(T);
	BiTree t;
	for(int i=0;i<d;i++)
	{
		num=0;
		if(!EmptyQueue(Q1)&&EmptyQueue(Q2))
			while(!EmptyQueue(Q1))
			{
				DeQueue(Q1,t);
				num++;
				if(t->lchild)
					EnQueue(Q2,t->lchild);
				if(t->rchild)
					EnQueue(Q2,t->rchild);
			}
		else
		{
			if(!EmptyQueue(Q2)&&EmptyQueue(Q1))
				while(!EmptyQueue(Q2))
				{
					DeQueue(Q2,t);
					num++;
					if(t->lchild)
						EnQueue(Q1,t->lchild);
					if(t->rchild)
						EnQueue(Q1,t->rchild);
				}
		}
		if(num>max)
			max=num;
	}
	return max;
}
Status InOrder(BiTree T, LinkQueue &Q)//得到中序序列 
{
	if(T)
	{
		if(InOrder(T->lchild,Q))
			if(EnQueue(Q,T))
				if(InOrder(T->rchild,Q))
					return OK;
		else
			return ERROR;
	}
	return OK;
}
Status IsBiSortTree(BiTree &T)//通过判断树的中序序列来判断是否为二叉排序树 
{
	if(!T)
		return OK;
	LinkQueue Q;
	InitQueue(Q);
	InOrder(T,Q);
	BiTree t;
	Elem temp;
	DeQueue(Q,t);
	temp=t->data;
	while(!EmptyQueue(Q))
	{
		DeQueue(Q,t);
		if(temp<t->data)
			temp=t->data;
		else
			return ERROR;
	}
	return OK;
}
