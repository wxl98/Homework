#include"Expression.h"
int main()
{
	int select;
	float Out;
	char s[128];
	printf("��ѡ���ȡ���ʽ��ʽ��\n");
	printf("1:��������\n2:�ļ���ȡ\n0:��������\n"); 
	scanf("%d",&select);
	while(select!=0)
	{
		if(select==1)
		{
			puts("��������ʽ:");
			scanf("%s",s);
			if(EvaluateExpression(s,Out))
			{
				puts("�ñ��ʽ��ֵΪ:");
				printf("%s\b=%g\n\n",s,Out);
			}
		}
		else if(select==2)
		{
			puts("�������ļ���:");
			char filename[81],temp;
			scanf("%s",filename);
			FILE *fp;
			fp=fopen(filename,"r");
			if(!fp)
			{
				puts("�ļ���ʧ�ܣ�\n");
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
			printf("�ñ��ʽΪ:%s\n",s);
			if(EvaluateExpression(s,Out))
			{
				puts("�ñ��ʽ��ֵΪ:");
				printf("%s\b=%g\n\n",s,Out);
			}
		}
		else
			printf("�������룡\n\n");
		printf("��ѡ���ȡ���ʽ��ʽ��\n");
		printf("1:��������\n2:�ļ���ȡ\n0:��������\n"); 
		scanf("%d",&select);
	}
    return 0;
}
