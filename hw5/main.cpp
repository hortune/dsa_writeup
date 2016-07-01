
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
//int PRIME=10000019;
using namespace std;
typedef bool (*comp)(string&,string&);

struct node
{
	char word[36]={};
	node * next=NULL;
};
vector<node> hash_table;
bool cmp_max(string& a,string &b){
	if(a>b)
		return 1;
	return 0;
};
priority_queue<string,vector<string>,comp> pqueue1(cmp_max),pqueue2(cmp_max);
inline int hash_make(string &a)
{
	unsigned long int hash_num=0;
	for(int i=0;i<a.size();i++)
		hash_num=(hash_num<<5)+hash_num+a[i];
	hash_num%=10000019;
	return int(hash_num);
}
inline void lower_case(char &a)
{
	if(a<='Z'&&a>='A')
		a+=32;
}
bool is_it_in_dictionary(string &a)
{
	int hash_num = hash_make(a);
	node *next=hash_table[hash_num].next;
	if(strcmp(hash_table[hash_num].word,a.c_str())==0)
		return 1;
	else if(next==NULL)
		return 0;
	else
		while(next->next!=NULL)
		{
			if(strcmp(next->word,a.c_str())==0)
				return 1;
			next=next->next;
		}
	return 0;
}
void trytry(string &str,priority_queue<string,vector<string>,comp>  &test)//trying
{
	string temp;
	for(int i=0;i<str.size();i++)//subsitute
		for(int j=0;j<26;j++)
		{
			temp = str;
			temp[i]='a'+j;
			test.push(temp);
		}
	for(int i=0;i<=str.size();i++)
		for(int j=0;j<26;j++)
		{
			temp=str;
			temp.insert(i,1,'a'+j);
			test.push(temp);
		}
	for(int i=0;i<=str.size();i++)
		{
			temp=str;
			temp.erase(i,1);
			test.push(temp);
		}
	temp=str;
	for(int i=0;i<str.size()-1;i++)
	{
		char temp_char;
		temp_char = temp[i];
		temp[i]= temp[i+1];
		temp[i+1]=temp_char;
		test.push(temp);
		temp_char = temp[i];
		temp[i]= temp[i+1];
		temp[i+1]=temp_char;
	}
}
void trytry2(string &str,priority_queue<string,vector<string>,comp>  &test)//trying
{
	string temp;
	for(int i=0;i<str.size();i++)//subsitute
		for(int j=0;j<26;j++)
		{
			temp = str;
			temp[i]='a'+j;
			if(is_it_in_dictionary(temp))
				test.push(temp);
		}
	for(int i=0;i<=str.size();i++)
		for(int j=0;j<26;j++)
		{
			temp=str;
			temp.insert(i,1,'a'+j);
			if(is_it_in_dictionary(temp))
				test.push(temp);
		}
	for(int i=0;i<=str.size();i++)
		{
			temp=str;
			temp.erase(i,1);
			if(is_it_in_dictionary(temp))
				test.push(temp);
		}
	temp=str;
	for(int i=0;i<str.size()-1;i++)
	{
		char temp_char;
		temp_char = temp[i];
		temp[i]= temp[i+1];
		temp[i+1]=temp_char;
		if(is_it_in_dictionary(temp))
				test.push(temp);
		temp_char = temp[i];
		temp[i]= temp[i+1];
		temp[i+1]=temp_char;
	}
}

int main()
{
	//cin>>PRIME;
	FILE *fp;
	fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "r");
	char ch;
	string str;
	hash_table.reserve(10000019);
	int i=0;
	while(1){
		while((ch = fgetc(fp))!=EOF)
		{
			if(ch== ' '||ch==';')
				break;
			else
			{
				lower_case(ch);
				str+=ch;
			}
		}
		if(str.size())
		{
			int hash_num=(int)hash_make(str);
			if(hash_table[hash_num].next!=NULL)
			{
				node * next;
				next=hash_table[hash_num].next;
				while(next->next!=NULL)
					next=next->next;
				next->next = new node;
				strcpy(next->word,str.c_str());
			}
			else
			{
				hash_table[hash_num].next = new node;
				strcpy(hash_table[hash_num].word,str.c_str());
			}
			//printf("%s %d\n",str.c_str(),hash_num);
		}
		while(((ch=fgetc(fp)) != '\n')&&(ch!=EOF));
		if(ch==EOF)break;
		str.clear();
	}
	char a;
	str.clear();
	/*int max=0;
	for(i=0;i<PRIME;i++)
	{
		node * next;
		int j=0;
		if(hash_table[i].next!=NULL)
		{
			next =hash_table[i].next;
			while(next->next!=NULL)
			{
				j++;
				next=next->next;
			}
		}	

		if(max<j)max=j;
	}
	cout<<max<<endl;
	*/
	
	while(1)
	{
		while((a=getchar())!=EOF)
		{
			if(a!='\t')
			{
				//lower_case(a);
				str+=a;
			}
			else
				break;
		}
		//cout<<"hi"<<endl;
		if(a==EOF)
			break;
		printf("%s ==>",str.c_str());
		if(is_it_in_dictionary(str))
			printf(" OK\n");
		else
		{
			trytry(str,pqueue1);
			string pre = "";
			while(!pqueue1.empty())
			{
				string temp = pqueue1.top();
				pqueue1.pop();
				if(temp!=pre&&temp!="")
				{
					trytry2(temp,pqueue2);
				}
				pre = temp;
			}
			pre = "";
			if(pqueue2.empty())
				printf(" NONE");
			while(!pqueue2.empty())
			{
				string temp =pqueue2.top();
				pqueue2.pop();
				if(temp!=pre)
						printf(" %s",temp.c_str());
				pre = temp;
			}
			printf("\n");
		}
		while(a=getchar())
		{
			if(a=='\n'||a=='\r'||a==EOF)
				break;
		}
		
		str.clear();
	}
	

}
