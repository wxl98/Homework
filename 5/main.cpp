#include"WSN.h"
int main()
{
	MGraph *G=NULL;
	int select;
	cout<<"��������Ӧ�������в�����\n";
	cout<<"1:���������Ϣ���ų��޷�ʵ�ִ���Ľ�㡣\n2:���ÿ����㵽��۵�����ʱ��ͨ����"<<endl;
	cout<<"3:����������絽��۵��ƽ���ܺ���С����ṹ��\n0:��������"<<endl;
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
				cout<<"���ȴ��������Ϣ��"<<endl;
			cout<<endl;
		}
		else if(select==3)
		{
			if(G)
				MinEnergyComsuption(*G,0);
			else
				cout<<"���ȴ��������Ϣ��"<<endl;
			cout<<endl;
		}
		cout<<"1:���������Ϣ���ų��޷�ʵ�ִ���Ľ�㡣\n2:���ÿ����㵽��۵�����ʱ��ͨ����"<<endl;
		cout<<"3:����������絽��۵��ƽ���ܺ���С����ṹ��\n0:��������"<<endl;
		cin>>select;
	}
	return 0;
}
