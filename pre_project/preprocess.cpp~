#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
unsigned int temp_value=100;
int i,j,total=0;
void input(char * write_path){
	printf("%s",write_path);
	
	FILE *fw;
	fw = fopen(write_path,"wb");
	for(int number=2;number<6;number++){
		FILE *fp;
		string path="/tmp2/dsa2016_project/";
		path+=char(number+'0');
		path+="gm.small.txt";
		
		if(fp = fopen(path.c_str(), "r"))
		printf("succes\n");
		char ch;
		char strange=char(26);
		int i=0;
		int buff_size=4096;
		char buffer[4096];
		bool tab_yes=false;
		while((ch = fgetc(fp))!=EOF)
		{
			
			if(ch=='\t')
				{
					buffer[i]='k';
					tab_yes=true;
					i++;
				}
			else if(ch=='\n')
			{
				buffer[i]='k';
				i++;
				tab_yes=false;
			}
			else if(tab_yes)
			{
				buffer[i]=ch-'0';
				i++;
			}
			else if(ch==' ')
			{
				buffer[i]=strange;
				i++;
			}
			else
			{
				buffer[i]=ch-'a';
				i++;
			}
			if(i==4096)
			{
				i=0;
				fwrite(buffer,1,sizeof(char)*buff_size,fw);
			}
		}
		fwrite(buffer,1,sizeof(char)*i,fw);
		fclose(fp);
	}
	fclose(fw);
}


int main(int argc, char* argv[])
{
		printf("hello\n");
		input(argv[1]);  
}
