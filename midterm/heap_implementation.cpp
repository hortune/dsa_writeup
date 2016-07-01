#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void swap(int &a,int&b)
{
	int t;
	t=a;
	a=b;
	b=t;
}
class heap 
{
	public:
		heap():size(0){};
		void add(int num){
			size++;
			_heap[size]=num;
			int temp_size=size;
			while(temp_size!=1)
			{
				int temp = _heap[temp_size/2];
				if(temp < _heap[temp_size])
				{
					_heap[temp_size/2]=_heap[temp_size];
					_heap[temp_size] = temp;
					temp_size/=2;
				}
				else 
					break;
			}
		}
		int top()
		{
			if(!empty())
			return _heap[1];
		}
		void remove_max()
		{
			if(!empty())
			{
				_heap[1]=_heap[size];
				size--;
				int index=1;
				int temp = index*2;
				while(temp <=size)
				{
					if((temp+1)<=size)
					{
						if(_heap[index]<_heap[temp])
						{
							if(_heap[temp]<_heap[temp+1])
								swap(_heap[index],_heap[temp+1]),index = temp+1;
							else
								swap(_heap[index],_heap[temp]),index = temp;
							
						}
						else if(_heap[index]<_heap[temp+1])
							swap(_heap[index],_heap[temp+1]),index=temp+1;
						else
							break;//let it bomb
					}
					else
					{
						if(_heap[index]<_heap[temp])
								swap(_heap[index],_heap[temp]),index=temp;
						else
							break;
					}
					temp=index*2;
							
						
				}
			}
		}
		bool empty()
		{
			return (size==0);
		}
	private:
		int size;
		int _heap[100]={};
};
int main()
{
	heap test;
	srand (time(NULL));
	for(int i=0;i<100;i++)
	{
		test.add(rand()%1000);
		//cout<<i<<endl;
	}
	while(!test.empty())
	{
		cout<<test.top()<<" ";
		test.remove_max();
		//cout<<test.empty()<<endl;
	}

}