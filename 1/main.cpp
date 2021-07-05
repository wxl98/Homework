#include"Shop.h"
int main()
{
	LinkList Shop;
	DuLinkList Du_L;
	FILE *fp,*f_w;
	int n,k,t;//用于操作判断
	int num; 
	char filename[30],Goods_name[30];
	printf("please input the filename:\n");
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("cannot open file!\n");
		exit(ERROR);
	}
	if(InitList_S(Shop,fp))
	{
		printf("Data Reading Success!\n");
	}
	printf("请按相应按键进行操作:\n"); 
	printf("1:店铺管理 2:查询商品 3:购买商品 0:退出程序\n");
	scanf("%d",&n);
	while(n!=0)
	{
		if(n==1)
		{
			printf("1:增加商铺 2:删除店铺 3:更改商品 4:查看店铺\n");
			scanf("%d",&k);
			if(k==1)
			{
				Insert_S(Shop);
			}
			else if(k==2)
			{
				printf("请输入你要删除的店铺编号：\n");
				scanf("%d",&num);
				Delete_S(Shop,num);
			}
			else if(k==3)
			{
				printf("请输入店铺编号:\n");
				scanf("%d",&num);
				Shop_Find(Shop,num);
				printf("1:增加商品 2:删除商品 3:修改商品价格\n");
				scanf("%d",&t);
				switch(t){
					case 1:Goods_Add(Shop,num);break;
					case 2:Goods_Del(Shop,num);break;
					case 3:Goods_Revise(Shop,num);break;
					default:printf("输入错误操作指令.\n");
				}
			}
			else if(k==4)
			{
				printf("1:查看所有店铺 2:查看单个\n");
				scanf("%d",&t);
				if(t==1)
				{
					Shop_Traverse(Shop);
				}
				else if(t==2)
				{
					printf("请输入店铺编号:\n");
					scanf("%d",&num);
					PrintGoods(Shop,num);
				}
				else
				{
					printf("输入错误操作指令.\n");
				}
			}
			else
			{
				printf("输入错误操作指令.\n");
			}
		}
		else if(n==2)
		{
			printf("请输入要查询商品名称:\n");
			scanf("%s",Goods_name);
			InitList_Du(Du_L,Shop,Goods_name);
			Traverse_Du(Du_L);
			Destroy_Du(Du_L);
		}
		else if(n==3)
		{
			printf("请输入店铺编号:\n");
			scanf("%d",&num);
			Goods_Purchase(Shop,num);
		}
		else
		{
			printf("输入错误操作指令.\n");
		}
		printf("1:店铺管理 2:查询商品 3:购买商品 0:退出程序\n");
		scanf("%d",&n);
	}
	f_w=fopen(filename,"w");
	if(!f_w)
	{
		printf("file revise failed!\n");
		exit(ERROR);
	}
	Destroy_S(Shop,f_w);
	return 0;
}
