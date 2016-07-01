#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
double min(const double & a,const double &b)
{
	if(a>b)
		return b;
		return a;
}
int min(const int & a, const int &b)
{
	if(a>b)
		return b;
	return a;
}

int main(){
	int m,n;
	scanf("%d",&m);
	double *pitch = new double[m];
	//printf("hello");
	for(int i=0;i<m;i++)
		scanf("%lf",&pitch[i]);
	//sort(pitch+1,pitch+m+1);
	scanf("%d",&n);
	double *node = new double[n];
	for(int j=0;j<n;j++)
		scanf("%lf",&node[j]);
	
	double ** dp = new double *[m];
	for(int i=0;i<m;i++)
		dp[i]=new double[n];
	//printf("hello");
	

	dp[0][0]=abs(pitch[0]-node[0]);
	for(int j=1;j<n;j++)
		dp[0][j]=dp[0][j-1];
	for(int i=1;i<m;i++)
		dp[i][0]=dp[i-1][0]+abs(pitch[i]-node[0]);
	

	for(int k=1;k<n;k++)
		dp[k][k]=dp[k-1][k-1]+abs(pitch[k]-node[k]);
	vector<int> temp;
	vector<vector<int>> answer;
	answer.reserve(n);

	for(int i=0;i<n;i++){
		temp.push_back(i);
		answer.push_back(temp);
	}
	stack<int> emp;
	for(int i=2;i<m;i++){
		for(int j=1;j<min(i,n);j++)
			{
				if(dp[i-1][j]>=dp[i-1][j-1])
					emp.push(j);
				dp[i][j]=abs(pitch[i]-node[j])+min(dp[i-1][j],dp[i-1][j-1]);
			}
		while(!emp.empty())
		{
			int a=emp.top();
			answer[a]=answer[a-1];
			answer[a].push_back(i);
			emp.pop();
		}
	}
	double max = dp[m-1][0];
	int index=0;
	for(int j=1;j<n;j++)
		if(max>dp[m-1][j])
			{
				max=dp[m-1][j];
				index=j;
			}
	printf("%lf\n",max);
	for(int i=0;i<answer[index].size();i++)
		printf("%d ",answer[index][i]);
}