#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXVEX 100/*最大顶点数*/
typedef float VRType;/*边上的权值类型 */
typedef int VertexType;/*顶点类型*/
typedef int Status;
typedef struct AreCell{
	VRType w;
}ArcCell,AdjMatrix[MAXVEX][MAXVEX];
typedef struct{
    VertexType vexs[MAXVEX];
    AdjMatrix arcs;
    int vexnum,arcnum;
}MGraph;
typedef struct {
	VertexType adjvex;
	VRType lowcost;
}money,closedge[MAXVEX];
typedef struct{
	VertexType i;
	VertexType j;
}Plan;//用于求最低能耗路径
Status CreateGraph(MGraph **G)
{
	FILE *fp;
	char filename[81];
	cout<<"请输入包含传感器结点信息的文件名："<<endl;
	cin>>filename;
	fp=fopen(filename,"r");
	if(!fp)
	{
		cout<<"文件打开失败！"<<endl;
		exit(ERROR);
	}
	
	int n,ni,xi,yi;//记录结点信息
	int i,j,k_1,l_1,k_2,l_2;
	int Position[101][101];//模拟结点所在的平面位置
	for(i=0;i<101;i++)
	{
		for(j=0;j<101;j++)
		{
			Position[i][j]=0;
		}
	}
	fscanf(fp,"%d",&n);
	if(feof(fp))
		return ERROR;
	while(!feof(fp))
	{
		fscanf(fp,"%d%d%d",&ni,&xi,&yi);
		Position[xi][yi]=ni;
	}
	*G=(MGraph*)malloc(sizeof(MGraph));
	(*G)->vexnum=n+1;
	for(i=0;i<(*G)->vexnum;i++)//构造图
	{
		(*G)->vexs[i]=i;
	}
	(*G)->arcnum=0;
	for(i=0;i<(*G)->vexnum;i++)
	{
		for(j=0;j<(*G)->vexnum;j++)
		{
			(*G)->arcs[i][j].w=INFINITY;
		}
	}
	for(i=0;i<11;i++)//将到汇聚点距离小于等于10的结点与汇聚点连通，其权值即为他们之间的距离。
	{
		for(j=0;j<11;j++)
		{
			if(Position[i][j]!=0&&(i*i)+(j*j)<=100)
			{
				ni=Position[i][j];
				(*G)->arcs[0][ni].w=sqrt((i*i)+(j*j));
				(*G)->arcs[ni][0].w=sqrt((i*i)+(j*j));
				(*G)->arcnum++;
			}
		}
	}
	for(i=0;i<(*G)->vexnum;i++)//将距离小于等于10的结点与结点连通，其权值即为他们之间的距离。从而构成一个无向网
	{
		for(k_1=0;k_1<101;k_1++)
		{
			for(l_1=0;l_1<101;l_1++)
			{
				if(Position[k_1][l_1]==i)
				{
					break;
				}
			}
			if(Position[k_1][l_1]==i)
			{
				break;
			}
		}
		for(j=i+1;j<(*G)->vexnum;j++)
		{
			for(k_2=0;k_2<101;k_2++)
			{
				for(l_2=0;l_2<101;l_2++)
				{
					if(Position[k_2][l_2]==j)
					{
						break;
					}
				}
				if(Position[k_2][l_2]==j)
				{
					break;
				}
			}
			if((k_1-k_2)*(k_1-k_2)+(l_1-l_2)*(l_1-l_2)<=100)
			{
				(*G)->arcs[i][j].w=sqrt((k_1-k_2)*(k_1-k_2)+(l_1-l_2)*(l_1-l_2));
				(*G)->arcs[j][i].w=sqrt((k_1-k_2)*(k_1-k_2)+(l_1-l_2)*(l_1-l_2));
				(*G)->arcnum++;
			}
		}
	}
	int num=0;//记录无法实现网络传输的结点个数
	for(i=0;i<(*G)->vexnum;i++)
	{
		for(j=0;j<(*G)->vexnum;j++)
		{
			if((*G)->arcs[i][j].w!=INFINITY)
				break;
		}
		if(j>=(*G)->vexnum)
		{
			cout<<(*G)->vexs[i]<<"号结点无法实现网络传输."<<endl;
            num++;
		}
	}
	if(num==0)
		cout<<"所有结点均能实现网络传输。"<<endl;
/*    cout<<"当前结点分布如下："<<endl;
	for(i=0;i<101;i++)
	{
		for(j=0;j<101;j++)
		{
			cout<<Position[i][j];
		}
		cout<<endl;
	}*/
	fclose(fp);
	return OK;
}
Status ShortestTimePath(MGraph G)//利用FLOYD算法求出每个点到汇聚点的最短路径即为最短时间。
{
	int i,j,k;
	float D[MAXVEX][MAXVEX];
	bool Path[MAXVEX][MAXVEX][MAXVEX];
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(i!=j)
				D[i][j]=G.arcs[i][j].w;
			else
				D[i][j]=0;
			for(k=0;k<G.vexnum;k++)
			{
				Path[i][j][k]=false;
			}
			if(D[i][j]<INFINITY)
			{
				Path[i][j][i]=true;
				Path[i][j][j]=true;
			}
		}
	}
	for(k=0;k<G.vexnum;k++)
	{
		for(i=0;i<G.vexnum;i++)
		{
			for(j=0;j<G.vexnum;j++)
			{
				if(D[i][k]+D[k][j]<D[i][j]&&D[i][k]!=INFINITY&&D[k][j]!=INFINITY)
				{
					D[i][j]=D[i][k]+D[k][j];
					for(int u=0;u<G.vexnum;u++)
					{
						Path[i][j][u]=Path[i][k][u]||Path[k][j][u];
					}
				}
			}
		}
	}
	float t;
	cout<<"请输入单位距离的传输时间t:"<<endl;
	cin>>t;
	for(i=1;i<G.vexnum;i++)
	{
		if(D[i][0]!=INFINITY)
		{
			cout<<"从"<<i<<"号结点到汇聚点最短时间为:"<<t*D[i][0]<<"s."<<endl;
			cout<<"路径结点为:"<<endl;
			for(j=0;j<G.vexnum;j++)
			{
				if(Path[i][0][j])
					cout<<j<<" ";
			}
			cout<<endl<<endl;
		}
	}
	return OK;
}
int LocateVex(MGraph &G, VertexType u)
{
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.vexs[i]==u)
			return i;
	}
	return -1;
}
int Mini(int n,closedge &m)
{
	int p=0;
	float min=INFINITY;
	for(int i=0;i<n;i++)
	{
		if(m[i].lowcost<min&&m[i].lowcost!=0)
		{
			min=m[i].lowcost;
			p=i;
		}
	}
	if(p!=0)
		return p;
	else
		return -1;
}
void MinEnergyComsuption(MGraph &MG,VertexType u)//用PRIM算法求最小生成树即为最少耗能路径
{
	MGraph G;
	G.arcnum=MG.arcnum;
	G.vexnum=MG.vexnum;
	for(int i=0;i<G.vexnum;i++)
	{
		G.vexs[i]=MG.vexs[i];
		for(int h=0;h<G.vexnum;h++)
		{
			G.arcs[i][h].w=MG.arcs[i][h].w*MG.arcs[i][h].w;
		}
	}
	closedge cost;
	Plan *s=(Plan*)malloc(sizeof(Plan)*G.vexnum);
	int k=LocateVex(G,u);
	int min_energy=0,position=0;
	float en_comsuption;
	cout<<"请输入单位距离平方的传输能耗:"<<endl;
	cin>>en_comsuption;
	for(int j=0;j<G.vexnum;j++)
	{
		if(j!=k)
		{
			cost[j].adjvex=u;
			cost[j].lowcost=G.arcs[k][j].w;
		}
	}
	cost[k].lowcost=0;
	for(int i=0;i<G.vexnum;++i)
	{
		k=Mini(G.vexnum,cost);
		if(k==-1)
			break;
		min_energy+=cost[k].lowcost*en_comsuption;
		cost[k].lowcost=0;
		for(int j=0; j<G.vexnum; j++)
		{
			if(G.arcs[k][j].w<cost[j].lowcost)
			{
				cost[j].adjvex=G.vexs[k];
				cost[j].lowcost=G.arcs[k][j].w;
			}
		}
		s[position].i=cost[k].adjvex;
		s[position].j=G.vexs[k];
		position++;
	}
	cout<<"平均最小能耗为:"<<min_energy<<endl;
	cout<<"建立以下"<<position-1<<"条连接方式："<<endl;
	for(int i=0;i<position;i++)
	{
		if(i!=position-1)
			cout<<"结点"<<s[i].i<<"与结点"<<s[i].j<<"、"<<endl;
		else
			cout<<"结点"<<s[i].i<<"与结点"<<s[i].j<<"。"<<endl;
	}
	free(s);
}
Status PrintMtrix(MGraph &G)
{
		for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[i][j].w!=INFINITY)
				cout<<G.arcs[i][j].w<<" ";
			else
				cout<<"∞ ";
		}
		cout<<endl;
	}
	return OK;
}
