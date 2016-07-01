#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;
int total_userId = 0;
const int length = 73209277;
map<int, int > thres;
struct _data
{
	int userid, itemid, time;
	short result;
};
struct _item
{
	int itemid, first, last;
};
vector <int> userid;
vector<_data> stru;//預先跑過
vector<_item> item;
bool cmp(_data d1, _data d2)
{
	if (d1.itemid < d2.itemid)
		return true;
	else if (d1.itemid>d2.itemid)
		return false;
	else
	{
		if (d1.userid < d2.userid)
			return true;
		else if (d1.userid >d2.userid)
			return false;
		else
		{
			if (d1.time < d2.time)
				return true;
			else
				return false;
		}
	}
}//cmp for initial data
bool cmp_method(_data d1, _data d2)
{
	if (d1.itemid < d2.itemid)
		return true;
	else
		return false;
}//cmp for finding bound
bool cmp_method_1(_data d1, _data d2)
{
	if (d1.userid < d2.userid)
		return true;
	else
		return false;
}
bool cmp_for_find(_data d1, _data d2)
{
	if (d1.time < d2.time)
		return true;
	else
		return false;
}
bool equal(_data &a, _data &b)
{
	if (a.userid == b.userid)
		if (a.itemid == b.itemid)
			if (a.result == b.result)
				if (a.time == b.time)
					return true;
	return false;
}
void accept(int u, int i, int t);
void items(int u1, int u2);

void users(int i1, int i2, int t1, int t2);
void ratio(int i, int threshold);
void findtime_item(int i);
int main()
{
	double START = clock();
	userid.reserve(1392873);
	item.reserve(4710);
	stru.reserve(length);
	_data tmp;
	string str;
	int i = 0, k = 0, k_first = 0, tmpt[4] = {},j=0;
		FILE *fp;
		fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "r");
		int integer = 0;
		char ch;
		bool last_blank = 0;
		while ((ch = fgetc(fp)) != EOF) {
			if (ch == '\n') {
				stru[i].userid = tmpt[0];
				stru[i].itemid = tmpt[1];
				stru[i].result = tmpt[2];
				stru[i].time = integer;
				if (thres.end() == thres.find(stru[i].userid))
				{
					thres[stru[i].userid] = total_userId;
					userid[total_userId] = 1;
					total_userId++;
				}
				else
					userid[thres[stru[i].userid]]++;
				integer = 0;
				i++;
				j = 0;
			}
			else if (isdigit(ch)) {
				integer = integer * 10 + (ch - '0');
				last_blank = 0;
			}
			else if (ch == '-')
			{
				integer = -1;
				ch = fgetc(fp);
				last_blank = 0;
			}
			else if (last_blank == 0) {
				tmpt[j] = integer;
				j++;
				integer = 0;
				last_blank = 1;
			}
		}
	
	fclose(fp);
		sort(stru.begin(), stru.begin() + length, cmp);
		
		
	for (i = 0; i < 4710; i++)
	{
		tmp = { 0,stru[k_first].itemid ,0,0 };
		k = upper_bound(stru.begin() + k, stru.begin() + length, tmp, cmp_method) - stru.begin();
		item[i] = { stru[k - 1].itemid,k_first,k };
		k_first = k;
	}
	tmpt[0] = tmpt[1] = tmpt[2] = tmpt[3] = 0;
	for (i = 0; i < length; ++i)
	{
		if (tmpt[0] == stru[i].userid&&tmpt[1] == stru[i].itemid&&tmpt[2] == stru[i].result&&stru[i].time == tmpt[3])
		{
			userid[thres[tmpt[0]]]--;
		}
		tmpt[0] = stru[i].userid;
		tmpt[1] = stru[i].itemid;
		tmpt[2] = stru[i].result;
		tmpt[3] = stru[i].time;
	}
	for (map<int, int>::iterator it = thres.begin(); it != thres.end(); ++it)
		it->second = userid[it->second];
	sort(userid.begin(), userid.begin() + 1392873);
	int a, b, c;
	int times;
	cin >> times;
	while (times--)
	{
		cin >> str;
		if (str == "accept")
		{
			cin >> a >> b >> c;
			accept(a, b, c);
		}
		else if (str == "items")
		{
			cin >> a >> b;
			items(a, b);
		}
		else if (str == "users")
		{
			cin >> a >> b >> c >> j;
			users(a, b, c, j);
		}
		else if (str == "ratio")
		{
			cin >> a >> b;
			ratio(a, b);
		}
		else
		{
			cin >> i;
			findtime_item(i);
		}
	}
	
	return 0;
}
//O(log n) 確定ok good
void accept(int u, int i, int t)
{
	_data date = { u,i,t ,(short)-1 };
	_data date1 = { u,i,t ,(short)1 };
	int gg = lower_bound(stru.begin(), stru.begin() + 73209277, date, cmp) - stru.begin();
	if (equal(date, stru[gg]))
		cout << -1 << endl;
	else if (equal(date1, stru[gg]))
		cout << 1 << endl;
	else
		cout << 0 << endl;
}
//O(logn ) 確定ok 應該 good
void items(int u1, int u2)
{
	_data u1_1, u2_1;
	bool empty = true;

	for (int i = 0; i < 4710; i++)
	{
		u1_1 = { u1,item[i].itemid,0,0 };
		u2_1 = { u2,item[i].itemid,0,0 };
		int cmp_1 = lower_bound(stru.begin() + item[i].first, stru.begin() + item[i].last, u1_1, cmp_method_1) - stru.begin();
		int cmp_2 = lower_bound(stru.begin() + item[i].first, stru.begin() + item[i].last, u2_1, cmp_method_1) - stru.begin();
		if (stru[cmp_1].userid == u1&&stru[cmp_2].userid == u2)
		{
			empty = false;
			cout << item[i].itemid << endl;
		}
	}
	if (empty)
		cout << "EMPTY" << endl;
	//cout << endl;
}
//O(m+n)   確定ok 應該 [t1,t2] good
void users(int i1, int i2, int t1, int t2)
{
	bool empty = true;
	int first, first1, last, last1;
	for (int j = 0; j < 4710; j++)
		if (item[j].itemid == i1)
		{
			first = item[j].first;
			last = item[j].last;
			break;
		}
	for (int j = 0; j < 4710; j++)
		if (item[j].itemid == i2)
		{
			first1 = item[j].first;
			last1 = item[j].last;
			break;
		}
	int tmp = 0;
	while (1)
	{
		if (stru[first].time <= t2&&stru[first].time >= t1)
		{
			if (stru[first1].time <= t2&&stru[first1].time >= t1)
			{
				if (stru[first].userid == stru[first1].userid)
				{
					if (tmp != stru[first].userid)
						cout << stru[first].userid << endl;
					tmp = stru[first].userid;
					first++;
					first1++;
					empty = false;
				}
				else if (stru[first].userid > stru[first1].userid)
				{
					first1++;
				}
				else
					first++;
			}
			else
				first1++;
		}
		else
		{
			first++;
		}
		if (first == last || first1 == last1)
			break;
	}
	if (empty)cout << "EMPTY" << endl;
	//cout << endl;
}
//O(logn+n/4710) >threshold not sure can run 找人程式 核對 確定掰了
void ratio(int i, int threshold)
{
	int total, ans = 0, first, last, tmpid = 0;
	for (int j = 0; j < 4710; j++)
		if (item[j].itemid == i)
		{
			first = item[j].first;
			last = item[j].last;
			break;
		}
	/// 
	total = 1392873 + userid.begin() - lower_bound(userid.begin(), userid.begin() + 1392873, (threshold + 1));
	///
	for (; first < last; first++)
		if (stru[first].result==1&&tmpid != stru[first].userid&&thres[stru[first].userid]>threshold)
		{
			ans++;
			tmpid = stru[first].userid;
		}
	cout << ans << "/" << total << endl;
}
void findtime_item(int i)//qaq 可以了
{
	bool empty = true;
	string str;
	int u, last = 0,j;
	map<int, bool >mymap;
	cin.ignore();
	getline(cin, str);
	int integer=0;
	bool last_blank =0;
	for (int index = 0; index < str.size(); ++index)
	{
		if (isdigit(str[index])) {
			integer = integer * 10 + (str[index] - '0');
			last_blank = 0;
		}
		else if (last_blank == 0) {
			mymap[integer]=true;
			integer = 0;
			last_blank = 1;
		}
	}
	if (integer)
		mymap[integer] = true;
	for (j = 0; j < 4710; ++j)
		if (item[j].itemid == i)
			break;
	i = j;
	sort(stru.begin() + item[i].first, stru.begin() + item[i].last, cmp_for_find);
	for (int j = item[i].first; j < item[i].last; j++)
		if (mymap[stru[j].userid] && last != stru[j].time)
		{
			empty = 0;
			cout << stru[j].time <<endl;
			last = stru[j].time;//改過

		}
	if (empty)cout << "EMPTY" << endl;
	sort(stru.begin() + item[i].first, stru.begin() + item[i].last, cmp);
}
//單一user most amount 8375857
// userid 數量 1392873
// item  amount 4710 
//solo user pid num id 14456
// accept O(logn)
// items O(m+n)
// 紀錄區間邊數 花費空間 4710 *3 (id low up) 要sort 一下
// 紀錄user id item 數 (id)
// 紀錄
//可以 優化
//check 最後一組資料
//最後是 \n 接eof ....