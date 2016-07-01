#include <iostream>
using namespace std;
int array[100]={6,1,3,4,5,1,2,3,4,5,2,3};
void quicksort(int front,int end)
{
	
	int a=front+1,b=end;
	if(front<end)
	{
		do
		{
			while(array[front]>=array[a])
				{
					a++;
					if(a==(end+1))
						break;
			}
			while(array[front]<array[b])
				b--;
			if(a<b)
				swap(array[a],array[b]);
		}while(a<b&&a<=end&&b>front);
		swap(array[front],array[b])	;
			quicksort(front,b-1);
			quicksort(b+1,end);
	}
}
int main()
{
	
	quicksort(0,11);
	for(int i=0;i<12;i++)
		cout<<array[i]<<" ";
	cout<<endl;
}
