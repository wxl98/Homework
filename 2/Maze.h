#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 20
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define N 22              //迷宫最大行列数 
typedef int Status;
typedef struct
{
	int row;//row表示"行"号
	int line;//line表示"列"号
}PosType;//位置的元素类型
typedef struct
{
	int ord;//该通道在路径上的"序号"
	PosType seat;//通道块在迷宫中的"坐标位置"
	int di;//从此通道走向下以通道块的"方向"
}ElemType;//栈的元素类型
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack &S)
{
	if(!S.base)
	{
		free(S.base);
		S.top=S.base=NULL;
		S.stacksize=0;
	}
	return OK;
}

Status Push(SqStack &S, ElemType &e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(ElemType*)realloc(S.base,(STACKINCREMENT+S.stacksize)*sizeof(ElemType));
		if(!S.base)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Pop(SqStack &S, ElemType &e)
{
	if(S.base==S.top)
		return ERROR;
	e=*--S.top;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
		return OK;
	else
		return ERROR;
}

Status Stack_Traverse(SqStack &S)//用于输出最终的通路 
{
	ElemType *p=S.base;
	for(p;p<S.top;p++)
	{
		printf("%d,%d\n",(*p).seat.row,(*p).seat.line);
	}
	return OK;
}
void InitMaze(int maze[N][N], int &x, int &y)//初始化迷宫
{
	FILE *fp;
	char s[N];
	int i,j;
	printf("请输入初始化迷宫的文件名：\n");
	scanf("%s",s);
	fp=fopen(s,"r");
	if(!fp)
	{
		printf("Open file failed!\n");
		exit(ERROR);
	}
	fscanf(fp,"%d %d ",&x,&y);//读入迷宫的行数和列数。
	while(!feof(fp))
	{
		for(i=1; i<=x; i++)
		{
			for(j=1; j<=y; j++)
			{
				fscanf(fp,"%d",&(maze[i][j]));//读入迷宫信息 
			}
		}
	}
	printf("读入成功！\n\n"); 
	fclose(fp);
}

void PrintMaze(int maze[N][N], int x, int y)//显示读入的迷宫图 
{
	int i,j;
	printf("读入的迷宫行数和列数:");
	printf("row:%d,col:%d\n",x,y);
	printf("读入的迷宫(#表示墙):\n"); 
    for(i=0;i<y+2;i++)
		printf("%c ",'#');
	printf("\n");	
	for(i=1;i<x+1;i++)
	{
		printf("%c ",'#');
        for(int j=1;j<y+1;j++)
		{
			printf("%d ",maze[i][j]);
		}
		printf("%c",'#');
		printf("\n");
	}
	for(i=0;i<y+2;i++)
		printf("%c ",'#');
	printf("\n\n");
}

Status Pass(int maze[N][N], PosType CurPos)//判断当前位置是否可通
{
	if(maze[CurPos.row][CurPos.line]==0)
		return OK;//如果当前位置是可以通过,返回1
    else
		return ERROR;//其它情况返回0
}

void MarkFoot(int maze[N][N], PosType CurPos)//标记当前位置不可通或者已走过，并用8标记
{
	maze[CurPos.row][CurPos.line]=8;
}

PosType NextPos(PosType CurPos, int Di)//进入下一位置
{
	PosType ChangePos;
	switch(Di)
	{
    case 1://向右走一步 
        ChangePos.row=CurPos.row;
        ChangePos.line=CurPos.line+1;
        break;
    case 2://向下走一步 
        ChangePos.row=CurPos.row+1;
        ChangePos.line=CurPos.line;
        break;
    case 3://向左走一步 
        ChangePos.row=CurPos.row;
        ChangePos.line=CurPos.line-1;
        break;
    case 4://向上走一步 
        ChangePos.row=CurPos.row-1;
        ChangePos.line=CurPos.line;
        break;
	}
	return ChangePos;
}

Status MazePath(int maze[N][N], SqStack &S, PosType start, PosType end)//找通路
{
	PosType curpos;
	int curstep;
	ElemType e;
	curpos=start;//设定"当前位置"为"入口位置
	curstep=1;//探索第一步
	do{
		if(Pass(maze,curpos))//当前位置可通过，即是未曾走到过的通道块
		{
			MarkFoot(maze,curpos);//留下足迹
			e.di=1;
			e.ord=curstep;
			e.seat=curpos;
			Push(S,e);//加入路径
			if (curpos.row==end.row && curpos.line==end.line)
				return OK;//到达终点（出口）
			curpos=NextPos(curpos,1);//下一位置是当前位置的东邻
			curstep++;//探索下一步 
		}
    	else//当前位置不能通过
		{
			if(!StackEmpty(S)) 
			{
            	   Pop(S,e);
            	   while (e.di==4 && !StackEmpty(S))
					{
                		MarkFoot(maze,e.seat);//留下不能通过的标记,并退回一步
						Pop(S,e);
					}
            	   if(e.di<4)
					{
                	   e.di++;// 换下一个方向探索
					   Push(S,e);
					   curpos=NextPos(e.seat,e.di);//当前位置设为新方向的相邻块
					}
			}
		}
	}while(!StackEmpty(S));
	return ERROR;//即没有通路 
}

void PrintPath(int maze[N][N], SqStack &S, int x, int y, PosType start, PosType end)//显示通路
{
	int i,j,m,num;
	printf("\n通路路径:\n");
	ElemType *p=S.base;
	while(p!=S.top)
	{
		maze[p->seat.row][p->seat.line]=2;//标记为路径中的点
		p++;
	}
	printf("路径图为：\n");
	for(m=0;m<y+2;m++)
		printf("%c ",'#');
	printf("\n");
	for(i=1;i<x+1;i++)
	{
		printf("%c ",'#');
		for(int j=1;j<y+1;j++)
		{
			if(maze[i][j]==2)
			{
				if((i==start.row&&j==start.line)||(i==end.row&&j==end.line))//如果是入口和出口另外标记 
				{
					if(i==start.row&&j==start.line)
						printf("S ");
		    		if(i==end.row&&j==end.line)
						printf("E ");
				}
				else
					printf("%c ",' ');
			}
			else
				printf("%c ",'#');
		}
		printf("%c ",'#');
		printf("\n");
	}
	for(i=0;i<y+2;i++)
		printf("%c ",'#');
	printf("\n");
	printf("路径线路为：\n");
	SqStack M;	
	InitStack(M);
	ElemType e1;
	while(!StackEmpty(S))
	{ 	
		Pop(S,e1);
		Push(M,e1);
	}
	num=0;
	while(!StackEmpty(M))
	{
		num++;
		Pop(M,e1);
		printf("(%d,%d)",e1.seat.row,e1.seat.line);
		if(num%8==0)
			printf("\n");
	}
	DestroyStack(M);
	printf("\n");
	printf("路径输出成功！\n");
}
