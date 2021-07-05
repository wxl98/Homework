#include"BiTree.h"
int main()
{
	BiTree T=NULL;
	int select;
	int Hei,num_nodes,wid;
	printf("please enter the number to operate:\n");
	printf("1:构建二叉树2:遍历二叉树(递归)3:遍历二叉树(非递归)\n4:求二叉树的高度、宽度、结点数5:判断是否为二叉排序树6:结束程序\n");
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
				printf("请先构建二叉树!\n");
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
				printf("请先构建二叉树!\n");
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
				printf("请先构建二叉树!\n");
			else
			{
				num_nodes=0;
				Hei=Height(T);
				printf("该二叉树的高度为:%d\n",Hei);
				CountNodes(T,num_nodes);
				printf("该二叉树的结点数为:%d\n",num_nodes);
				wid=BiTreeWidth(T);
				printf("该二叉树的宽度为:%d\n",wid);
			}
		}
		else if(select==5)
		{
			if(!T)
				printf("请先构建二叉树!\n");
			else if(IsBiSortTree(T))
				printf("This BiTree is a SearchTree!\n");
			else
				printf("This BiTree isn't a SearchTree!\n");
		}
		printf("请选择接下来的操作:\n");
		printf("1:构建二叉树2:遍历二叉树(递归)3:遍历二叉树(非递归)\n4:求二叉树的高度、宽度、结点数5:判断是否为二叉排序树6:结束程序\n");
		scanf("%d",&select);
	}
	return 0;
}
