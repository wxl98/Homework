#include"Huffman.h"
int main()
{

	HuffmanTree HT=NULL;
	HuffmanCode HC=NULL;
	FILE *f;
	int *w,n,k;
	char filename[81],*s_type=(char*)malloc(sizeof(char)*MAX_CHARNUM);
	printf("请按相应按键进行操作：\n");
	printf("1:读入文件构建编码并输出字符及其对应编码\n2:将编码表及文章编码保存于文件\n3:解码并输出文章\n0:结束程序\n");
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
			printf("%d种字符\n",n);
			CreateHuffmanTree(HT,w,n);
			Get_HuffmanCode(HT,HC,n);
			for(int i=1;i<=n;i++)
			{
				putchar(s_type[i]);
				printf("出现次数:%d,编码:%s\n",w[i],HC[i]);
			}
			printf("\n"); 
		}
		else if(k==2)
		{
			if(HC!=NULL)
			{
				CreateCodeFile(HC,s_type,filename,n);
				printf("编码表已保存于CodeList.txt,文章编码保存于HCCode.data。\n"); 
				printf("\n"); 
			}
			else
				printf("请先读入文件并编码。\n\n"); 
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
				printf("请先读入文件并编码。\n\n");
			
		}
		printf("1:读入文件构建编码并输出字符及其对应编码\n2:将编码表及文章编码保存于文件\n3:解码并输出文章\n0:结束程序\n");
		scanf("%d",&k);
	}
	return 0;
}
