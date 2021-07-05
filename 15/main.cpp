#include"Trie.h"
int main()
{
	Trie Root;
	int select,k;
	char word[26],tran[30],revise[30];
	char *find; 
	InitTrie(Root);
	cout<<"请按根据提示进行操作："<<endl;
	cout<<"1:查找生词\n2:添加单词\n3:删除单词\n4:修改单词\n5:显示所有生词\n0:结束程序"<<endl;
	cin>>select;
	while(select!=0)
	{
		if(select==1)
		{
			cout<<"请输入要查找的单词:"<<endl;
			cin>>word;
			find=Trie_Search(Root,word);
			if(find)
			{
				cout<<word<<endl<<"译:"<<find<<endl; 
			}
			else
			{
				cout<<"字典中不存在该单词，是否选择插入(1:Y,0:N):"<<endl; 
				cin>>k;
				if(k==1)
				{
					cout<<"请输入"<<word<<"的翻译:"<<endl;
					cin>>tran;
					Trie_Insert(Root,word,tran);
					cout<<"生词添加成功!"<<endl;
				}
				else if(k==0)
				{
				}
				else
				{
					cout<<"操作指令错误！"<<endl;
				}
			}
		}
		else if(select==2)
		{
			cout<<"请输入你要添加的单词跟它的翻译:"<<endl;
			cin>>word;
			cin>>tran;
			if(Trie_Insert(Root,word,tran))
			{
				cout<<"生词添加成功！"<<endl;
			}
		}
		else if(select==3)
		{
			cout<<"请输入要删除的单词:"<<endl;
			cin>>word;
			if(DeleteWord(Root,word))
				cout<<"单词删除成功!"<<endl;
			else
				cout<<"字典中无此单词!"<<endl; 
		}
		else if(select==4)
		{
			cout<<"请选择修改内容:\n1:修改单词\n2:修改翻译"<<endl;
			cin>>k;
			if(k==1)
			{
				cout<<"请输入要修改的单词和修改后的单词:"<<endl;
				cin>>word;
				cin>>revise;
				if(Revise_Word(Root,word,revise))
				{
					cout<<"修改成功！"<<endl;
				}
				else
				{
					cout<<"字典中无您要修改的单词!"<<endl; 
				}
			}
			else if(k==2)
			{
				cout<<"请输入要修改的单词和修改后的翻译:"<<endl;
				cin>>word;
				cin>>revise;
				if(Revise_Tran(Root,word,revise))
				{
					cout<<"修改成功！"<<endl;
				}
				else
				{
					cout<<"字典中无您要修改的单词!"<<endl; 
				}
			}
			else
			{
				cout<<"操作指令错误!"<<endl;
			}
		}
		else if(select==5)
		{
			PrintAllword();
		} 
		else
		{
			cout<<"操作指令错误!"<<endl;
		}
		cout<<"1:查找生词\n2:添加单词\n3:删除单词\n4:修改单词\n5:显示所有生词\n0:结束程序"<<endl;
		cin>>select;
	}
}
