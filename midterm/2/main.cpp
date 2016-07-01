/*#include <iostream>
#include <stack>
using namespace std;
stack<int> k,j;

void recursive(int num)
{
	if(num==0)
	{
		for(int i=0;i<12;i++)
			cout<<vec[i]<<" ";
		cout<<endl;
	}
	else
	{

		recursive(num-1);
		k.push(j.top());
		j.pop();
		recursive(num-1);
		j.push(k.top());
		k.pop();
	}
}

int main(){

}*/

#include <iostream>
using namespace std;
int a[1000],index=0;
void preorder(int num)
{
	if(num<index)
	{
		if(a[num]!=-1)
	 	{
	 		cout<<a[num]<<" ";
	 		preorder(2*num);
	 		preorder(2*num+1);
	 	}
	}
}
void inorder(int num)
{
	if(num<index)
	{
		if(a[num]!=-1)
	 	{
	 		
	 		inorder(2*num);
	 		cout<<a[num]<<" ";
	 		inorder(2*num+1);
	 	}
	}
}

void postorder(int num)
{
	if(num<index)
	{
		if(a[num]!=-1)
	 	{
	 		
	 		postorder(2*num);
	 		
	 		postorder(2*num+1);
	 		cout<<a[num]<<" ";
	 	}
	}
}
int main()
{
	int b;
	while(cin>>a[index])
	{
		index++;
	}
	preorder(1);
	cout<<endl;
	inorder(1);
	cout<<endl;
	postorder(1);
	cout<<endl;
}