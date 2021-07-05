#include<iostream>
#include<fstream> 
#include<stdlib.h>
#include<string.h>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef struct TrieNode{
	int count;//ͳ�Ƶ���ǰ׺���ִ�����
	struct TrieNode *next[26];//26��Ӣ����ĸ
	bool IsWord;//������־����ʾ���������ܹ�����һ������ 
	char trans[30];//������˼������
}TrieNode,*Trie;
TrieNode *CreateTrieNode()
{
	TrieNode* node=(TrieNode *)malloc(sizeof(TrieNode));
	if(!node)
	{
		cout<<"OVERFLOW!"<<endl; 
		return NULL;
	}
	node->count=0;
	node->IsWord=false;
	memset(node->next,0,sizeof(node->next));//��ʼ��Ϊ��ָ��
	return node;
}
Trie Trie_Search_D(Trie &T,char *word,int &i)
{
	Trie node=T,parent=NULL;
    char *p=word;
    int id;
    while(*p)
    {
        id=*p - 'a';
        parent=node;
        i=id;
        node= node->next[id];
        ++p; 
        if(node == NULL)
            return NULL;
    }
    if(node->IsWord)// ���ҳɹ�
        return parent;
    else                     // ����ʧ��
        return NULL;
}
char* Trie_Search(Trie root, char* word)
{
    Trie node = root;
    char *p = word;
    int id;
    while( *p )
    {
        id = *p - 'a';
        node = node->next[id];
        ++p; 
        if(node == NULL)
            return NULL;
    }
    if(node->IsWord)          // ���ҳɹ�
        return node->trans;
    else                     // ����ʧ��
        return NULL;
}
void FileDeal_Delete(char *word)
{
	fstream in,out;
	char w[200][26],t[200][30];
	int i=0;
	in.open("DataBase.txt",ios::in);
	while(!in.eof())
	{
		in>>w[i];
		if(in.eof())
		{
			break;
		}
		in>>t[i];
		i++;
	}
	in.close();
	for(int j=0;j<i;j++)
	{
		if(strcmp(word,w[j])==0)
		{
			for(int k=j;k<i-1;k++)
			{
				strcpy(w[k],w[k+1]);
				strcpy(t[k],t[k+1]);
			}
			i--;
			break;
		}
	}
	out.open("DataBase.txt",ios::out);
	for(int j=0;j<i;j++)
	{
		out<<w[j]<<" "<<t[j]<<endl;
	}
	out.close();
}
void FileDeal_Revisetran(char *word,char *tran)
{
	fstream in,out;
	char w[200][26],t[200][30];
	int i=0;
	in.open("DataBase.txt",ios::in);
	while(!in.eof())
	{
		in>>w[i];
		if(in.eof())
		{
			break;
		}
		in>>t[i];
		i++;
	}
	in.close();
	for(int j=0;j<i;j++)
	{
		if(strcmp(word,w[j])==0)
		{
			strcpy(w[j],word);
			strcpy(t[j],tran);
			break;
		}
	}
	out.open("DataBase.txt",ios::out);
	for(int j=0;j<i;j++)
	{
		out<<w[j]<<" "<<t[j]<<endl;
	}
	out.close();
}
void FileDeal_Reviseword(char *word,char *new_word)
{
	fstream in,out;
	char w[200][26],t[200][30];
	int i=0;
	in.open("DataBase.txt",ios::in);
	while(!in.eof())
	{
		in>>w[i];
		if(in.eof())
		{
			break;
		}
		in>>t[i];
		i++;
	}
	in.close();
	for(int j=0;j<i;j++)
	{
		if(strcmp(word,w[j])==0)
		{
			strcpy(w[j],new_word);
			break;
		}
	}
	out.open("DataBase.txt",ios::out);
	for(int j=0;j<i-1;j++)
	{
		out<<w[j]<<" "<<t[j]<<endl;
	}
	out.close();
}
Status Trie_Insert(Trie &root, char* word, char* trans)
{
	fstream out;
	out.open("DataBase.txt",ios::out|ios::app);
	if(!out)
	{
		cout<<"�����ļ���ʧ�ܣ�"<<endl;
		return ERROR;
	}
    Trie node=root;
    int i;
    if(Trie_Search_D(root,word,i)!=NULL)
	{
		cout<<"�����Ѵ��ڣ�"<<endl;
		return ERROR;
	}
    char *p=word;
    int id;
    while(*p)
    {
        id = *p-'a';
        if(node->next[id] == NULL)  
        {
            node->next[id]=CreateTrieNode();
        }
        node = node->next[id];  // ÿ����һ�����൱����һ���´�������ָ�������ƶ�
        ++p;
        node->count += 1;      // ���д�������ͳ��ÿ������ǰ׺���ֵĴ�����Ҳ����ͳ��ÿ�����ʳ��ֵĴ���
    }
    node->IsWord=true;        //���ʽ����ĵط���Ǵ˴����Թ���һ������
    strcpy(node->trans,trans);
    out<<word<<" "<<trans<<endl;
    out.close();
    return OK;
}
Status InitTrie(Trie &T)
{
	T=CreateTrieNode();
	if(!T)
	{
		return ERROR;
	}
	fstream in;
	in.open("DataBase.txt",ios::in);
	if(!in)
	{
		cout<<"�����ļ���ʧ�ܡ�\n"; 
	}
	char word[26],tran[20];
	while(!in.eof())
	{
		in>>word;
		if(in.eof())
		{
			break;
		}
		in>>tran;
		Trie node=T;
		char *p=word;
		int id;
    	while(*p)
		{
        	id = *p-'a';
        	if(node->next[id] == NULL)  
			{
            	node->next[id]=CreateTrieNode();
        	}
        	node = node->next[id];
        	++p;
        	node->count += 1;
    	}	
    	node->IsWord=true;
    	strcpy(node->trans,tran);
	}
	in.close();
	return OK;
}
Status DeleteWord(Trie &T,char *word)
{
	Trie p;
	int location;//ɾ����λ�� 
	p=Trie_Search_D(T,word,location);
	if(p)
	{
		p->count--;
		delete p->next[location];
		p->next[location]=NULL;
		FileDeal_Delete(word);
		return OK;
	}
	else
		return ERROR;
}
Status Revise_Word(Trie &T,char *s,char *t)
{
	Trie p;
	int location;
	char tran[30];
	p=Trie_Search_D(T,s,location);
	if(p)
	{
		p->count--;
		strcpy(tran,p->trans);
		delete p->next[location];
		p->next[location]=NULL;
		Trie_Insert(T,t,tran);
		FileDeal_Reviseword(s,t);
		return OK;
	}
	else
	{
		return ERROR;
	}
}
Status Revise_Tran(Trie &T,char *word,char *new_tran)
{
	Trie p;
	int location;
	char *tran;
	p=Trie_Search_D(T,word,location);
	if(p)
	{
		strcpy(p->next[location]->trans,new_tran);
		FileDeal_Revisetran(word,new_tran);
		return OK;
	}
	else
		return ERROR;
}
void PrintAllword()
{
	fstream in;
	char word[26];
	char tran[30];
	in.open("DataBase.txt",ios::in);
	while(!in.eof())
	{
		in>>word;
		if(in.eof())
		{
			break;
		}
		in>>tran;
		cout<<word<<endl<<"�룺"<<tran<<endl;
	}
	in.close();
}
