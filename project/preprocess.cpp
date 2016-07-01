#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
size_t prime = 199999991;
int * mappi;
int position=1;
bool print = 0; ////.
int hash_function(int input)
{
	int hash=0;
	while(input)
	{
		hash+=11*hash+input%10;
		input/=10;
	}
	if (hash < 0)hash = -hash;
	//if(hash<0)printf("%d\n",hash);
	return hash%prime;

}

void collision(int hash)
{
	hash=hash_function(hash);
//	if(print)
//		printf("%d %d\n",hash,mappi[hash]);
	if(!mappi[hash])
		mappi[hash]=position;
	else
		collision(hash);
}
int main(int argc, const char *argv[])
{
//    const char *filepath = "/tmp/mmapped.bin";

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    size_t textsize = prime*8 + 1; // + \0 null character
    
    lseek(fd, textsize+1, SEEK_SET);
    //
    mappi=(int *)mmap(0, textsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    write(fd," ",sizeof(mappi)+1);
    int temp_position=1;
    for(int number=2;number<6;number++){
        FILE *fp;
       	char path[50]="/tmp2/dsa2016_project/*gm.small.txt";
        path[22]=char(number+'0');
        //printf("%s\n",path);
	fp = fopen(path, "r");
	char ch;
        bool tab_yes=false;
	//printf("%d\n",temp_position);
        unsigned int hash=0;
            while((ch = fgetc(fp))!=EOF)
            {
		if(ch=='\t')
               	{
		    hash = hash%prime;
		
		  //  {
		//	    printf("%u\n",hash);
		    //	    print =1;
		   // }
//	            if(hash == 8503276)
//		    {
//			    printf("hash: %d\n",hash);
//			    printf("position : %d\n",position);
//			    printf("mappi :%d\n",mappi[hash]);
//			    printf("good\n");
//		    	    print=1;
		    
		    
//		    }
		    if(!mappi[hash])
			    mappi[hash]=position;
		    else
			{
			 	collision(hash);
			}
//		    print =0;
		    tab_yes=true;
		}
            	else if(ch=='\n')
            	{
                	tab_yes=false;
                	hash=0;
			position =temp_position+1;
	    	}
            	else if(tab_yes)
            	{
	
            	}
            	else
            	{
                	hash = hash*33+ch;
            	}
	    	temp_position++;
        	if(temp_position<0)
		{
			printf("asshole!\n");
			break;
		}
	    }
	//if(position==temp_position)
		//printf("yes\n");
        fclose(fp);
    }
   // printf("is me?\n");
    msync(mappi, textsize, MS_SYNC);
    close(fd);
    return 0;
}
