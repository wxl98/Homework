#include"Expression.h"
int main()
{
	int select;
	float Out;
	char s[128];
	printf("请选择读取表达式方式：\n");
	printf("1:键盘输入\n2:文件读取\n0:结束程序\n"); 
	scanf("%d",&select);
	while(select!=0)
	{
		if(select==1)
		{
			puts("请输入表达式:");
			scanf("%s",s);
			if(EvaluateExpression(s,Out))
			{
				puts("该表达式的值为:");
				printf("%s\b=%g\n\n",s,Out);
			}
		}
		else if(select==2)
		{
			puts("请输入文件名:");
			char filename[81],temp;
			scanf("%s",filename);
			FILE *fp;
			fp=fopen(filename,"r");
			if(!fp)
			{
				puts("文件打开失败！\n");
				exit(0);
			}
			int i=0;
			while(!feof(fp))
			{
				temp=fgetc(fp);
				if(temp!=EOF)
					s[i++]=temp;
			}
			s[i]='\0';
			fclose(fp);
			printf("该表达式为:%s\n",s);
			if(EvaluateExpression(s,Out))
			{
				puts("该表达式的值为:");
				printf("%s\b=%g\n\n",s,Out);
			}
		}
		else
			printf("错误输入！\n\n");
		printf("请选择读取表达式方式：\n");
		printf("1:键盘输入\n2:文件读取\n0:结束程序\n"); 
		scanf("%d",&select);
	}
    return 0;
}
