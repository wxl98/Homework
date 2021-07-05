#include"Shop.h"
int main()
{
	LinkList Shop;
	DuLinkList Du_L;
	FILE *fp,*f_w;
	int n,k,t;//���ڲ����ж�
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
	printf("�밴��Ӧ�������в���:\n"); 
	printf("1:���̹��� 2:��ѯ��Ʒ 3:������Ʒ 0:�˳�����\n");
	scanf("%d",&n);
	while(n!=0)
	{
		if(n==1)
		{
			printf("1:�������� 2:ɾ������ 3:������Ʒ 4:�鿴����\n");
			scanf("%d",&k);
			if(k==1)
			{
				Insert_S(Shop);
			}
			else if(k==2)
			{
				printf("��������Ҫɾ���ĵ��̱�ţ�\n");
				scanf("%d",&num);
				Delete_S(Shop,num);
			}
			else if(k==3)
			{
				printf("��������̱��:\n");
				scanf("%d",&num);
				Shop_Find(Shop,num);
				printf("1:������Ʒ 2:ɾ����Ʒ 3:�޸���Ʒ�۸�\n");
				scanf("%d",&t);
				switch(t){
					case 1:Goods_Add(Shop,num);break;
					case 2:Goods_Del(Shop,num);break;
					case 3:Goods_Revise(Shop,num);break;
					default:printf("����������ָ��.\n");
				}
			}
			else if(k==4)
			{
				printf("1:�鿴���е��� 2:�鿴����\n");
				scanf("%d",&t);
				if(t==1)
				{
					Shop_Traverse(Shop);
				}
				else if(t==2)
				{
					printf("��������̱��:\n");
					scanf("%d",&num);
					PrintGoods(Shop,num);
				}
				else
				{
					printf("����������ָ��.\n");
				}
			}
			else
			{
				printf("����������ָ��.\n");
			}
		}
		else if(n==2)
		{
			printf("������Ҫ��ѯ��Ʒ����:\n");
			scanf("%s",Goods_name);
			InitList_Du(Du_L,Shop,Goods_name);
			Traverse_Du(Du_L);
			Destroy_Du(Du_L);
		}
		else if(n==3)
		{
			printf("��������̱��:\n");
			scanf("%d",&num);
			Goods_Purchase(Shop,num);
		}
		else
		{
			printf("����������ָ��.\n");
		}
		printf("1:���̹��� 2:��ѯ��Ʒ 3:������Ʒ 0:�˳�����\n");
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
