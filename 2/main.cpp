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
	int k,t;//选择器 
	int x,y;//接收迷宫行数和列数
	printf("请按对应按钮执行操作：\n"); 
	printf("1:初始化迷宫并显示迷宫（0表示通路，1表示障碍）\n2:设置迷宫的入口和出口\n3:寻找路线\n4:结束程序\n");
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
			printf("入口坐标：\nrow:");
			scanf("%d",&start.row);
			printf("col:");
			scanf("%d",&start.line);
			printf("出口坐标:\nrow:");
			scanf("%d",&end.row);
			printf("col:");
			scanf("%d",&end.line);
			printf("设置成功！\n\n"); 
		}
		else if(k==3)
		{
			if(end.line!=0&&end.row!=0)//判断是否输入口坐标和出口坐标。 
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
					printf("该迷宫没有通路！\n"); 
				}
				DestroyStack(S);
				start.row=0;
				start.line=0;
				end.row=0;
				end.row=0;
				printf("请重新初始化迷宫和入口出口坐标。\n\n"); 
			}
			else
			{
				printf("未输入口坐标和出口坐标，请重新选择。\n\n");
			}
		}
		else
		{
			printf("指令错误，请重新输入\n\n");
		}
		printf("1:初始化迷宫并显示迷宫（0表示通路，1表示障碍）\n2:设置迷宫的入口和出口\n3:寻找路线\n4:结束程序\n");
		scanf("%d",&k);
	}
	return 0;
}
