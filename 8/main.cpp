#include"BusRoute.h"
int main()
{
	ALGraph G;
	if(!CreateALGraph(G))
		return 0;
	cout<<G.vexnum<<" "<<G.arcnum<<endl;
	int select;
	cout<<"�밴��Ӧ�������в�����\n"; 
	cout<<"1:��ѯ������·��\n0:��������"<<endl;
	cin>>select;
	while(select!=0)
	{
		if(select==1)
		{
			cout<<"��������ʼ��վ�����յ㳵վ����"<<endl;
			string s,t;
			InitStack(S);
			cin>>s>>t;
			int s1,t1;
			s1=Locate(G,s);
			t1=Locate(G,t);
			while(s1<0||t1<0)
			{
				cout<<"��վ�������������������\n"; 
				cin>>s>>t;
				s1=Locate(G,s);
				t1=Locate(G,t);
			}
			AllPath_DFSTraverse(G,s1,t1);
			DestroyStack(S);
		}
		else
		{
			cout<<"����ָ�������������������\n";
		}
		cout<<"�Ƿ������ѯ��(1:��������0:��������)"<<endl;
		cin>>select;
	}
	return 0;
}
