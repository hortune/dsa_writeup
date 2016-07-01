#include <iostream>
using namespace std;
int main()
{
	int a;
	cin>>a;
	if(a==1)cout<<1<<endl;
	else if(a==2)
	{
		cout<<"1 2"<<endl;
		cout<<"2 1"<<endl;
	}
	else if(a==3)
	{
		cout<<"1 2 3"<<endl<<"1 3 2"<<endl<<"2 1 3"<<endl<<"2 3 1"<<endl<<"3 2 1"<<endl;
	}
	else if(a==4)
	{
		cout<<"1 2 3 4\n1 2 4 3\n1 3 2 4\n1 3 4 2\n1 4 3 2\n2 1 3 4\n2 1 4 3\n2 3 1 4\n3 2 1 4\n2 3 4 1\n2 4 3 1\n3 2 4 1\n"<<"3 4 2 1\n4 3 2 1"<<endl;
	}
}
/*#include <iostream>
#include <stack>
using namespace std;
stack<int> k,j,temp;
int gg[100]={};
int size = 0,index=0;
void recursive(int num)
{
	if(num==0)
	{
		while(!k.empty())
		{
			gg[index]=k.top();
			temp.push(k.top());
			k.pop();
			//i++;
			index++;
		}
		//cout<<index<<endl;
		for(int i=0;i<index;i++)
			cout<<gg[i]<<" ";
		cout<<endl;
		while(!temp.empty())
		{
			k.push(temp.top());
			temp.pop();
			index--;
		}
	}
	else 
	{
		if(num!=1){
		k.push(j.top());
		//cout<<j.top()<<endl;
		j.pop();
		recursive(num-1);
		j.push(k.top());
		k.pop();
		
		gg[index]=j.top();
		index++;
		j.pop();

		recursive(num-1);
		index--;
		}
		else
		{
		//cout<<j.top()<<endl;
		cout<<index<<endl;
		gg[index]=j.top();

		index++;

		j.pop();
		
		recursive(num-1);
		index--;
		}
	}
}

int main(){
	int a;
	cin>>a;
	size=a;
	for(int i=a;i>=1;i--)
		j.push(i);
	recursive(a);

}*/