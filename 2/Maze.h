#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 20
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define N 22              //�Թ���������� 
typedef int Status;
typedef struct
{
	int row;//row��ʾ"��"��
	int line;//line��ʾ"��"��
}PosType;//λ�õ�Ԫ������
typedef struct
{
	int ord;//��ͨ����·���ϵ�"���"
	PosType seat;//ͨ�������Թ��е�"����λ��"
	int di;//�Ӵ�ͨ����������ͨ�����"����"
}ElemType;//ջ��Ԫ������
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

Status Stack_Traverse(SqStack &S)//����������յ�ͨ· 
{
	ElemType *p=S.base;
	for(p;p<S.top;p++)
	{
		printf("%d,%d\n",(*p).seat.row,(*p).seat.line);
	}
	return OK;
}
void InitMaze(int maze[N][N], int &x, int &y)//��ʼ���Թ�
{
	FILE *fp;
	char s[N];
	int i,j;
	printf("�������ʼ���Թ����ļ�����\n");
	scanf("%s",s);
	fp=fopen(s,"r");
	if(!fp)
	{
		printf("Open file failed!\n");
		exit(ERROR);
	}
	fscanf(fp,"%d %d ",&x,&y);//�����Թ���������������
	while(!feof(fp))
	{
		for(i=1; i<=x; i++)
		{
			for(j=1; j<=y; j++)
			{
				fscanf(fp,"%d",&(maze[i][j]));//�����Թ���Ϣ 
			}
		}
	}
	printf("����ɹ���\n\n"); 
	fclose(fp);
}

void PrintMaze(int maze[N][N], int x, int y)//��ʾ������Թ�ͼ 
{
	int i,j;
	printf("������Թ�����������:");
	printf("row:%d,col:%d\n",x,y);
	printf("������Թ�(#��ʾǽ):\n"); 
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

Status Pass(int maze[N][N], PosType CurPos)//�жϵ�ǰλ���Ƿ��ͨ
{
	if(maze[CurPos.row][CurPos.line]==0)
		return OK;//�����ǰλ���ǿ���ͨ��,����1
    else
		return ERROR;//�����������0
}

void MarkFoot(int maze[N][N], PosType CurPos)//��ǵ�ǰλ�ò���ͨ�������߹�������8���
{
	maze[CurPos.row][CurPos.line]=8;
}

PosType NextPos(PosType CurPos, int Di)//������һλ��
{
	PosType ChangePos;
	switch(Di)
	{
    case 1://������һ�� 
        ChangePos.row=CurPos.row;
        ChangePos.line=CurPos.line+1;
        break;
    case 2://������һ�� 
        ChangePos.row=CurPos.row+1;
        ChangePos.line=CurPos.line;
        break;
    case 3://������һ�� 
        ChangePos.row=CurPos.row;
        ChangePos.line=CurPos.line-1;
        break;
    case 4://������һ�� 
        ChangePos.row=CurPos.row-1;
        ChangePos.line=CurPos.line;
        break;
	}
	return ChangePos;
}

Status MazePath(int maze[N][N], SqStack &S, PosType start, PosType end)//��ͨ·
{
	PosType curpos;
	int curstep;
	ElemType e;
	curpos=start;//�趨"��ǰλ��"Ϊ"���λ��
	curstep=1;//̽����һ��
	do{
		if(Pass(maze,curpos))//��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ����
		{
			MarkFoot(maze,curpos);//�����㼣
			e.di=1;
			e.ord=curstep;
			e.seat=curpos;
			Push(S,e);//����·��
			if (curpos.row==end.row && curpos.line==end.line)
				return OK;//�����յ㣨���ڣ�
			curpos=NextPos(curpos,1);//��һλ���ǵ�ǰλ�õĶ���
			curstep++;//̽����һ�� 
		}
    	else//��ǰλ�ò���ͨ��
		{
			if(!StackEmpty(S)) 
			{
            	   Pop(S,e);
            	   while (e.di==4 && !StackEmpty(S))
					{
                		MarkFoot(maze,e.seat);//���²���ͨ���ı��,���˻�һ��
						Pop(S,e);
					}
            	   if(e.di<4)
					{
                	   e.di++;// ����һ������̽��
					   Push(S,e);
					   curpos=NextPos(e.seat,e.di);//��ǰλ����Ϊ�·�������ڿ�
					}
			}
		}
	}while(!StackEmpty(S));
	return ERROR;//��û��ͨ· 
}

void PrintPath(int maze[N][N], SqStack &S, int x, int y, PosType start, PosType end)//��ʾͨ·
{
	int i,j,m,num;
	printf("\nͨ··��:\n");
	ElemType *p=S.base;
	while(p!=S.top)
	{
		maze[p->seat.row][p->seat.line]=2;//���Ϊ·���еĵ�
		p++;
	}
	printf("·��ͼΪ��\n");
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
				if((i==start.row&&j==start.line)||(i==end.row&&j==end.line))//�������ںͳ��������� 
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
	printf("·����·Ϊ��\n");
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
	printf("·������ɹ���\n");
}
