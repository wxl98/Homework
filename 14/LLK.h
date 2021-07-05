#include<iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
struct data{
	int x;
	int y;//x,y记录当前位置信息 
	int dir;//记录移动的方向 
	int turn;//记录转弯次数即直线数量 
	bool operator < (const data &c)const//重载运算符用于比较两个基础元素
	{
		return c.turn<turn;
	}
};
priority_queue<data> q;//调用队列 
data temp,temp2;//用于在连线过程中的查找 
int tempx,tempy,tempdir,tempturn; 
int m,n,sum,x1,x2,yy1,y2;//m,n为地图尺寸，sum为图像总数量 
int map[11][21];
int direct[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//四个方向 
bool already[11][21];//用于标记已走过的路劲 
bool Judge()//判断是否当前位置存在图像 
{
	if(map[tempx][tempy]!=0)
		return false;
	if(already[tempx][tempy])
		return false;
	return true;
}
void Push()//标记已经消除的图像 
{
	temp2.x=tempx;
	temp2.y=tempy;
	temp2.dir=tempdir;
	temp2.turn=tempturn;
	q.push(temp2);
	already[tempx][tempy]=true;
}
bool Linking()//判断是否能够消除图像
{
	if(x1<=0 || x2<=0 || yy1<=0 || y2<=0 || x1>=m+1 || yy1>=n+1 || x2>=m+1 || y2>=n+1)//输入的位置不在范围内 
		return false;
	if(map[x1][yy1]==0 || map[x2][y2]==0)//输入的位置图像已被清除 
		return false;
	if(map[x1][yy1]!=map[x2][y2])//所要连接的两个图像不同 
		return false;
	temp.x=x1;
	temp.y=yy1;
	temp.dir=9999;//初始方向 
	temp.turn=-1;//初始表示未发生转弯 
	while(!q.empty())//清空队列
		q.pop(); 
	memset(already,false,sizeof(already));//清空路径情况 
	q.push(temp); 
	already[x1][yy1]=true;
	while (!q.empty())
	{
		temp=q.top();
		for(int i=0;i<=3;i++)//四个方向一一移动看能否在三条直线内连接 
		{
			tempx=temp.x+direct[i][0];
			tempy=temp.y+direct[i][1];
			tempdir=i;
			if(tempx<0 || tempy<0 || tempx>m+1 || tempy>n+1) 
				continue;
			if(temp.dir==9999 || (temp.dir+i)%2==1)//第一次移动产生第一条直线或者每转一次方向就转弯加一 
				tempturn=temp.turn+1;
            else
				tempturn=temp.turn;
            if(tempturn>=3)//大于三条直线，无法消除 
				continue;
            if(tempx==x2 && tempy==y2)//可成功消除 
				return true;
            if(!Judge())//路途中间有图像无法通过 
				continue;
            Push();
        }
        q.pop();
    }
    return false;
}
double Random(double start, double end)//随机函数，产生范围内的随机数产生字符
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
void Creat()//初始化地图
{
	int t=0,a,i,j;
	int k,l=0;
	int Is[10]={0};//用于生成10个不同图案 
	srand(time(0));
	memset(map,0,sizeof(map));
	while(t!=sum&&l<10)
	{
		a=(int)Random(0,26)+1;
		if(Isexist(Is,a))//保证10个不相同的图案，如果生成的图案已有则再次随机 
			continue;
		Is[l]=a; 
		l++;//用于记录已经产生的图案种类 
		while(1)
		{
			if(l==10)//最后一次生成数量由总图案减去已生成的所有图案数量 
			{
				k=sum-t;
				break;
			}
			k=(int)Random(2,30);
			if(k%2==0&&(k+2*(10-l)+t)<=sum)//保证每个图案个数为偶数并且数量都大于2 
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
void Print()//打印版面
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
void Dealing()//处理每次的连接函数 
{  
	system("cls");
	if(Linking())
	{
		map[x1][yy1]=map[x2][y2]=0;  
		sum-=2;  
		if(sum!=0)  
		{
			cout<<"真棒!请继续加油！"<<endl<<endl;
			Print();
		}
	}
	else
	{
		cout<<"这不可以哦，请再找找!"<<endl<<endl;
		Print();
	}
}
