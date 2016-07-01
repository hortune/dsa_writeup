#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
int rec = 0;
int nanogram[100][100] = {};
vector <int> row[100];
vector <int> coluum[100];
int test_row[100] = {}, test_coluum[100] = {};
bool manipulat[100] = {};
int m, n;
int tmpi, tmpj;
void letitbenum(int *a, int* b, int num)// [a,b]
{
	*b = num;
	while (a != b)
	{
		*a = num;
		a++;
	}
}
void letitbenum(bool *a, bool* b, bool num)// [a,b]
{
	*b = num;
	while (a != b)
	{
		*a = num;
		a++;
	}
}
void input(int qaq, vector<int>* vec)//ok
{
	for (int i = 0; i<qaq; i++)
	{
		char cha;
		int num = 0;
		bool last_zero=true;
		while (cin.get(cha))
		{
			//cout<<cha<<endl;// test
			if (cha == '\n' || cha == ' ')
			{
				if (!last_zero)
					vec[i].push_back(num);
				num = 0;
				last_zero = true;
				if (cha == '\n')
					break;
			}
			else if (cha == EOF )
				break;
			else
			{
				num = num * 10 + (cha - '0');
				last_zero = false;
			}
		}

	}
}
bool test()//just a test
{
	for (int i = 0; i<m; i++)
		for (int j = 0; j<n; j++)
			if (nanogram[i][j] == 0)
			{
				tmpi = i;
				tmpj = j; // record thats reverse place
				return false;
			}
	return true;
}
bool final_test_row(int i)
{
	
		bool last_zero = 1;
		int te = 0, tete = 0;
		for (int j = 0; j < n; j++)
		{
			if (nanogram[i][j]>0)
			{
				tete++;
				last_zero = 0;
			}
			else 
			{
				if (!last_zero)
				{
					if (row[i].size() == te)
						return false;
					if (row[i][te] != tete)
						return 0;
					tete = 0;
					te++;
				}

				last_zero = 1;
			}

		}
		if (!last_zero){
		
			if (row[i].size() == te)
				return false;
			if (row[i][te] != tete)
				return 0;
			tete = 0;
			te++;
		}
		if (te != row[i].size())
			return 0;
		return 1;
}
bool final_test_coluum(int j)
{
		bool last_zero = 1;
		int te = 0, tete = 0;
		for (int i = 0; i < m; i++)
		{
			if (nanogram[i][j]>0)
			{
				tete++;
				last_zero = 0;
			}
			else
			{
				if (!last_zero)
				{
					if (coluum[j].size() == te)
						return false;
					if (coluum[j][te] != tete)
						return false;
					tete = 0;
					te++;
				}

				last_zero = 1;
			}
		}
		if (!last_zero)
		{
			if (coluum[j].size() == te)
				return false;
			if (coluum[j][te] != tete)
				return false;
			tete = 0;
			te++;
		}
		if (te != coluum[j].size())
			return false;
		return true;
}
bool final_test()
{
	for (int i = 0; i < m; i++)
	{
		bool last_zero = 1;
		int te = 0, tete = 0;
		for (int j = 0; j < n; j++)
		{
			if (nanogram[i][j]>0)
			{
				tete++;
				last_zero = 0;
			}
			else
			{
				if (!last_zero)
				{
					if (row[i].size() == te)
						return false;
					if (row[i][te] != tete)
						return false;
					tete = 0;
					te++;
				}

				last_zero = 1;
			}
			
		}
		if (!last_zero)
		{
			if (row[i].size() == te)
				return false;
			if (row[i][te] != tete)
				return false;
			tete = 0;
			te++;
		}
		if (te != row[i].size())
			return false;
	}
	for (int j = 0; j < n; j++)
	{
		bool last_zero = 1;
		int te = 0, tete = 0;
		for (int i = 0; i < m; i++)
		{
			if (nanogram[i][j]>0)
			{
				tete++;
				last_zero = 0;
			}
			else
			{
				if (!last_zero)
				{   
					if (coluum[j].size() == te)
						return false;
					if (coluum[j][te] != tete)
						return false;
					tete = 0;
					te++;
				}

				last_zero = 1;
			}
		}
		if (!last_zero)
			{
				if (coluum[j].size() == te)
					return false;
				if (coluum[j][te] != tete)
					return false;
				tete = 0;
				te++;
			}
		if (te != coluum[j].size())
			return false;
	}
	return true;
}
void erase_full_map(int assume)//erase assumption
{
	bool first = true;
	for (int i = 0; i<m; i++)
		for (int j = 0; j<n; j++)
			if ((nanogram[i][j] >= assume) || (nanogram[i][j] <=(-assume)))
			{
				if (first)
				{
					first = false;
					tmpi = i;
					tmpj = j;
				}
				nanogram[i][j] = 0;
			}
}
int dfs_filling_blanks_row(int i, int num, int next_fill, int assume)//may need to change for assumption
{
	int n_fake = n;
	if (num == row[i].size())
	{
		for (int q = next_fill; q<n; q++)//make sure that no more 1 at back
			if (nanogram[i][q]>0)
				return 0;
		for (int q = 0; q<n; q++)
			test_row[q] += manipulat[q];
		return 1;
	}
	// if next_fill is bigger than n that means contridiction
	if (next_fill >= n)
		return 0;
	int sum = 0;
	//n_fake = n;
	while ((next_fill + row[i][num]) <= n_fake)//hasn't consider the nono fact
	{
		bool contridiction = 0;
		int index;
		for (index = next_fill; index<next_fill + row[i][num]; index++)//prevent -1 to 1
			if (nanogram[i][index]<0)
			{
				next_fill = index + 1;
				contridiction = 1;
				break;
			}
			else if (nanogram[i][index]>0)
			{
				n_fake = min(index + row[i][num], n_fake);
			}
		if (contridiction) continue;

		if ((next_fill + row[i][num]<n_fake) && nanogram[i][next_fill + row[i][num]] > 0)//if the blank is 1 ,makesure it won't boom out
		{
			n_fake = min(next_fill + 2 * row[i][num], n_fake);
			next_fill++;
			continue;
		}
		if ((next_fill + row[i][num]) <= n_fake) {
			letitbenum(manipulat + next_fill, manipulat + next_fill + row[i][num] - 1, 1);
			sum += dfs_filling_blanks_row(i, num + 1, next_fill + row[i][num] + 1, assume);//+1 need for blank	
			letitbenum(manipulat + next_fill, manipulat + next_fill + row[i][num] - 1, 0);
		}
		next_fill++;
	}

	return sum;
}
int dfs_filling_blanks_coluum(int j, int num, int next_fill, int assume)//may need to change for assumption
{
	//cout << j << " " << num << " "<<next_fill<<" " << assume << endl;
	int m_fake = m; 
	if (num == coluum[j].size())
	{
		for (int q = next_fill; q<m; q++)//make sure that no more 1 at back
			if (nanogram[q][j]>0)
				return 0;
		for (int q = 0; q<m; q++)
			test_coluum[q] += manipulat[q];
		return 1;
	}
	// if next_fill is bigger than n that means contridiction
	if (next_fill >= m)
		return 0;
	int sum = 0;
	// m_fake = m;
	while ((next_fill + coluum[j][num]) <= m_fake)//hasn't consider the nono fact
	{
		bool contridiction = 0;
		int index;
		for (index = next_fill; index<next_fill + coluum[j][num]; index++)//prevent -1 to 1
			if (nanogram[index][j]<0)
			{
				next_fill = index + 1;
				contridiction = 1;
				break;
			}
			else if (nanogram[index][j]>0)
			{
				m_fake = min(index + coluum[j][num], m_fake);
				
			}
		if (contridiction) continue;

		if ((next_fill + coluum[j][num]<m_fake) && nanogram[next_fill + coluum[j][num]][j] > 0)//if the blank is 1 ,makesure it won't boom out
		{
			m_fake = min(next_fill + 2 * coluum[j][num], m_fake);
			next_fill++;
			continue;
		}
		if ((next_fill + coluum[j][num]) <= m_fake) {
			letitbenum(manipulat + next_fill, manipulat + next_fill + coluum[j][num] - 1, 1);
			sum += dfs_filling_blanks_coluum(j, num + 1, next_fill + coluum[j][num] + 1, assume);//+1 need for blank	
			letitbenum(manipulat + next_fill, manipulat + next_fill + coluum[j][num] - 1, 0);
		}next_fill++;
	}

	return sum;
}

bool dfs(int index_i, int index_j, int assume)
{

	while (1)
	{
		//cout<<1<<endl;
		int newstuff = 0;
		//bool contridiction = false;
		for (int i = 0; i<m; i++)
			if (final_test_row(i))
				for (int j = 0; j < n; j++)
				{
					if (nanogram[i][j] == 0)
					{
						nanogram[i][j] = -assume;
						newstuff++;
					}
				}
			else {
				letitbenum(test_row, test_row + n - 1, 0);
				letitbenum(manipulat, manipulat + n - 1, 0);
				int times = 0;
				times = dfs_filling_blanks_row(i, 0, 0, assume);
				if (times)
				{
					for (int j = 0; j < n; j++)
						if (test_row[j] == times && nanogram[i][j] == 0)
						{
							nanogram[i][j] = assume;
							newstuff++;
						}
						else if (test_row[j] == 0 && nanogram[i][j] == 0)
						{
							nanogram[i][j] = -assume;
							newstuff++;
						}
				}
			}
	
	
			
			for (int j = 0; j < n; j++)
				if (final_test_coluum(j))
					for (int i = 0; i < m; i++)
					{
						if (nanogram[i][j] == 0)
						{
							nanogram[i][j] = -assume;
							newstuff++;
						}
					}
			else
			{

				letitbenum(test_coluum, test_coluum + m - 1, 0);
				letitbenum(manipulat, manipulat + m - 1, 0);
				int times = 0;
				times = dfs_filling_blanks_coluum(j, 0, 0, assume);
				if (times)
				{
					for (int i = 0; i<n; i++)
						if (test_coluum[i] == times && nanogram[i][j] == 0)
						{
							nanogram[i][j] = assume;
							newstuff++;
						}
						else if (test_coluum[i] == 0 && nanogram[i][j] == 0)
						{
							nanogram[i][j] = -assume;
							newstuff++;
						}
				}
			}
		/*if (contridiction)
		{
			if (nanogram[index_i][index_j] == -assume)
			{
				erase_full_map(assume);
				return false;
			}
			nanogram[index_i][index_j] = -assume;
		}
		else 
		*/
		if (!newstuff)
		{
			if (test())
			{
				if (final_test())
					return true;
				erase_full_map(assume);
				return false;
			}
			assume++;
			nanogram[tmpi][tmpj] = assume;
			if (!dfs(tmpi, tmpj, assume))
			{
				erase_full_map(assume);
				nanogram[tmpi][tmpj] = -assume;
			
				return dfs(tmpi, tmpj, assume);
			}
			else return true;
		}
	}
}
int main()
{
	cin >> m >> n;
	cin.ignore();
	//cout<<m<<" "<<n<<endl;
	input(m, row);
	input(n, coluum);//input done
	//ofstream output;
	//cout.open("out.txt");
	dfs(0, 0, 1);
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j < n; j++)
			if (nanogram[i][j]>0)
				cout << "#";
			else
				cout <<".";
		//if(i!=(m-1))
		cout << endl;
	}
	//cout.close();
}

/*
想辦法判斷
contridiction

*/
