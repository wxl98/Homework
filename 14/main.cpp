#include"LLK.h" 
int main()  
{  
    cout << "-----------------------������-------------------------" << endl;  
    cout << "Ȼ��ÿ������4����������Ҫ�����������ӵ���������������." << endl;  
    cout << "------------------------------------------------------" << endl;  
    m=10,n=20;
    cout << endl;
    sum=m*n;
    Creat();//��ʼ����Ϸ��ͼ 
    cout<<"��Ϸ������ʼ��"<<endl;
    system("pause");
    cout<<"Map has created!"<<endl<<endl;
	Print();
	while(1)
	{
		if(sum==0)
		{
			cout<<"������������ϲͨ����!" << endl;
			break;  //ֱ��������ͼȫ����������Ϸ���� 
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
	system("pause");  //��Ϸ��������ͣ 
	return 0;
}
