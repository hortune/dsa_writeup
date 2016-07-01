#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
unsigned int temp_value=100;
int i,j,total=0;
char **matrix;
char **ordinary_matrix;
char prep[20][10]={ "of", "to","in", "for", "with", "on", "at", "by", "from", "up", "about",
"than", "after", "before", "down", "between", "under", "since", "without", "near"};

struct data{
	unsigned int a;
	char **b;
};
typedef bool (*comp)(data&,data&);
int bool_map_num=0;
struct bool_map{
	int front,back;
}map_bo[5];
bool cmp_max(data& a,data &b){
	
	if(a.a>b.a)
		return 0;
	else if(a.a==b.a)
	{
		char **temp_a;
		char **temp_b;
		temp_a=a.b;
		temp_b=b.b;
		char temp_a_1[101];
		int q=0;
		while(*temp_a)
		{
			for(char * te=*temp_a;*te;te++)
			{
				temp_a_1[q]=*te;
				q++;
			}
			temp_a_1[q]=' ';
			q++;
			temp_a++;
		}
		temp_a_1[q]='\0';
		char temp_b_1[101];
		q=0;
		while(*temp_b)
		{
			for(char * te =*temp_b;*te;te++)
			{
				temp_b_1[q]=*te;
				q++;
			}
			temp_b_1[q]=' ';
			q++;
			temp_b++;
		}
		temp_b_1[q]='\0';
		if(strcmp(temp_a_1,temp_b_1)>0)
			return 1;
		else
			return 0;

	}
	return 1;
};//not finished;
void print(char **a)
{	
	bool first=1;
	for(;*a;a++)
	{	if(first)
		first=0;
		else
		printf(" ");
		for(char *k=*a;*k;k++)
			printf("%c",*k);
	}
}
priority_queue<data,vector<data>,comp> queue1(cmp_max);

struct node{
	unsigned int value=0;
	node* next[27];
}*root=new node(),*root_prep=new node();

int lookup(char* s){
    node* p = root;
    for (; *s; ++s)
    {
    char temp=*s-'a';
    if(*s==' ')
		temp='{';
	if (!p->next[temp]) return 0;
        p = p->next[temp];
    }
    return p->value;
}
unsigned int lookup_matrix(char** s){
    node* p = root;
    for(char *g=*s;*g;g++)
			{
				int temp=*g-'a';
				if (!p->next[temp]) return 0;
        			p = p->next[temp];
			}
	++s;
    for(;*s;++s)
		{
			if(!p->next[26])return 0;
			p=p->next[26];
			for(char *g=*s;*g;g++)
			{
				int temp=*g-'a';
				if (!p->next[temp]) return 0;
        			p = p->next[temp];
			}
		}
    return p->value;
}
void input(char *path){
	FILE *fp;
	fp = fopen(path, "rb");
	char ch='a';
	int i=0;
	int buffer_size=4096;
	char *buffer = new char [4096];
	bool eat_k=false;
	node * p =root;
 	//long long int line=0;
	while(i= fread(buffer,1,buffer_size,fp)){
		for(int j=0;j<i;j++)
		{
			//line++;
			if(eat_k)
			{
				if(buffer[j]=='k')
				{
					eat_k=false;
					p->value=temp_value;
					p=root;
				//	printf("\n");
				}
				else
				{
					temp_value=temp_value*10+buffer[j];
				//	printf("%c",buffer[j]+'0');
				}
			}
			else
			{
				if(buffer[j]=='k')
				{
					eat_k=true;
					temp_value=0;
				//	printf("\n");
				}
				else
				{
					if(!p->next[buffer[j]])
						p->next[buffer[j]]=new node();
					p=p->next[buffer[j]];
				//	printf("%c",buffer[j]+'a');
				}

			}
		}
	}
	fclose(fp);
	//printf("%lld",line);
}
void edit(char **b)
{
	for(int q=0;q<=i+1;q++)
		for(int x=0;x<20;x++) 
			{
				char **a=new char * [7];
				for(int y=0;y<q;y++)
					a[y]=b[y];
				a[q]=prep[x];
				for(int y=q+1;y<=i+1;y++)
					a[y]=b[y-1];
				a[i+2]=NULL;				
				unsigned int num=lookup_matrix(a);
				if(num)
				{
					total++;
					queue1.push({num,a});
				}
			}
}
void edit_cone(char** kfc,int bool_num,int index,node * instant_place,int instant_amount,bool first);
void subsitute(char** &kfc,int &bool_num,int &index,node * &instant_place,int &instant_amount,bool first){
		bool error=0;
		bool original_first=first;
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back;jj++)//didn't debug
			for(int qq=0;qq<20;qq++)
				if(prep[qq]!=matrix[jj])
				{
					first=original_first;
					char ** tp = new char * [11];
					for(int gg=0;gg<instant_amount;gg++)
						tp[gg]=kfc[gg];
					node * temp_place =instant_place;
					for(int ip=index;ip<=map_bo[bool_num].back;ip++)
					{
						if(!first)
						{
							if(temp_place->next[26])
								temp_place=temp_place->next[26];
							else
							{
								error=1;
								break;
							}
						}
						else first=0;
						char * temp;
						if(ip!=jj)
							temp=matrix[ip];
						else
							temp=prep[qq];
						for(int var=0;var<strlen(temp);var++)
							if(temp_place->next[temp[var]-'a'])
								temp_place=temp_place->next[temp[var]-'a'];
							else
								{
									error=1;
									break;
								}
						tp[ip-index+instant_amount]=temp;
						if(error)
							break;	
					}
				tp[instant_amount+minus]=NULL;
				if(!error)
					edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,temp_place,instant_amount+minus,first);
				error = 0;
				}
}
void origin_a(char** &kfc,int &bool_num,int &index,node * &instant_place,int &instant_amount,bool first){
		bool error=0;
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		node * temp_place =instant_place;
		char ** tp = new char * [11];
		for(int gg=0;gg<instant_amount;gg++)
			tp[gg]=kfc[gg];
		for(int ip=index;ip<=map_bo[bool_num].back;ip++)
		{
			if(!first)
				{
					if(temp_place->next[26])
						temp_place=temp_place->next[26];
					else
						return;
				}
			else first=0;
			//printf("pass 02\n");

			char * temp=matrix[ip];
			for(int var=0;var<strlen(temp);var++)
				if(temp_place->next[temp[var]-'a'])
					temp_place=temp_place->next[temp[var]-'a'];
				else
						return;
			tp[ip-index+instant_amount]=temp;
			if(error)
				break;	
		}
		tp[instant_amount+minus]=NULL;
		edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,temp_place,instant_amount+minus,first);
		//delete(tp);
}
void insert_a(char** &kfc,int &bool_num,int &index,node * &instant_place,int &instant_amount,bool first){
		bool error=0;
		bool original_first=first;
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back+1;jj++)
			for(int qq=0;qq<20;qq++)
			{
				first=original_first;
				char ** tp = new char * [11];
				for(int gg=0;gg<instant_amount;gg++)
					tp[gg]=kfc[gg];
				node * temp_place =instant_place;
				

				for(int ip=index;ip<=map_bo[bool_num].back+1;ip++)
					{
						if(!first)
							{
								if(temp_place->next[26])
									temp_place=temp_place->next[26];
								else
								{
									error=1;
									break;
								}
							}
						else first=0;
						char * temp;
						if(ip<jj)
							temp=matrix[ip];
						else if(ip==jj){
							temp=prep[qq];
						}
						else 
							temp=matrix[ip-1];
						
						for(int var=0;var<strlen(temp);var++)
							if(temp_place->next[temp[var]-'a'])
								temp_place=temp_place->next[temp[var]-'a'];
							else
								{
									error=1;
									break;
								}
						tp[ip-index+instant_amount]=temp;
						if(error)
							break;					
					}
				tp[instant_amount+minus+1]=NULL;
				if(!error)
				edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,temp_place,instant_amount+minus+1,first);
				error=0;
				//delete(tp);
	}
}
void delete_a(char** &kfc,int &bool_num,int &index,node * &instant_place,int &instant_amount,bool first){
	bool error=0;
		//subsitute
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		bool original_first=first;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back;jj++)//didn't debug
			{
				first=original_first;
				char ** tp = new char * [11];
				for(int gg=0;gg<instant_amount;gg++)
					tp[gg]=kfc[gg];
				node * temp_place =instant_place;
				for(int ip=index;ip<=map_bo[bool_num].back;ip++)
					if(ip!=jj)
					{
						if(!first)
							{
								if(temp_place->next[26])
									temp_place=temp_place->next[26];
								else
								{
									error=1;
									break;
								}
							}
						else first=0;
						

						char * temp=matrix[ip];
						for(int var=0;var<strlen(temp);var++)
							if(temp_place->next[temp[var]-'a'])
								temp_place=temp_place->next[temp[var]-'a'];
							else
								{
									error=1;
									break;
								}
						if(ip<jj)
							tp[ip-index+instant_amount]=temp;
						else 
							tp[ip-index+instant_amount-1]=temp;
						if(error)
							break;					
					} 
				tp[instant_amount+minus-1]=NULL;
				if(!error)
				edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,temp_place,instant_amount+minus-1,first);
				error=0;
	}
}

int main(int argc, char* argv[])
{	
	input(argv[1]);
	char a;
	char temp[100];
	//i=0,j=0;
	ordinary_matrix	= new char *[11];
	for(int i=0;i<11;i++)
		ordinary_matrix[i]=new char[101];
	matrix = new char *[11];
	for(int i=0;i<11;i++)
		matrix[i]=ordinary_matrix[i];
	for(int i=0;i<20;i++)             //prep_trie
		{
			node * temp = root_prep;
			for(int j=0;j<strlen(prep[i]);j++)
				{
					if(!temp->next[prep[i][j]-'a'])
						temp->next[prep[i][j]-'a'] = new node();
					temp= temp->next[prep[i][j]-'a'];
					//printf("%c\n",prep[i][j]);
				}

			//printf("\n");
			temp->value=1;
		}
	i=j=0;
	while(a=getchar())
	{
		if(a==EOF)break;
		
		if(a==' ')
		{	
			if(i>=10)
			{		
				gets(temp);
				i=j=0; 
				for(int qaq=0;qaq<11;qaq++)
					matrix[qaq]=ordinary_matrix[qaq];
			}
	
			matrix[i][j]='\0';
			i++;
			j=0;
		}
		else if(a=='\n')
		{
			matrix[i][j]='\0';
			int prep_amount=0;
			bool is_prep[11]={};
			for(int q=0;q<=i;q++)
				for(int x=0;x<20;x++)
					if(strcmp(prep[x],matrix[q])==0) //use trie
						{
							prep_amount++;
							is_prep[q]=1;
							matrix[q]=prep[x];
							break;
						}
			//printf("%d\n",prep_amount); //need to take off
			if(prep_amount==0)
			{
				char **gg=new char *[7];
				for(int y=0;y<=i;y++)
					gg[y]=matrix[y];
				gg[i+1]=NULL;
				unsigned int num1=lookup_matrix(gg);
				if(num1)
				{
					queue1.push({num1,gg});
					total++;
				}
				
				if((i+1)<=4)
				for(int q=0;q<=i+1;q++)
					for(int x=0;x<20;x++)
						{
							
							
							char **qaq=new char *[7];
							for(int y=0;y<q;y++)
								qaq[y]=matrix[y];
							qaq[q]=prep[x];
							for(int y=q+1;y<=i+1;y++)
								qaq[y]=matrix[y-1];
							qaq[i+2]=NULL;
							unsigned int num = lookup_matrix(qaq);
							//printf("pass this\n"); //pass this
							if(num)
							{
								queue1.push({num,qaq});
								total++;
							}
							if((i+2)<=4)///5->4
							{
								i++;
								edit(qaq);
								i--;
							}	
						}
			}
			else
			{
				bool_map_num=0;
				bool pre_prep=0;
				for(int q=0;q<=i;q++)
				{
					if(is_prep[q]&&pre_prep==0)
						{
							map_bo[bool_map_num].front=q;
							map_bo[bool_map_num].back=q;
							pre_prep=1;
							//printf("fucking %d \n",q);
						}
					else if(is_prep[q])
						map_bo[bool_map_num].back++;
					else if(pre_prep)
						{
							pre_prep=0;
							bool_map_num++;
						}
					else
						pre_prep=0;

				}
				if(is_prep[i])
					bool_map_num++;
				//printf("%d %d\n",map_bo[0].front,map_bo[0].back);
				map_bo[bool_map_num].front=i+1;
				//for(int qq=0;qq<bool_map_num;qq++)
				//	printf("%d %d\n",map_bo[qq].front,map_bo[qq].back);
					//////////////////////////
				char **abab= new char*[11];
				
				edit_cone(abab,0,0,root,0,1);
			}
			printf("query:");
			for(int q=0;q<=i;q++)
				printf(" %s",matrix[q]);
			printf("\n");
			
			
			int newtotal=0;
			vector<data> temp_string;
			temp_string.clear();
			//printf("pass one\n");
			char ** temp_char= new char*[11];
			temp_char[0]=NULL;
			while(!queue1.empty()){
				bool yes =true;
				data temp_gg=queue1.top();
				char ** temp_ch=temp_gg.b;
				//printf("word :");///////
				//print(temp_ch);// test
				//printf("\n");////////
				while(*temp_ch)
					if(*temp_ch!=*temp_char)
					{
						//printf("%s %s\n",*temp_ch,*temp_char);
						//cout<<temp_ch<<" "<<temp_char<<endl;
						yes=0;
						break;

					}
					else if(*temp_char==NULL)
					{
					
						yes=0;
						break;
					}
					else 
					{
						temp_ch++;
						temp_char++;
					}
				if(*temp_char!=NULL)
					yes=0;

				if(!yes)
				{
					temp_string.push_back(temp_gg);
					newtotal++;
					temp_char= temp_gg.b;
				}	
				queue1.pop();
			}
			//printf("pass 2\n");
			
			if(newtotal<10)
			printf("output: %d\n",newtotal);
			else
			printf("output: 10\n");
			for(int qq=0;qq<temp_string.size();qq++)
			{
				if(qq==10)break;
				print(temp_string[qq].b);
				printf("\t%d\n",temp_string[qq].a);
			}
			//printf("pass qq\n");
			i=j=total=0;
			for(int qaq= 0; qaq<11;qaq++)
			matrix[qaq]=ordinary_matrix[qaq];
		}
		else{
			matrix[i][j]=a;
			j++;
		}
		
	}
}
void edit_cone(char** kfc,int bool_num,int index,node * instant_place,int instant_amount,bool first)
//bool_num which range index: the index of the origin func  instant_amount : the local amount
{

	if(index>i)
		{
			kfc[instant_amount]=NULL;
			if(instant_place->value)
			{
				queue1.push({instant_place->value,kfc});
				total++;
			}
			return;
		}
	
	if((i+1-index)-(bool_map_num-bool_num)>(5-instant_amount))///////////////////
		return;

	for(int qq=index;qq<map_bo[bool_num].front;qq++)
		{
			if(!first)
				{
					if(instant_place->next[26])
					{
						instant_place=instant_place->next[26];
					}
				else
					return;
				}
			else
				first=0;
			//printf("%s",matrix[qq]);
			for(int qx=0;qx<strlen(matrix[qq]);qx++)
				{
				if(instant_place->next[matrix[qq][qx]-'a'])
					instant_place=instant_place->next[matrix[qq][qx]-'a'];
				else
					return;
				}
			kfc[instant_amount]=matrix[qq];
			instant_amount++;
			index++;
		}
	if(bool_map_num==bool_num) 
	{
		kfc[instant_amount]=NULL;
		if(instant_place->value)
		{
			queue1.push({instant_place->value,kfc});
			total++;
		}
		return;
	}
	else{
		subsitute(kfc,bool_num,index,instant_place,instant_amount,first);
		delete_a(kfc,bool_num,index,instant_place,instant_amount,first);
		insert_a(kfc,bool_num,index,instant_place,instant_amount,first);
		origin_a(kfc,bool_num,index,instant_place,instant_amount,first);
	}
}

