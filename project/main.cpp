#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
size_t prime = 199999991;
char ** matrix;
char ** ordinary_matrix;
int * map;
char ** dictionary;
bool findthing = 0;
unsigned int num;
int i,j,total=0;
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
priority_queue<data,vector<data>,comp> queue1(cmp_max);
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
unsigned int hash_function(char ** str)
{
	unsigned int hash=0;
	bool first = 1; 
	for (char ** temp = str;*temp; temp++)
	{
		if (!first)
			hash = hash * 33 + ' ';
		else first = 0;
		for (char* temp2 = *temp; *temp2; temp2++)
		{
			hash = hash * 33 + *temp2;
		}
	}
	return hash%prime;
}
int hash_second(int input)
{
	int old = input;
	int hash=0;
	while(input)
	{
		hash+=11*hash+input%10;
		input/=10;
	}
	if (hash < 0)hash = -hash;
	//if(hash<0)printf("%d\n",hash);
	hash = hash%prime;
	if(hash==old)
		return hash-1;
	else
	return hash;

}
void find(int position, int stream,char**& aaa)
{
	bool first = 1;
	findthing = 0;
	//bool error=0;
	for (char ** temp = aaa; *temp; temp++)
	{
		if (!first)
		{
		        //printf("%c",dictionary[stream][position]);	
			if (dictionary[stream][position] != ' ')
				return;
		//	error=1;
			position++;
		}
		else first = 0;
		for (char* temp2 = *temp; *temp2; temp2++)
		{
		//	printf("%c",dictionary[stream][position]);
			if (*temp2 != dictionary[stream][position])
				return;
		//	error=1;
			position++;
		}
	}
	//if(error)return;
	findthing = 1;
	num = 0;
	position++; //jump the tab
	while (dictionary[stream][position] != '\n')
	{
		num = num * 10 + dictionary[stream][position] - '0';
		position++;
	}
}
bool search(int hash,char** str)
{
	int position = map[hash];
	//print(str);
	//printf("\n");
	//printf("%d %d\n",hash,position);
	if (!position)
		return 0;
	if (position < 167129902)
		find(position - 1, 0,str);
	else if (position < 540525629)
		find(position - 167129902, 1,str);
	else if (position < 860319560)
		find(position - 540525629, 2,str);
	else
		find(position - 860319560, 3,str);
	
	//printf("\n");
	if (findthing)
		return 1;
	else
			return search(hash_second(hash),str);
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
				findthing =0;
				
				if(search(hash_function(a),a))			 
				 	queue1.push({num,a});

			}
}
void edit_cone(char** kfc,int bool_num,int index,int instant_amount);
void subsitute(char** &kfc,int &bool_num,int &index,int &instant_amount){
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back;jj++)//didn't debug
			for(int qq=0;qq<20;qq++)
				if(prep[qq]!=matrix[jj])
				{
					char ** tp = new char * [12];
					for(int gg=0;gg<instant_amount;gg++)
						tp[gg]=kfc[gg];
					for(int ip=index;ip<=map_bo[bool_num].back;ip++)
					{
						char * temp;
						if(ip!=jj)
							temp=matrix[ip];
						else
							temp=prep[qq];
						tp[ip-index+instant_amount]=temp;
					}
					tp[instant_amount+minus]=NULL;
					edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,instant_amount+minus);
				}
}
void origin_a(char** &kfc,int &bool_num,int &index,int &instant_amount){
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		char ** tp = new char * [12];
		for(int gg=0;gg<instant_amount;gg++)
			tp[gg]=kfc[gg];
		for(int ip=index;ip<=map_bo[bool_num].back;ip++)
			tp[ip-index+instant_amount]=matrix[ip];
			
		tp[instant_amount+minus]=NULL;
		edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,instant_amount+minus);
		//delete(tp);
}
void insert_a(char** &kfc,int &bool_num,int &index,int &instant_amount){
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back+1;jj++)
			for(int qq=0;qq<20;qq++)
			{
				char ** tp = new char * [12];
				for(int gg=0;gg<instant_amount;gg++)
					tp[gg]=kfc[gg];

				for(int ip=index;ip<=map_bo[bool_num].back+1;ip++)
					{
						char * temp;
						if(ip<jj)
							temp=matrix[ip];
						else if(ip==jj){
							temp=prep[qq];
						}
						else 
							temp=matrix[ip-1];
						tp[ip-index+instant_amount]=temp;
					}
				tp[instant_amount+minus+1]=NULL;
				edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,instant_amount+minus+1);
			}
}
void delete_a(char** &kfc,int &bool_num,int &index,int &instant_amount){
		int minus=1-map_bo[bool_num].front+map_bo[bool_num].back;
		for(int jj=map_bo[bool_num].front;jj<=map_bo[bool_num].back;jj++)//didn't debug
			{
				char ** tp = new char * [12];
				for(int gg=0;gg<instant_amount;gg++)
					tp[gg]=kfc[gg];
				for(int ip=index;ip<=map_bo[bool_num].back;ip++)
					if(ip!=jj)
					{
						if(ip<jj)
							tp[ip-index+instant_amount]=matrix[ip];
						else 
							tp[ip-index+instant_amount-1]=matrix[ip];
					} 
				tp[instant_amount+minus-1]=NULL;
				edit_cone(tp,bool_num+1,map_bo[bool_num].back+1,instant_amount+minus-1);
	}
}

int main(int argc, const char *argv[])
{
	//const char *filepath = "/tmp/mmapped.bin";
	char path[50] = "/tmp2/dsa2016_project/*gm.small.txt";
	char temp[100];
	int fd = open(argv[1], O_RDONLY, (mode_t)0600);
	int fdic[4];
	struct stat fileInfo = { 0 };
	struct stat fileInfo1[4];
	fstat(fd, &fileInfo);
	map = (int*)mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
	dictionary = new char *[4];
	for (int i = 0; i < 4; i++)
	{
		fileInfo1[i] = { 0 };
		path[22] = char(i + 2 + '0');
		fdic[i] = open(path, O_RDONLY, (mode_t)0600);
		fstat(fdic[i], &fileInfo1[i]);
		dictionary[i] = (char*)mmap(0, fileInfo1[i].st_size, PROT_READ, MAP_SHARED, fdic[i], 0);
	}
	char a;
	ordinary_matrix = new char *[12];
	for (int i = 0; i < 12; i++)
		ordinary_matrix[i] = new char[101];
	matrix = new char *[12];
	for (int i = 0; i < 12; i++)
		matrix[i] = ordinary_matrix[i];
	i = j = 0;
	//////////////////////////////////////////



	while (a = getchar())
	{
		if (a == EOF)break;
		if (a == ' ')
		{
			if (i > 10)
			{
				gets(temp);
				i = j = 0;
				for (int qaq = 0; qaq<12; qaq++)
					matrix[qaq] = ordinary_matrix[qaq];
			}
			matrix[i][j] = '\0';
			i++;
			j = 0;
		}
		else if (a == '\n')
		{
			matrix[i][j] = '\0';
			matrix[i + 1] = NULL;
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

			if(prep_amount==0)
			{
				if(i<=4){
				char **gg=new char *[7];
				for(int y=0;y<=i;y++)
					gg[y]=matrix[y];
				gg[i+1]=NULL;
			
				int hash = hash_function(gg);
				findthing = 0;
				if(search(hash,matrix))
					queue1.push({num,gg});
				if((i+1)<=4)
				for(int q=0;q<=i+1;q++)
					for(int x=0;x<20;x++){
							char **qaq=new char *[7];
							for(int y=0;y<q;y++)
								qaq[y]=matrix[y];
							qaq[q]=prep[x];
							for(int y=q+1;y<=i+1;y++)
								qaq[y]=matrix[y-1];
							qaq[i+2]=NULL;
							findthing=0;
			
							hash = hash_function(qaq);
							if(search(hash,qaq))
								queue1.push({num,qaq});
							if((i+2)<=4)///5->4
							{
								i++;
								edit(qaq);
								i--;
							}	
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
				map_bo[bool_map_num].front=i+1;
				char **abab= new char*[12];
				edit_cone(abab,0,0,0);
			}


			printf("query:");
			for(int q=0;q<=i;q++)
				printf(" %s",matrix[q]);
			printf("\n");
			int newtotal=0;
			vector<data> temp_string;
			temp_string.clear();
			//printf("pass one\n");
			char ** temp_char= new char*[12];
			temp_char[0]=NULL;
			while(!queue1.empty()){
				bool yes =true;
				data temp_gg=queue1.top();
				char ** temp_ch=temp_gg.b;
				while(*temp_ch)
					if(*temp_ch!=*temp_char)
					{
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
			i=j=total=0;
			for(int qaq= 0; qaq<12;qaq++)
			matrix[qaq]=ordinary_matrix[qaq];
		}
		else {
			matrix[i][j] = a;
			j++;
		}
	}
	
	munmap(map, fileInfo.st_size);
    close(fd);
    
    return 0;
}

void edit_cone(char** kfc,int bool_num,int index,int instant_amount)
{
	if(index>i)
		{
			kfc[instant_amount]=NULL;
			findthing=0;
			//print(kfc);
			//printf("\n");
			if(search(hash_function(kfc),kfc))
				queue1.push({num,kfc});
			return;
		}
	
	if((i+1-index)-(bool_map_num-bool_num)>(5-instant_amount))///////////////////
		return;

	for(int qq=index;qq<map_bo[bool_num].front;qq++)
		{
			kfc[instant_amount]=matrix[qq];
			instant_amount++;
			index++;
		}
	
	if(bool_map_num==bool_num) 
	{
		findthing=0;
		kfc[instant_amount]=NULL;
		//print(kfc);
		//printf("\n");
		if(search(hash_function(kfc),kfc))
				queue1.push({num,kfc});
			return;
	}
	else{
		if((i+1-index)-(bool_map_num-bool_num)>(5-instant_amount))
			return;
		subsitute(kfc,bool_num,index,instant_amount);
		delete_a(kfc,bool_num,index,instant_amount);
		if((i+1-index)-(bool_map_num-bool_num)<=(4-instant_amount))
		insert_a(kfc,bool_num,index,instant_amount);
		origin_a(kfc,bool_num,index,instant_amount);
	}
}

