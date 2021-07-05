#include"WSN.h"
int main()
{
	MGraph *G=NULL;
	int select;
	cout<<"请输入相应按键进行操作：\n";
	cout<<"1:创建结点信息，排除无法实现传输的结点。\n2:输出每个结点到汇聚点的最短时间通道。"<<endl;
	cout<<"3:输出整个网络到汇聚点的平均能耗最小网络结构。\n0:结束程序"<<endl;
	cin>>select;
	while(select!=0)
	{
		if(select==1)
		{
			if(G)
				free(G);
			CreateGraph(&G);
			cout<<endl;
		}
		else if(select==2)
		{
			if(G)
				ShortestTimePath(*G);
   			else
				cout<<"请先创建结点信息。"<<endl;
			cout<<endl;
		}
		else if(select==3)
		{
			if(G)
				MinEnergyComsuption(*G,0);
			else
				cout<<"请先创建结点信息。"<<endl;
			cout<<endl;
		}
		cout<<"1:创建结点信息，排除无法实现传输的结点。\n2:输出每个结点到汇聚点的最短时间通道。"<<endl;
		cout<<"3:输出整个网络到汇聚点的平均能耗最小网络结构。\n0:结束程序"<<endl;
		cin>>select;
	}
	return 0;
}
