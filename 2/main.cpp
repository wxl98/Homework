#include"Maze.h"
int main()
{
	int Maze[N][N],maze[N][N];
	SqStack S;
	PosType start,end;
	start.row=0;
	start.line=0;
	end.row=0;
	end.row=0;
	int k,t;//ѡ���� 
	int x,y;//�����Թ�����������
	printf("�밴��Ӧ��ťִ�в�����\n"); 
	printf("1:��ʼ���Թ�����ʾ�Թ���0��ʾͨ·��1��ʾ�ϰ���\n2:�����Թ�����ںͳ���\n3:Ѱ��·��\n4:��������\n");
	scanf("%d",&k);
	while(k!=4)
	{
		if(k==1)
		{
			InitMaze(Maze,x,y);
			PrintMaze(Maze,x,y);
		}
		else if(k==2)
		{
			printf("������꣺\nrow:");
			scanf("%d",&start.row);
			printf("col:");
			scanf("%d",&start.line);
			printf("��������:\nrow:");
			scanf("%d",&end.row);
			printf("col:");
			scanf("%d",&end.line);
			printf("���óɹ���\n\n"); 
		}
		else if(k==3)
		{
			if(end.line!=0&&end.row!=0)//�ж��Ƿ����������ͳ������ꡣ 
			{
				InitStack(S);
				for(int i=0; i<N; i++)
				{
					for(int j=0; j<N; j++)
					{
						maze[i][j]=Maze[i][j];
					}
				}
				if(MazePath(maze,S,start,end))
				{
					PrintPath(maze,S,x,y,start,end);
				}
				else
				{
					printf("���Թ�û��ͨ·��\n"); 
				}
				DestroyStack(S);
				start.row=0;
				start.line=0;
				end.row=0;
				end.row=0;
				printf("�����³�ʼ���Թ�����ڳ������ꡣ\n\n"); 
			}
			else
			{
				printf("δ���������ͳ������꣬������ѡ��\n\n");
			}
		}
		else
		{
			printf("ָ���������������\n\n");
		}
		printf("1:��ʼ���Թ�����ʾ�Թ���0��ʾͨ·��1��ʾ�ϰ���\n2:�����Թ�����ںͳ���\n3:Ѱ��·��\n4:��������\n");
		scanf("%d",&k);
	}
	return 0;
}
