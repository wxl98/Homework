#include<iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
struct data{
	int x;
	int y;//x,y��¼��ǰλ����Ϣ 
	int dir;//��¼�ƶ��ķ��� 
	int turn;//��¼ת�������ֱ������ 
	bool operator < (const data &c)const//������������ڱȽ���������Ԫ��
	{
		return c.turn<turn;
	}
};
priority_queue<data> q;//���ö��� 
data temp,temp2;//���������߹����еĲ��� 
int tempx,tempy,tempdir,tempturn; 
int m,n,sum,x1,x2,yy1,y2;//m,nΪ��ͼ�ߴ磬sumΪͼ�������� 
int map[11][21];
int direct[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//�ĸ����� 
bool already[11][21];//���ڱ�����߹���·�� 
bool Judge()//�ж��Ƿ�ǰλ�ô���ͼ�� 
{
	if(map[tempx][tempy]!=0)
		return false;
	if(already[tempx][tempy])
		return false;
	return true;
}
void Push()//����Ѿ�������ͼ�� 
{
	temp2.x=tempx;
	temp2.y=tempy;
	temp2.dir=tempdir;
	temp2.turn=tempturn;
	q.push(temp2);
	already[tempx][tempy]=true;
}
bool Linking()//�ж��Ƿ��ܹ�����ͼ��
{
	if(x1<=0 || x2<=0 || yy1<=0 || y2<=0 || x1>=m+1 || yy1>=n+1 || x2>=m+1 || y2>=n+1)//�����λ�ò��ڷ�Χ�� 
		return false;
	if(map[x1][yy1]==0 || map[x2][y2]==0)//�����λ��ͼ���ѱ���� 
		return false;
	if(map[x1][yy1]!=map[x2][y2])//��Ҫ���ӵ�����ͼ��ͬ 
		return false;
	temp.x=x1;
	temp.y=yy1;
	temp.dir=9999;//��ʼ���� 
	temp.turn=-1;//��ʼ��ʾδ����ת�� 
	while(!q.empty())//��ն���
		q.pop(); 
	memset(already,false,sizeof(already));//���·����� 
	q.push(temp); 
	already[x1][yy1]=true;
	while (!q.empty())
	{
		temp=q.top();
		for(int i=0;i<=3;i++)//�ĸ�����һһ�ƶ����ܷ�������ֱ�������� 
		{
			tempx=temp.x+direct[i][0];
			tempy=temp.y+direct[i][1];
			tempdir=i;
			if(tempx<0 || tempy<0 || tempx>m+1 || tempy>n+1) 
				continue;
			if(temp.dir==9999 || (temp.dir+i)%2==1)//��һ���ƶ�������һ��ֱ�߻���ÿתһ�η����ת���һ 
				tempturn=temp.turn+1;
            else
				tempturn=temp.turn;
            if(tempturn>=3)//��������ֱ�ߣ��޷����� 
				continue;
            if(tempx==x2 && tempy==y2)//�ɳɹ����� 
				return true;
            if(!Judge())//·;�м���ͼ���޷�ͨ�� 
				continue;
            Push();
        }
        q.pop();
    }
    return false;
}
double Random(double start, double end)//���������������Χ�ڵ�����������ַ�
{
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
bool Isexist(int a[],int x)
{
	for(int i=0;i<10;i++)
	{
		if(x==a[i])
			return true;
	}
	return false;
}
void Creat()//��ʼ����ͼ
{
	int t=0,a,i,j;
	int k,l=0;
	int Is[10]={0};//��������10����ͬͼ�� 
	srand(time(0));
	memset(map,0,sizeof(map));
	while(t!=sum&&l<10)
	{
		a=(int)Random(0,26)+1;
		if(Isexist(Is,a))//��֤10������ͬ��ͼ����������ɵ�ͼ���������ٴ���� 
			continue;
		Is[l]=a; 
		l++;//���ڼ�¼�Ѿ�������ͼ������ 
		while(1)
		{
			if(l==10)//���һ��������������ͼ����ȥ�����ɵ�����ͼ������ 
			{
				k=sum-t;
				break;
			}
			k=(int)Random(2,30);
			if(k%2==0&&(k+2*(10-l)+t)<=sum)//��֤ÿ��ͼ������Ϊż����������������2 
				break;
		}
		for(int l=1;l<=k;l++)
		{
			while(1)
			{
				i=(int)Random(0,m)+1;
				j=(int)Random(0,n)+1;
				if(map[i][j]==0)
				{
					map[i][j]=a;
					break;
				}
			}
		}
		t+=k;
	}
}
void Print()//��ӡ����
{
	char c;
	cout<<"  ";
	for(int i=1;i<=n;i++)
	cout<<i%10;
	cout<<endl<<"  ";
	for(int i=1;i<=n;i++)
		cout << "-";
	cout<<endl;
	for(int i=1;i<=m;i++)
	{
		cout<<i%10<< "|";
		for(int j=1;j<=n;j++)
		{
			if(map[i][j]!=0)
			{
				c=map[i][j]-1+'a';
				cout<<c;
			}
			else
				cout<<" ";
		}
		cout<<"|"<<endl;
	}
	cout<<"  ";
	for(int i=1;i<=n;i++)
		cout<<"-";
    cout << endl;
}
void Dealing()//����ÿ�ε����Ӻ��� 
{  
	system("cls");
	if(Linking())
	{
		map[x1][yy1]=map[x2][y2]=0;  
		sum-=2;  
		if(sum!=0)  
		{
			cout<<"���!��������ͣ�"<<endl<<endl;
			Print();
		}
	}
	else
	{
		cout<<"�ⲻ����Ŷ����������!"<<endl<<endl;
		Print();
	}
}
