#include"Goods.h"
typedef struct LNode_S{
	int num;
	char name[30];
	int credit;
	ListGoods Goods;
	struct LNode_S *next;
}LNode_S,*ListShops;
typedef struct{
	ListShops head,rear;
	int len;
}LinkList;
typedef struct DuLNode{
	int num;
	char name[30];
	int credit;
	LNode_G Goods;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode,*DuLinkList;

Status InitList_S(LinkList &L, FILE *f)
{
	L.head=(LNode_S*)malloc(sizeof(LNode_S));
	if(!L.head)
		exit(OVERFLOW);
	if(!feof(f))
	{
		fscanf(f,"%d %s %d",&(L.head->num),L.head->name,&(L.head->credit));
		InitList_G(L.head->Goods,f);
		L.len=1;
	}
	LNode_S *q=L.head;
	while(fgetc(f)!=EOF)
	{
		fseek(f,-1,1);
		LNode_S *p=(LNode_S*)malloc(sizeof(LNode_S));
		fscanf(f,"%d %s %d",&(p->num),p->name,&(p->credit));
		InitList_G(p->Goods,f);
		q->next=p;
		q=q->next;
		L.len++;
		if(feof(f))
			break;
	}
	q->next=NULL;
	L.rear=q;
	fclose(f);
	return OK;
}

Status Destroy_S(LinkList &L, FILE *f)
{
	LNode_S *p=L.head,*q=p;
	while(p)
	{
		fprintf(f,"%d %s %d",p->num,p->name,p->credit);
		fputc(' ',f);
		Destroy_G(p->Goods,f);
		q=p;
		p=p->next;
		free(q);
	}
	L.rear=L.head=NULL;
	fclose(f);
	return OK;
}

Status Insert_S(LinkList &L)
{
	LNode_S *p;
	int n;
	p=(LNode_S*)malloc(sizeof(LNode_S));
	printf("please input the information of the new Shop:\n");
	printf("name creditworthiness\n");
	scanf("%s%d",p->name,&(p->credit));
	n=L.rear->num;
	p->num=n+1;
	p->next=L.rear->next;
	L.rear->next=p;
	L.rear=p;
	printf("input the mount of the Goods:\n");
	scanf("%d",&n);
	InitList_G_Put(p->Goods,n);
	printf("增加成功！\n");
	L.len++;
	return OK;
}

Status Goods_Add(LinkList &L, int n)
{
	LNode_S *p=L.head;
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
	Insert_G(p->Goods);
	printf("添加成功！\n");
	return OK;
}

Status Goods_Del(LinkList &L, int n)
{
	LNode_S *p=L.head;
	char name[30];
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
/*	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);*/
	printf("请输入你要删除的商品名称:\n");
	scanf("%s",name);
	Delete_G(p->Goods,name);
	return OK;
}

Status Shop_Find(LinkList &L,int n)
{
	LNode_S *p=L.head;
	char name[30];
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);
	return OK;
}

Status Goods_Revise(LinkList &L, int n)
{
	LNode_S *p=L.head;
	char name[30];
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
/*	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);*/
	printf("请输入你要修改价格的商品名称:\n");
	scanf("%s",name);
	Price_revise(p->Goods,name);
	return OK;
}

Status Goods_Purchase(LinkList &L, int n)
{
	LNode_S *p=L.head;
	char name[30];
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);
	printf("请输入你要购买的商品名称:\n");
	scanf("%s",name);
	Purchase(p->Goods,name);
	return OK;
}

Status PrintGoods(LinkList &L, int n)
{
	LNode_S *p=L.head;
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		p=p->next;
	}
	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);
	return OK;
}

Status Delete_S(LinkList &L, int n)
{
	LNode_S *p=L.head,*q=p;
	if(n>L.len||n<=0)
	{
		printf("The Shop is not exist!\n");
		return ERROR;
	}
	while(p->num!=n)
	{
		q=p;
		p=p->next;
	}
	printf("删除店铺信息：\n编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);
	q->next=p->next;
	q=p;
	p=p->next;
	while(p!=NULL)
	{
		p->num--;
		p=p->next;
	}
	Destroy_G_S(q->Goods);
	free(q);
	printf("Delete success!\n");
	L.len--;
	return OK;
}

Status Shop_Traverse(LinkList L)
{
	LNode_S *p=L.head;
	while(p!=L.rear)
	{
		printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
		printf("商品：\n"); 
		Goods_Traverse(p->Goods);
		printf("\n"); 
		p=p->next;
	}
	printf("编号：%d 店名：%s 信誉度：%d\n",p->num,p->name,p->credit);
	printf("商品：\n"); 
	Goods_Traverse(p->Goods);
	printf("\n"); 
	return OK;
}

LNode_G* Locate(LNode_S &L, char *n)
{
	LNode_G *p=L.Goods->next;
	while(p!=NULL)
	{
		if(strcmp(p->name,n)==0)
		{
			return p;
		}
		p=p->next;
	}
	return NULL;
}

Status Sort_Du(DuLinkList &L)
{
	if(L==NULL)
	{
		return ERROR;
	}
	DuLNode *p=L->next,*p1=L,*q=L;
	while(p!=L)
	{
		if(p->Goods.sale_volume > p1->Goods.sale_volume)
		{
			p->prior->next=p->next;
			p->next->prior=p->prior;
			while(q!=p1&&q->Goods.sale_volume > p->Goods.sale_volume)
			{
				q=q->next;
			}
			p->prior=q->prior;
			q->prior->next=p;
			q->prior=p;
			p->next=q;
			if(p1==L||q==L)
			{
				L=p;
				p1=p;
				p=p1->next;
			}
			q=L;
			p=p1->next;
		}
		else
		{
			p1=p;
			p=p->next;
		}
	}
	return OK;
}

Status Traverse_Du(DuLinkList &L)
{
	if(L==NULL)
	{
		printf("找不到该商品！\n");
		return ERROR;
	}
	DuLNode *p=L;
	while(p->next!=L)
	{
		printf("编号：%d 店名：%s 信誉度：%d\n商品名：%s 价格：%.2f 销量：%d\n",p->num,p->name,p->credit,p->Goods.name,p->Goods.price,p->Goods.sale_volume);
		p=p->next;
	}
	printf("编号：%d 店名：%s 信誉度：%d\n商品名：%s 价格：%.2f 销量：%d\n",p->num,p->name,p->credit,p->Goods.name,p->Goods.price,p->Goods.sale_volume);
	return OK;
}

Status InitList_Du(DuLinkList &Du_L, LinkList &L,char *s)
{
	DuLNode *q1;
	LNode_S *p=L.head;
	LNode_G *temp;
	int n=0;
	Du_L=NULL;
	while(p!=NULL)
	{
		if(temp=Locate(*p,s))
		{
			if(n==0)
			{
				DuLNode *q=(DuLNode*)malloc(sizeof(DuLNode));
				q->credit=p->credit;
				strcpy(q->name,p->name);
				q->num=p->num;
				strcpy((q->Goods.name),temp->name);
				q->Goods.price=temp->price;
				q->Goods.sale_volume=temp->sale_volume;
				q->next=q->prior=NULL;
				q1=q;
				Du_L=q;
				n++;
			}
			else
			{
				DuLNode *q=(DuLNode*)malloc(sizeof(DuLNode));
				q->credit=p->credit;
				strcpy(q->name,p->name);
				q->num=p->num;
				strcpy((q->Goods.name),temp->name);
				q->Goods.price=temp->price;
				q->Goods.sale_volume=temp->sale_volume;
				q1->next=q;
				q->prior=q1;
				q1=q;
			}
		}
		p=p->next;
	}
	if(!Du_L)
		return ERROR;
	q1->next=Du_L;
	Du_L->prior=q1;
	Sort_Du(Du_L);
	return OK;
}

Status Destroy_Du(DuLinkList &L)
{
	if(L==NULL)
		return ERROR;
	DuLNode *p=L->next,*q;
	while(p!=L)
	{
		q=p;
		p=p->next;
		free(q);
	}
	free(L);
	return OK;
}
