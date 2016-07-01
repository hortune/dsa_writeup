#include <iostream>
#include <string>
using namespace std;
int queue[100]={},front =0,end=0,size=100;
void increase(int &num)
{
	num++;
	if(num==size)
		num=0;
}
void decrease(int &num)
{
	num--;
	if(num<0)
		num=size-1;
}

void push(int a)
{
	if(front == end)
	{
		queue[front]= a;
		increase(end);
	}
	else
	{
		decrease(front);
		queue[front]= a;
	}
}
int pop()
{
	decrease(end);
	return queue[end];
}
void show()
{
	int temp_front=front, temp_end=end;
	while(temp_front!=temp_end)
	{
		cout<<queue[temp_front]<<" ";
		increase(temp_front);
	}
	cout<<endl;
}
int main()
{
	string a;
	int b;
	while(cin>>a)
	{
		if(a=="push")
			{
				cin>>b;
				push(b);
			}
		else if(a=="pop")
		{
			pop();
		}
		else if(a=="show")
		{
			show();
		}
	}

}