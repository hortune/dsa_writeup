#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef bool (*comp)(int&,int&);
struct node{
	int bid,client,action,price,sharecount;
};

vector <node> data;

bool cmp_max(int &a,int &b){
	if(data[a].price<data[b].price)
		return 1;
	if(data[a].price==data[b].price)
	{
		if(data[a].bid>data[b].bid)
			return 1;
	}
	return 0;
}
bool cmp_min(int &a,int &b){
	if(data[a].price>data[b].price)
		return 1;
	if(data[a].price==data[b].price)
	{
		if(data[a].bid>data[b].bid)
			return 1;
	}
	return 0;
}
bool cmp_for_cancel(node a, node b){
	if(a.bid<b.bid)
		return 1;
		return 0;
}
priority_queue<int, vector<int>,comp > maxheap(cmp_max); //buyheap
priority_queue<int, vector<int>,comp > minheap(cmp_min); //sellheap

int main()
{
	data.reserve(1000001);
	int index=0,transid=0;
	int bid,client,action,price,sharecount;
	while(scanf("%d%d%d%d%d",&bid,&client,&action,&price,&sharecount)!=EOF)
	{
		//printf("%d %d %d %d %d\n", bid,client,action,price,sharecount);
		switch(action)
		{
			case 0:			
			while(!minheap.empty()&&sharecount!=0)
			{
				//printf("i'm here \n");
				int i=minheap.top();
				if(data[i].sharecount==0)
					minheap.pop();//implement cancel
				else
				{
					if(data[i].price<=price)
					{
						if(data[i].sharecount>sharecount)
						{
							printf("%d\t%d\t%d\t%d\t%d\n",transid,client,data[i].client,data[i].price,sharecount);
							data[i].sharecount-=sharecount;
							sharecount = 0;
							transid++;
						}
						else
						{
							printf("%d\t%d\t%d\t%d\t%d\n",transid,client,data[i].client,data[i].price,data[i].sharecount);
							sharecount-=data[i].sharecount;
							minheap.pop();
							transid++;
						}
					}
					else break;
				}
			}
			if(sharecount != 0)
			{
				data[index]={bid,client,action,price,sharecount};
				maxheap.push(index);
				index++;
			}
			//printf("hello hortune\n");
			break;

			case 1:
			while(!maxheap.empty()&&sharecount!=0)
			{
		//		printf("i'm here \n");
				int i=maxheap.top();
				if(data[i].sharecount==0)
					maxheap.pop();//implement cancel
				else
				{
					if(data[i].price>=price)
					{
						if(data[i].sharecount>sharecount)
						{
							printf("%d\t%d\t%d\t%d\t%d\n",transid,data[i].client,client,price,sharecount);
							data[i].sharecount-=sharecount;
							sharecount = 0;
							transid++;
						}
						else
						{
							printf("%d\t%d\t%d\t%d\t%d\n",transid,data[i].client,client,price,data[i].sharecount);
							sharecount-=data[i].sharecount;
							maxheap.pop();
							transid++;
						}
					}
					else break;
				}
			}
			if(sharecount != 0)
			{
				data[index]={bid,client,action,price,sharecount};
				minheap.push(index);
				index++;
			}
			break;

			case 2:
			node temp;
			temp.bid=price;
			int i=lower_bound(data.begin(),data.begin()+index,temp,cmp_for_cancel)-data.begin();
			if(data[i].bid==price)
				data[i].sharecount=0;
			break;
		}
	}
	
}