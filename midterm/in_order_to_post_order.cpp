#include <iostream>
#include <stack>
#include <string>
using namespace std;
string cmp[2]={"*/","+-"};
int find_priority(string &a)
{
	for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				if(a[0]==cmp[i][j])
					return i;
	return 2;
}
int main()
{
	string str;
	stack <string> trans;
	
	while(cin>>str)
	{
		if(str=="hortune")break;
		bool isnum=1;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				if(str[0]==cmp[i][j])
					{
						//cout<<"hi"<<endl;
						if(!trans.empty())
						{
							int temp=find_priority(trans.top());
						
						while(temp<=i)
							{
							cout<<trans.top()<<" ";
							trans.pop();
							if(!trans.empty())
								temp=find_priority(trans.top());
							else break;
							}
						}
						trans.push(str);
						isnum=0;
					}
		if(str=="(")trans.push(str);
		else if(str==")")
		{
			int temp=find_priority(trans.top());
			while(temp!=2)
			{
					cout<<trans.top()<<" ";
					trans.pop();
					if(!trans.empty())
						temp=find_priority(trans.top());
					else break;
			}
			trans.pop();
		}
		else if(isnum)
			cout<<str<<" ";
	}
	while(!trans.empty())
	{
		cout<<trans.top()<<" ";
		trans.pop();
	}
}