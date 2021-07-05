#include"Trie.h"
int main()
{
	Trie Root;
	int select,k;
	char word[26],tran[30],revise[30];
	char *find; 
	InitTrie(Root);
	cout<<"�밴������ʾ���в�����"<<endl;
	cout<<"1:��������\n2:��ӵ���\n3:ɾ������\n4:�޸ĵ���\n5:��ʾ��������\n0:��������"<<endl;
	cin>>select;
	while(select!=0)
	{
		if(select==1)
		{
			cout<<"������Ҫ���ҵĵ���:"<<endl;
			cin>>word;
			find=Trie_Search(Root,word);
			if(find)
			{
				cout<<word<<endl<<"��:"<<find<<endl; 
			}
			else
			{
				cout<<"�ֵ��в����ڸõ��ʣ��Ƿ�ѡ�����(1:Y,0:N):"<<endl; 
				cin>>k;
				if(k==1)
				{
					cout<<"������"<<word<<"�ķ���:"<<endl;
					cin>>tran;
					Trie_Insert(Root,word,tran);
					cout<<"������ӳɹ�!"<<endl;
				}
				else if(k==0)
				{
				}
				else
				{
					cout<<"����ָ�����"<<endl;
				}
			}
		}
		else if(select==2)
		{
			cout<<"��������Ҫ��ӵĵ��ʸ����ķ���:"<<endl;
			cin>>word;
			cin>>tran;
			if(Trie_Insert(Root,word,tran))
			{
				cout<<"������ӳɹ���"<<endl;
			}
		}
		else if(select==3)
		{
			cout<<"������Ҫɾ���ĵ���:"<<endl;
			cin>>word;
			if(DeleteWord(Root,word))
				cout<<"����ɾ���ɹ�!"<<endl;
			else
				cout<<"�ֵ����޴˵���!"<<endl; 
		}
		else if(select==4)
		{
			cout<<"��ѡ���޸�����:\n1:�޸ĵ���\n2:�޸ķ���"<<endl;
			cin>>k;
			if(k==1)
			{
				cout<<"������Ҫ�޸ĵĵ��ʺ��޸ĺ�ĵ���:"<<endl;
				cin>>word;
				cin>>revise;
				if(Revise_Word(Root,word,revise))
				{
					cout<<"�޸ĳɹ���"<<endl;
				}
				else
				{
					cout<<"�ֵ�������Ҫ�޸ĵĵ���!"<<endl; 
				}
			}
			else if(k==2)
			{
				cout<<"������Ҫ�޸ĵĵ��ʺ��޸ĺ�ķ���:"<<endl;
				cin>>word;
				cin>>revise;
				if(Revise_Tran(Root,word,revise))
				{
					cout<<"�޸ĳɹ���"<<endl;
				}
				else
				{
					cout<<"�ֵ�������Ҫ�޸ĵĵ���!"<<endl; 
				}
			}
			else
			{
				cout<<"����ָ�����!"<<endl;
			}
		}
		else if(select==5)
		{
			PrintAllword();
		} 
		else
		{
			cout<<"����ָ�����!"<<endl;
		}
		cout<<"1:��������\n2:��ӵ���\n3:ɾ������\n4:�޸ĵ���\n5:��ʾ��������\n0:��������"<<endl;
		cin>>select;
	}
}
