#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
using namespace std;
int main()
{
	string str;
	stack <double> calc;
	double temp1,temp2;
	while(cin>>str)
	{
		switch(str[0])
		{
			case '*':
				temp1=calc.top();
				calc.pop();
				temp2=calc.top();
				calc.pop();
				calc.push(temp1*temp2);
				break;
			case '+':
				temp1=calc.top();
				calc.pop();
				temp2=calc.top();
				calc.pop();
				calc.push(temp1+temp2);
				break;
			case '/':
				temp1=calc.top();
				calc.pop();
				temp2=calc.top();
				calc.pop();
				calc.push(temp2/temp1);
				break;
			case '-':
				temp1=calc.top();
				calc.pop();
				temp2=calc.top();
				calc.pop();
				calc.push(temp2-temp1);
				break;
			default :
				calc.push((double)atoi(str.c_str()));
		}
		
	}
	cout<<calc.top();
}