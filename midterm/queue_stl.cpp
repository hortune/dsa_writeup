#include <iostream>
#include <queue>
using namespace std;
int main()
{
	queue<int > q;
	for(int i=0;i<100;i++)
		q.push(i);

	cout<<q.front()<<" "<<q.back()<<endl;
	q.pop();
	cout<<q.front()<<" "<<q.back()<<endl;
}