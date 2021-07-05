#include"BiTree.h"
int main()
{
	BiTree T=NULL;
	int select;
	int Hei,num_nodes,wid;
	printf("please enter the number to operate:\n");
	printf("1:����������2:����������(�ݹ�)3:����������(�ǵݹ�)\n4:��������ĸ߶ȡ���ȡ������5:�ж��Ƿ�Ϊ����������6:��������\n");
	scanf("%d",&select);
	while(select!=6)
	{
		if(select==1)
		{
			if(T)
				DestroyBiTree(T);
			CreateBiTree_File(T);
		}
		else if(select==2)
		{
			if(!T)
				printf("���ȹ���������!\n");
			else
			{
				printf("PreOrderTraverse:\n");
				PreOrderTraverse(T,Visit);
				printf("\n");
				printf("InOrderTraverse:\n");
				InOrderTraverse(T,Visit);
				printf("\n");
				printf("PostOrderTraverse:\n");
				PostOrderTraverse(T,Visit);
				printf("\n");
				printf("LevelOrderTraverse:\n");
				LevelOrderTraverse(T,Visit);
			}
		}
		else if(select==3)
		{
			if(!T)
				printf("���ȹ���������!\n");
			else
			{
				printf("PreOrderTraverse:\n");
				PreOrderTraverse_S(T,Visit);
				printf("InOrderTraverse:\n");
				InOrderTraverse_S(T,Visit);
				printf("PostOrderTraverse:\n");
				PostOrderTraverse_S(T);
			}
		}
		else if(select==4)
		{
			if(!T)
				printf("���ȹ���������!\n");
			else
			{
				num_nodes=0;
				Hei=Height(T);
				printf("�ö������ĸ߶�Ϊ:%d\n",Hei);
				CountNodes(T,num_nodes);
				printf("�ö������Ľ����Ϊ:%d\n",num_nodes);
				wid=BiTreeWidth(T);
				printf("�ö������Ŀ��Ϊ:%d\n",wid);
			}
		}
		else if(select==5)
		{
			if(!T)
				printf("���ȹ���������!\n");
			else if(IsBiSortTree(T))
				printf("This BiTree is a SearchTree!\n");
			else
				printf("This BiTree isn't a SearchTree!\n");
		}
		printf("��ѡ��������Ĳ���:\n");
		printf("1:����������2:����������(�ݹ�)3:����������(�ǵݹ�)\n4:��������ĸ߶ȡ���ȡ������5:�ж��Ƿ�Ϊ����������6:��������\n");
		scanf("%d",&select);
	}
	return 0;
}
