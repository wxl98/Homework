#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXVEX 100/*��󶥵���*/
typedef float VRType;/*���ϵ�Ȩֵ���� */
typedef int VertexType;/*��������*/
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
}Plan;//����������ܺ�·��
Status CreateGraph(MGraph **G)
{
	FILE *fp;
	char filename[81];
	cout<<"��������������������Ϣ���ļ�����"<<endl;
	cin>>filename;
	fp=fopen(filename,"r");
	if(!fp)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(ERROR);
	}
	
	int n,ni,xi,yi;//��¼�����Ϣ
	int i,j,k_1,l_1,k_2,l_2;
	int Position[101][101];//ģ�������ڵ�ƽ��λ��
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
	for(i=0;i<(*G)->vexnum;i++)//����ͼ
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
	for(i=0;i<11;i++)//������۵����С�ڵ���10�Ľ�����۵���ͨ����Ȩֵ��Ϊ����֮��ľ��롣
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
	for(i=0;i<(*G)->vexnum;i++)//������С�ڵ���10�Ľ��������ͨ����Ȩֵ��Ϊ����֮��ľ��롣�Ӷ�����һ��������
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
	int num=0;//��¼�޷�ʵ�����紫��Ľ�����
	for(i=0;i<(*G)->vexnum;i++)
	{
		for(j=0;j<(*G)->vexnum;j++)
		{
			if((*G)->arcs[i][j].w!=INFINITY)
				break;
		}
		if(j>=(*G)->vexnum)
		{
			cout<<(*G)->vexs[i]<<"�Ž���޷�ʵ�����紫��."<<endl;
            num++;
		}
	}
	if(num==0)
		cout<<"���н�����ʵ�����紫�䡣"<<endl;
/*    cout<<"��ǰ���ֲ����£�"<<endl;
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
Status ShortestTimePath(MGraph G)//����FLOYD�㷨���ÿ���㵽��۵�����·����Ϊ���ʱ�䡣
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
	cout<<"�����뵥λ����Ĵ���ʱ��t:"<<endl;
	cin>>t;
	for(i=1;i<G.vexnum;i++)
	{
		if(D[i][0]!=INFINITY)
		{
			cout<<"��"<<i<<"�Ž�㵽��۵����ʱ��Ϊ:"<<t*D[i][0]<<"s."<<endl;
			cout<<"·�����Ϊ:"<<endl;
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
void MinEnergyComsuption(MGraph &MG,VertexType u)//��PRIM�㷨����С��������Ϊ���ٺ���·��
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
	cout<<"�����뵥λ����ƽ���Ĵ����ܺ�:"<<endl;
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
	cout<<"ƽ����С�ܺ�Ϊ:"<<min_energy<<endl;
	cout<<"��������"<<position-1<<"�����ӷ�ʽ��"<<endl;
	for(int i=0;i<position;i++)
	{
		if(i!=position-1)
			cout<<"���"<<s[i].i<<"����"<<s[i].j<<"��"<<endl;
		else
			cout<<"���"<<s[i].i<<"����"<<s[i].j<<"��"<<endl;
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
				cout<<"�� ";
		}
		cout<<endl;
	}
	return OK;
}
