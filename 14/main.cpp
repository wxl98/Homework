#include"LLK.h" 
int main()  
{  
    cout << "-----------------------连连看-------------------------" << endl;  
    cout << "然后每次输入4个数，代表要消的两个格子的所在行数和列数." << endl;  
    cout << "------------------------------------------------------" << endl;  
    m=10,n=20;
    cout << endl;
    sum=m*n;
    Creat();//初始化游戏地图 
    cout<<"游戏即将开始！"<<endl;
    system("pause");
    cout<<"Map has created!"<<endl<<endl;
	Print();
	while(1)
	{
		if(sum==0)
		{
			cout<<"你真厉害，恭喜通关啦!" << endl;
			break;  //直到整个地图全部清除完成游戏结束 
		}
		cout<<"xi yi:";
		cin>> x1;
		cin>> yy1;
    	cout<<"xi yi:";
		cin>> x2;
		cin>> y2;
		cout<<endl;
		Dealing();
	}
	system("pause");  //游戏结束后暂停 
	return 0;
}
