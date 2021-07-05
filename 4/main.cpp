#include"Huffman.h"
int main()
{

	HuffmanTree HT=NULL;
	HuffmanCode HC=NULL;
	FILE *f;
	int *w,n,k;
	char filename[81],*s_type=(char*)malloc(sizeof(char)*MAX_CHARNUM);
	printf("�밴��Ӧ�������в�����\n");
	printf("1:�����ļ��������벢����ַ������Ӧ����\n2:����������±��뱣�����ļ�\n3:���벢�������\n0:��������\n");
	scanf("%d",&k);
	while(k!=0)
	{
		if(k==1)
		{
			printf("please intput the filename of the essay:\n");
			scanf("%s",filename);
			f=fopen(filename,"r");
			if(!f)
			{
				printf("open failed!\n");
				exit(ERROR);
			}
			w=Getweight(f,&s_type);
			fclose(f);
			n=w[0];
			printf("%d���ַ�\n",n);
			CreateHuffmanTree(HT,w,n);
			Get_HuffmanCode(HT,HC,n);
			for(int i=1;i<=n;i++)
			{
				putchar(s_type[i]);
				printf("���ִ���:%d,����:%s\n",w[i],HC[i]);
			}
			printf("\n"); 
		}
		else if(k==2)
		{
			if(HC!=NULL)
			{
				CreateCodeFile(HC,s_type,filename,n);
				printf("������ѱ�����CodeList.txt,���±��뱣����HCCode.data��\n"); 
				printf("\n"); 
			}
			else
				printf("���ȶ����ļ������롣\n\n"); 
		}
		else if(k==3)
		{
			if(HC!=NULL)
			{
				f=fopen("HCCode.data","rb");
				if(!f)
				{
					printf("open failed!\n");
					exit(ERROR);
				}
				Decoding(f,HT,HC,s_type,n);
				printf("\n"); 
				fclose(f);
			}
			else
				printf("���ȶ����ļ������롣\n\n");
			
		}
		printf("1:�����ļ��������벢����ַ������Ӧ����\n2:����������±��뱣�����ļ�\n3:���벢�������\n0:��������\n");
		scanf("%d",&k);
	}
	return 0;
}
