#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 100
#define MAXVEX 1000
#define MAXROU 40
typedef int Status;
typedef char* VexType;//图结构 
typedef struct InforType{
	char Route[MAXROU][5];
	int rounum;
}InforType;
typedef struct ArcNode{
	int adjvex;
	InforType route;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
	VexType Sitename;
	ArcNode *firstarc;
}VNode,AdjList[MAXVEX];
typedef struct MGraph{
	AdjList vertices;
	int vexnum;
	int arcnum;
}ALGraph;
typedef struct Record{
	int vexpostion;
	ArcNode *p;
}Record;
typedef Record ElemType;//栈定义 
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;
Status InitStack(SqStack &S)
{
	S.base=(ElemType*)malloc(STACK_INIT_SIZE*(sizeof(ElemType)));
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}
Status DestroyStack(SqStack &S)
{
	if(S.base!=NULL||S.top!=NULL)
	{
		free(S.base);
		S.base=NULL;
		S.top=NULL;
	}
	return OK;
}
int StackLength(SqStack &S)
{
	int len;
	if(S.base==NULL)
		return ERROR;
	len=S.top-S.base;
	return len;
}
Status StackEmpty(SqStack &S)
{
	if(S.base==S.top && S.base!=NULL && S.top!=NULL)
		return OK;
	else
		return ERROR;
}
Status GetTop(SqStack &S,ElemType &e)
{
	if(S.base==S.top)
		return ERROR;
	e=*(S.top-1);
	return OK;
}
Status Push(SqStack &S,ElemType e)
{
	if((S.top-S.base)>=S.stacksize)
	{
		S.base=(ElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(S.base==S.top)
		return ERROR;
	e=*--S.top;
	return OK;
}
bool IsInStack(SqStack S,ElemType x)/*判断节点是否在栈中*/
{
	if(S.base==S.top)
		return false;
	ElemType *p;
	p=S.base;
	while(p<S.top)
	{
		if((*p).vexpostion==x.vexpostion)
			return true;
		p++;
	}
	return false;
}
SqStack S;
int Shortestpath_site[MAXVEX];
int Shortestpath_route[MAXVEX];
int Locate(ALGraph &G,string n)
{
	for(int i=0;i<G.vexnum;i++)
	{
		if(strcmp(G.vertices[i].Sitename,n.c_str())==0)
			return i;
	}
	return -1;
}
int Locate_route(ArcNode cell,char *n)//在边上查找线路是否在上面 
{
	for(int i=0;i<cell.route.rounum;i++)
	{
		if(strcmp(cell.route.Route[i],n)==0)
			return i;
	}
	return -1;
}
Status CreateALGraph(ALGraph &G)
{
	G.vexnum=0;
	G.arcnum=0;
	char filename[20];
	cout<<"请输入公交车站点信息的文件名:"<<endl;
	cin>>filename;
	ifstream in;
	in.open(filename);
	if(!in)
	{
		cout<<"文件打开失败！"<<endl;
		return ERROR;
	}
	string sitename,sitename1,rouname;
	int sitenum,temp,location,location1;
	while(!in.eof())
	{
		in>>rouname;
		if(in.eof())
		{
			break;
		}
		in>>sitenum;
		in>>sitename;
		location=Locate(G,sitename);
		if(location<0)
		{
			G.vertices[G.vexnum].Sitename=new char[sitename.length()+1];
			strcpy(G.vertices[G.vexnum].Sitename,sitename.c_str());
			G.vertices[G.vexnum].firstarc=NULL;
			location=G.vexnum;
			G.vexnum++;
		}
		for(int i=1;i<sitenum;i++)
		{
			in>>sitename1;
			location1=Locate(G,sitename1);
			if(location1<0)
			{
				G.vertices[G.vexnum].Sitename=new char[sitename1.length()+1];
				strcpy(G.vertices[G.vexnum].Sitename,sitename1.c_str());
				G.vertices[G.vexnum].firstarc=NULL;
				location1=G.vexnum;
				G.vexnum++;
			}
			ArcNode *p,*p1;
			if(!G.vertices[location].firstarc)//第一个站名的情况 
			{
				G.vertices[location].firstarc=new ArcNode;
				G.vertices[location].firstarc->adjvex=location1;
				G.vertices[location].firstarc->nextarc=NULL;
				strcpy((G.vertices[location].firstarc)->route.Route[0],rouname.c_str());
				G.vertices[location].firstarc->route.rounum=1;
				G.arcnum++;
			}
			else
			{
				p=G.vertices[location].firstarc;
				if(p->adjvex==location1)
				{
					temp=G.vertices[location].firstarc->route.rounum;
					strcpy(G.vertices[location].firstarc->route.Route[temp],rouname.c_str());
					G.vertices[location].firstarc->route.rounum++;
					G.arcnum++;
				}
				else
				{
					while(p->nextarc!=NULL&&p->nextarc->adjvex!=location1)
					{
						p=p->nextarc;
					}
					if(!p->nextarc)
					{
						p->nextarc=new ArcNode;
						p->nextarc->nextarc=NULL;
						p->nextarc->adjvex=location1;
						strcpy(p->nextarc->route.Route[0],rouname.c_str());
						p->nextarc->route.rounum=1;
						G.arcnum++;
					}
					else
					{
						temp=p->nextarc->route.rounum;
						strcpy(p->nextarc->route.Route[temp],rouname.c_str());
						p->nextarc->route.rounum++;
						G.arcnum++;
					}
				}
			}
			if(!G.vertices[location1].firstarc)//第二个站名的情况 
			{
				G.vertices[location1].firstarc=new ArcNode;
				G.vertices[location1].firstarc->adjvex=location;
				G.vertices[location1].firstarc->nextarc=NULL;
				strcpy(G.vertices[location1].firstarc->route.Route[0],rouname.c_str());
				G.vertices[location1].firstarc->route.rounum=1;
			}
			else
			{
				p1=G.vertices[location1].firstarc;
				if(p1->adjvex==location)
				{
					temp=G.vertices[location1].firstarc->route.rounum;
					strcpy(G.vertices[location1].firstarc->route.Route[temp],rouname.c_str());
					G.vertices[location1].firstarc->route.rounum++;
				}
				else
				{
					while(p1->nextarc!=NULL&&p1->nextarc->adjvex!=location)
					{
						p1=p1->nextarc;
					}
					if(!p1->nextarc)
					{
						p1->nextarc=new ArcNode;
						p1->nextarc->nextarc=NULL;
						p1->nextarc->adjvex=location;
						strcpy(p1->nextarc->route.Route[0],rouname.c_str());
						p1->nextarc->route.rounum=1;
					}
					else
					{
						temp=p1->nextarc->route.rounum;
						strcpy(p1->nextarc->route.Route[temp],rouname.c_str());
						p1->nextarc->route.rounum++;
					}
				}
			}
			sitename=sitename1;
			location=location1;
		}//endfor
	}//endwhile
	in.close();
	return OK;
}
char *GetRoute(ALGraph G,int i,int j)
{
	int k;
	ArcNode *p=G.vertices[i].firstarc;
	while(p->adjvex!=j)
	{
		p=p->nextarc;
	}
	for(k=0;k<p->route.rounum-1;k++)
	{
		cout<<p->route.Route[k]<<"、";
	}
	cout<<p->route.Route[k];
}
void PrintPath_rou(ALGraph G)
{
	int i=1;
	while(i<Shortestpath_route[0])
	{
		cout<<G.vertices[Shortestpath_route[i]].Sitename<<"-";
		GetRoute(G,Shortestpath_route[i],Shortestpath_route[i+1]);
		cout<<"->";
		i++;
	}
	cout<<G.vertices[Shortestpath_route[i]].Sitename;
	cout<<endl;
}
void SavePath_rou(SqStack S,int e)
{
	ElemType *p=S.base;
	Shortestpath_route[0]=StackLength(S)+1;
	for(int i=1;p<S.top;i++,p++)
	{
		Shortestpath_route[i]=p->vexpostion;
	}
	Shortestpath_route[Shortestpath_route[0]]=e;
}
void PrintPath_site(ALGraph G)
{
	int i=1;
	while(i<Shortestpath_site[0])
	{
		cout<<G.vertices[Shortestpath_site[i]].Sitename<<"-";
		GetRoute(G,Shortestpath_site[i],Shortestpath_site[i+1]);
		cout<<"->";
		i++;
	}
	cout<<G.vertices[Shortestpath_site[i]].Sitename;
	cout<<endl;
}
void SavePath_site(SqStack S,int e)
{
	ElemType *p=S.base;
	Shortestpath_site[0]=StackLength(S)+1;
	for(int i=1;p<S.top;i++,p++)
	{
		Shortestpath_site[i]=p->vexpostion;
	}
	Shortestpath_site[Shortestpath_site[0]]=e;
}
bool IsExit(char r[MAXVEX][4],char *s,int num)
{
	for(int i=0;i<num;i++)
	{
		if(strcmp(r[i],s)==0)
			return true;
	}
	return false;
}
void Countnum(int *a,char r[MAXVEX][4],char *s,int num)
{
	for(int i=0;i<num;i++)
	{
		if(strcmp(r[i],s)==0)
		{
			a[i]++;
		}
	}
}
bool Adjust(bool *m,char *s)
{
	int i;
	ElemType *q;
	bool tag=false;
	for(i=0,q=S.base;q<S.top;q++,i++)
	{
		if(m[i]==false)
			for(int j=0;j<q->p->route.rounum;j++)
			{
				if(strcmp(q->p->route.Route[j],s)==0)
				{
					m[i]=true;
					tag=true;
					break;
				}
			}
	}
	return tag;
}
bool Selectway(int *a,bool *t,bool *m,int num,char r[MAXVEX][4])//选择合适的线路 
{
	int max=0;
	int j=0;
	for(int i=0;i<num;i++)
	{
		if(t[i]==true)//先选出必经路线 
		{
			t[i]=false;
			a[i]=0;
			if(Adjust(m,r[i]))//将这条路线经过的站点之间的弧进行标记 
				return true;
		}
	}
	for(int i=0;i<num;i++)
	{
		if(a[i]>max)//次优先选出所有出现次数最多并未被选出的线路 
		{
			j=i;
			max=a[i];
		}
	}
	a[j]=0;
	if(Adjust(m,r[j]))//如果对线路状态发生改变则有效否则这条线路多余 
		return true;
	return false; 
}
bool Check(bool *m)
{
	for(int i=0;i<StackLength(S);i++)
	{
		if(m[i]==false)
		{
			return false;
		}
	}
	return true;
}
int GetRoutenum(ALGraph G)
{
	char routename[MAXVEX][4];
	int num=0,routenum=0,n;
	n=StackLength(S);
	ElemType *q=S.base;
	while(q<S.top) 
	{
		for(int i=0;i<q->p->route.rounum;i++)
		{
			if(!IsExit(routename,q->p->route.Route[i],num))//记录该条路径出现的所有公交线路和数量 
			{
				strcpy(routename[num],q->p->route.Route[i]);
				num++;
			}
		}
		q++;
	}
	int *Count=new int[num]; //用于统计每条线路出现的次数 
	bool *tag=new bool[num],*Must=new bool[n];//tag用于判断是否该公交线路是必须经过的即唯一线路可达 
	for(int j=0;j<num;j++)
	{
		Count[j]=0;
		tag[j]=false;
	}
	for(int j=0;j<n;j++)//Must记录每两个站点之间是否已经存在线路可达 
	{
		Must[j]=false;
	}
	q=S.base;
	while(q<S.top)//统计并选出必须线路 
	{
		for(int i=0;i<q->p->route.rounum;i++)
		{
			if(q->p->route.rounum==1)
			{
				for(int i=0;i<num;i++)
				{
					if(strcmp(routename[i],q->p->route.Route[i])==0)
					{
						tag[i]=true;
					}
				}
			}
			Countnum(Count,routename,q->p->route.Route[i],num);
		}
		q++;
	}
	while(!Check(Must))//查看是否每条弧都已经存在线路可达 
	{
		if(Selectway(Count,tag,Must,num,routename))//选择必进的线路或者出现次数最多的线路 
			routenum++;
	}
	free(Count);
	free(tag);
	free(Must);
	return routenum;
}
Status AllPath_DFSTraverse(ALGraph G,int s,int e)//深度优先遍历整个图找出所有通路选出其中需要的路径 
{
	int sitenum=2000;
	int rounum=2000;
	Record temp,top;
	temp.vexpostion=s;
	temp.p=G.vertices[s].firstarc;
	if(!IsInStack(S,temp))
	{
		Push(S,temp);
	}
	while(!StackEmpty(S))
	{
		GetTop(S,top);
		if(top.p==NULL)
		{
			Pop(S,top);
			if(StackEmpty(S))
				break;
			(*(S.top-1)).p=(*(S.top-1)).p->nextarc;
			continue;
		}
		temp.vexpostion=top.p->adjvex;
		temp.p=G.vertices[temp.vexpostion].firstarc;
		if(!IsInStack(S,temp))
		{
			if(temp.vexpostion==e)
			{
				int k=GetRoutenum(G);
				if(k<rounum)//选换乘最少的路径 
				{
					rounum=k;
					SavePath_rou(S,e);
				}
				if(StackLength(S)<sitenum)//选站点最少的路径 
				{
					sitenum=StackLength(S);
					SavePath_site(S,e);
				}
				(*(S.top-1)).p=(*(S.top-1)).p->nextarc;
				continue;
			}
			Push(S,temp);
		}
		else
		{
			(*(S.top-1)).p=(*(S.top-1)).p->nextarc;
		}
	}
	cout<<"经过站点最少的乘车路线:\n"<<"共经过"<<sitenum+1<<"站"<<endl;
	PrintPath_site(G);
	cout<<endl;
	cout<<"转车次数最少的乘车路线:\n"<<"共转车"<<rounum-1<<"次,共经过"<<Shortestpath_route[0]<<"个站点"<<endl;
	PrintPath_rou(G);
	cout<<endl;
	return OK;
}
