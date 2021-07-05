#include"BusRoute.h"
int main()
{
	ALGraph G;
	if(!CreateALGraph(G))
		return 0;
	cout<<G.vexnum<<" "<<G.arcnum<<endl;
	int select;
	cout<<"请按相应按键进行操作：\n"; 
	cout<<"1:查询公交车路线\n0:结束程序"<<endl;
	cin>>select;
	while(select!=0)
	{
		if(select==1)
		{
			cout<<"请输入起始车站名和终点车站名："<<endl;
			string s,t;
			InitStack(S);
			cin>>s>>t;
			int s1,t1;
			s1=Locate(G,s);
			t1=Locate(G,t);
			while(s1<0||t1<0)
			{
				cout<<"车站名输入错误，请重新输入\n"; 
				cin>>s>>t;
				s1=Locate(G,s);
				t1=Locate(G,t);
			}
			AllPath_DFSTraverse(G,s1,t1);
			DestroyStack(S);
		}
		else
		{
			cout<<"操作指令输入错误请重新输入\n";
		}
		cout<<"是否继续查询？(1:继续查找0:结束程序)"<<endl;
		cin>>select;
	}
	return 0;
}
