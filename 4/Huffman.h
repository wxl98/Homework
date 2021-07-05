#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW -2
#define INFEASIBLE -1
#define ERROR 0
#define OK 1
#define MAX_CHARNUM 256
typedef int Status;
typedef struct{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;
typedef char* *HuffmanCode;
void Select(HuffmanTree HT,int n,int &l,int &r)
{
	int i,min;
	min=INT_MAX;
	for(i=1; i<=n;i++)
	{
		if(HT[i].parent==0&&HT[i].weight<=min)
		{
			min=HT[i].weight;
			l=i;
		}
	}
	min=INT_MAX;
	for(i=1;i<=n;i++)
	{
		if(i==l)
			continue;
		if(HT[i].parent==0&&HT[i].weight<=min)
		{
			min=HT[i].weight;
			r=i;
		}
	}
}
void CreateHuffmanTree(HuffmanTree &HT, int *w, int n)//*w为权重，n为有个权重
{
	int p,i,j,m,lc,rc;
	if(n<=1)
		return;//n<=1时无法生成一颗huffmantree。
	m=2*n-1;
	if(HT)
		free(HT);
	HT=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));//HT[0]不放节点用来当头节点
	for(p=1,i=1,j=1;i<=n;++i,++p,++j)//第一步生成所有权重的叶子节点
	{
		HT[p].weight=w[j];
		HT[p].parent=0;
		HT[p].lchild=0;
		HT[p].rchild=0;
	}
	for(;i<=m;i++)//按照Huffman的算法依次挑选出最小权重的结点组成树
	{
		Select(HT,i-1,lc,rc);//从HT[1..i-1]中找出当前权数最小且parent=0的两个结点位置分别为lc,rc。
		HT[lc].parent=i;
		HT[rc].parent=i;
		HT[i].parent=0;
		HT[i].lchild=lc;
		HT[i].rchild=rc;
		HT[i].weight=HT[lc].weight+HT[rc].weight;
	}
	HT[0].lchild=i-1;
	HT[0].weight=-1;
}
Status Get_HuffmanCode(HuffmanTree &HT, HuffmanCode &HC, int n)
{
	if(HC)
		free(HC);
	HC=(HuffmanCode)malloc(sizeof(char *)*(n+1));//0号位置不用
	if(!HC)
		exit(OVERFLOW);
	char *cd=(char*)malloc(sizeof(char)*n);
	if(!cd)
		exit(OVERFLOW);
	cd[n-1]='\0';
	int start,c,f;//存放位置、孩子结点位置、父节点位置 
	for(int i=1; i<=n; i++)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0; c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		}
		HC[i] = (char*)malloc(sizeof(n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
	return OK;
}
int Search(char *a,char c)
{
	for(int i=1;a[i]!='\0';i++)
	{
		if(a[i]==c)
			return i;
	}
	return 0;
}
int *Getweight(FILE *fp,char *(*s_type))
{
	int *w,num=0,i=1,j;
	w=(int*)malloc(sizeof(int)*MAX_CHARNUM);
	char c;
	for(j=1;j<MAX_CHARNUM;j++)
	{
		(*s_type)[j]='\0';
		w[j]=0;
	}
	w[0]=0;
	while(!feof(fp))
	{
		c=fgetc(fp);
		if(c==EOF)
			break;
		num++;
		if(j=Search(*s_type,c))
		{
			w[j]++;
		}
		else
		{
			(*s_type)[i]=c;
			w[i]++;
			i++;
			w[0]++;
		}
	}
	return w;
}
void writeBit(char *ch,FILE *fp)
{
	int i;
	int j;
	int count = 0;
	int  num;    //存储字符需要的多少个字节
	int left;	//字符串剩余不足8位的个数
	char *p = NULL; 
	for (i = 0; ch[i] !='\0'; i++)
	{
		count++;       //统计字符个数 
	}
	num = count / 8;
	left = count % 8;
	if (left == 0)	//如果left为0，那么num个字节刚好能够存放,否则需要num + 1字节
	{
		p = (char *)malloc(sizeof(char) * num);
		memset(p, 0, num);
	}
	else
	{
		p = (char *)malloc(sizeof(char) * (num + 1));
		memset(p, 0, num + 1);
	}
	j = -1;
	for (i = 0; i < count; i++)//位运算，每8个字符以2进制的形式储存在一个字符中 
	{
		if (i % 8 == 0)
		{
			j++;
		}
		p[j] <<= 1;        
		ch[i] -= '0';
		p[j] |= ch[i];
	}
	if (left != 0) //如果left不为0，需要把剩余的几个位向左边靠拢 
	{
		p[j] <<= 8 - left;
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p,1, num + 1,fp);
	}
	else
	{
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p, 1, num , fp);	
	}
}
Status CreateCodeFile(HuffmanCode HC,char *s,char *filename,int n)
{
	FILE *fp,*ftxt;
	char c,*temp=(char*)malloc(sizeof(char)*INT_MAX);
	strcpy(temp,"");
	int p;
	fp=fopen("CodeList.txt","w");
	if(!fp)
	{
		printf("open failed!\n");
		exit(ERROR);
	}
	for(int i=1;i<n;i++)
	{
		fprintf(fp,"%c%s\n",s[i],HC[i]);
	}
	fclose(fp);
	fp=fopen("HCCode.data","wb");
	ftxt=fopen(filename,"r");
	if(!ftxt||!fp)
	{
		printf("open failed!\n");
		exit(ERROR);
	}
	while(!feof(ftxt))
	{
		c=fgetc(ftxt);
		if(c==EOF)
			break;
		p=Search(s,c);
		strcat(temp,HC[p]);
	}
	writeBit(temp,fp);
	fclose(fp);
	fclose(ftxt);
	return OK;
}
char *readBit(FILE *fp)
{
	int count;
	int num;
	int left;
	int i,j,k=0;
	unsigned char flag=128;//即10000000
	char *p = NULL,*temp;
	fread(&count, sizeof(count), 1, fp);
	temp=(char*)malloc(sizeof(char)*(count+1));
	num=count/8;
	left=count%8;
	if (left == 0)
	{
		p = (char *)malloc(sizeof(char) * num);
		fread(p,1,num,fp);
	}
	else
	{
		p = (char *)malloc(sizeof(char) * (num + 1));
		fread(p, 1, num + 1, fp);
	}
	j = -1;
	for (i = 0; i < count; i++)
	{
		if(i % 8 == 0)
		{
			j++;
			flag = 128;
		}
		if((p[j] & flag))//通过改变flag字符2进制1的位置判读，一个字节哪个位是1，哪个位是0
		{
			temp[k++]='1';
			flag /= 2;
		}
		else
		{
			temp[k++]='0';
			flag /= 2;
		}
	}
	temp[k]='\0'; 
	return temp;
}
Status Decoding(FILE *fp,HuffmanTree HT,HuffmanCode HC,char *s,int n)
{
	int j;
	char *temp,c,filename[81],back[20];
	FILE *out;
	printf("please input the filename of the decoding file:\n");
	scanf("%s",filename);
	out=fopen(filename,"w");
	if(!out)
	{
		printf("open failed!\n");
		exit(ERROR);
	}
	temp=readBit(fp);
	int i=0,k,m;
	c=temp[i++];
	while(c!='\0')
	{
		m=0;
		k=2*n-1;
		while(HT[k].lchild!=0&&HT[k].rchild!=0)
		{
			back[m++]=c;
			if(c=='0')
				k=HT[k].lchild;
			else if(c=='1')
				k=HT[k].rchild;
			c=temp[i++];
		}
		back[m]='\0';
		for(j=1;j<=n;j++)
		{
			if(strcmp(back,HC[j])==0)
			{
				printf("%c",s[j]);
				fputc(s[j],out);
				break;
			}
		}
	}
	fclose(out);
}
