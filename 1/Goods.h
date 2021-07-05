#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW -2
#define INFEASIBLE -1
#define ERROR 0
#define OK 1
typedef int Status;
typedef struct LNode_G{
	char name[30];
	float price;
	int sale_volume;
	struct LNode_G *next;
}LNode_G,*ListGoods;

Status InitList_G(ListGoods &L,FILE *f)
{
	L=(LNode_G*)malloc(sizeof(LNode_G));
	if(!L)
		exit(OVERFLOW);
	L->next=NULL;
	LNode_G *q=L;
	while(fgetc(f)!='\n')//文件中没个店铺之间的数据用换行隔开
	{
		fseek(f,-1,1);//读到的不是结束标志所以退格 
		LNode_G *p=(LNode_G*)malloc(sizeof(LNode_G));
		fscanf(f,"%s%f%d",p->name,&(p->price),&(p->sale_volume));
		if(!p)
			exit(OVERFLOW);
		q->next=p;
		q=q->next;
	}
	q->next=NULL;
	return OK;
}

Status InitList_G_Put(ListGoods &L,int n)
{
	L=(LNode_G*)malloc(sizeof(LNode_G));
	if(!L)
		exit(OVERFLOW);
	L->next=NULL;
	LNode_G *q=L;
	for(int i=0; i<n; i++)
	{
		LNode_G *p=(LNode_G*)malloc(sizeof(LNode_G));
		if(!p)
			exit(OVERFLOW);
		printf("please input the Goods' name and price\n");
		scanf("%s%f",p->name,&p->price);
		p->sale_volume=0;
		q->next=p;
		q=q->next;
	}
	q->next=NULL;
	return OK;
}

Status Destroy_G(ListGoods &L,FILE *f)
{
	LNode_G *p=L->next,*q=p;
	while(p->next)
	{
		fprintf(f,"%s %.2f %d",p->name,p->price,p->sale_volume);
		p=p->next;
		free(q);
		q=p;
		fputc(' ',f);
	}
	fprintf(f,"%s %.2f %d",p->name,p->price,p->sale_volume);
	free(p);
	fputc('\n',f);
	free(L);
	return OK;
}

Status Destroy_G_S(ListGoods &L)
{
	LNode_G *p=L->next,*q=L;
	while(p)
	{
		free(q);
		q=p;
		p=p->next; 
	}
	return OK;
}
Status Insert_G(ListGoods &L)
{
	LNode_G *p=L->next,*q;
	q=(LNode_G*)malloc(sizeof(LNode_G));
	if(!q)
		exit(OVERFLOW);
	printf("please enter the information of the goods(name and price):\n");
	scanf("%s%f",q->name,&q->price);
	q->sale_volume=0;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=q;
	q->next=NULL;
	return OK;
}

Status Delete_G(ListGoods &L, char *n)
{
	LNode_G *p=L->next,*q=L;
	while(p!=NULL && strcmp(p->name,n)!=0)
	{
		q=p;
		p=p->next;
	}
	if(!p)
	{
		printf("Goods is not exist!\n");
		return ERROR;
	}
	q->next=p->next;
	free(p);
	printf("Delete success!\n");
	return OK;
}

Status Price_revise(ListGoods &L, char *n)
{
	LNode_G *p=L->next;
	while(p!=NULL && strcmp(p->name,n)!=0)
	{
		p=p->next;
	}
	if(!p)
	{
		printf("Goods is not exist!\n");
		return ERROR;
	}
	printf("enter the price you revise:\n");
	scanf("%f",&p->price);
	printf("价格修改成功！\n");
	return OK;
}

Status Purchase(ListGoods &L, char *n)
{
	LNode_G *p=L->next,*q=L;
	while(p!=NULL && strcmp(p->name,n)!=0)
	{
		q=p;
		p=p->next;
	}
	if(!p)
	{
		printf("Goods is not exist!\n");
		return ERROR;
	}
	q->next=p->next;
	printf("Buy success!\n");
	p->sale_volume++;
	q=L;
	while(q->next!=NULL && q->next->sale_volume>p->sale_volume)
	{
		q=q->next;
	}
	p->next=q->next;
	q->next=p;
	return OK;
}

Status Goods_Traverse(ListGoods L)
{
	LNode_G *p=L->next;
	while(p)
	{
		printf("商品名：%s 价格：%.2f 销量：%d\n",p->name,p->price,p->sale_volume);
		p=p->next;
	}
	return OK;
}
