#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <Windows.h>
#include <map>
#include <set>

#define mdebug

using namespace std;

template <class T>
void print(T *ptr, int size, bool endline = true) {

#ifdef mdebug

	cout << "{ ";

	for (size_t i = 0; i < size; i++)
	{
		cout << ptr[i] << " ";
	}

	cout << "}\t";

	if (endline)
		cout << endl;

#endif // mdebug

}

void print(map<int, int> &map) {

	//cout << "{ ";
	auto ptr = map.begin();

	while (ptr != map.end()) {
		cout << ptr->first << "\t-\t" << ptr->second << endl;
		ptr++;
	}

	//cout << "}" << endl;
	//cout << endl;
}

bool count_frequence(map<int, int> &m, int z) {

	auto ptr = m.begin();

	while (ptr != m.end()) {
		if (ptr->second == z)
			return true;
		ptr++;
	}

	return false;
}

vector<int> freqQuery_old1(vector<vector<int>> queries) {

	vector<int> result;

	map<int, int> m;

	for (size_t i = 0; i < queries.size(); i++) {

		int &q = queries[i][0];
		int &data = queries[i][1];

		if (q == 1) {
			m[data]++;
		}
		else if (q == 2) {
			auto ptr = m.find(data);
			if (ptr != m.end() && ptr->second > 1)
				ptr->second--;
			else if (ptr != m.end())
				m.erase(ptr);
		}
		else if (q == 3) {
			//print(m);
			if (count_frequence(m, data))
				result.push_back(1);
			else result.push_back(0);
		}
		else std::runtime_error("wrong operation number");
	}

	return result;
}

vector<int> freqQuery(vector<vector<int>> queries) {

	vector<int>		result;

	map<int, int>	m; //key - data, value - number of data count
	map<int, int>	m_rev; //key - data count, value - number of figures have the same count

	for (size_t i = 0; i < queries.size(); i++) {

		int &query = queries[i][0];
		int &data = queries[i][1];

		if (query == 1) {

			m[data]++;
			int count = m[data];
			m_rev[count]++;

			if (count > 1) {
				auto ptr = m_rev.find(count - 1);
				ptr->second--;
				if (ptr->second == 0)
					m_rev.erase(ptr);
			}
		}
		else if (query == 2) {

			auto ptr = m.find(data);

			if (ptr == m.end()) 
				continue;

			int count = ptr->second;

			auto ptr_rev = m_rev.find(count);

			ptr->second--;

			if (ptr->second == 0) 
				m.erase(ptr);
			else 
				m_rev[ptr->second]++;

			ptr_rev->second--;
			if (ptr_rev->second == 0)
				m_rev.erase(ptr_rev);
		}
		else if (query == 3) {

			/*cout << "map<int, int> contaided [value] to [count]:" << endl;
			print(m);
			cout << "map<int, int> contaided [count] to [different numbers]:" << endl;
			print(m_rev);*/

			auto ptr_rev = m_rev.find(data);

			if (ptr_rev != m_rev.end())
				result.push_back(1);			
			else 
				result.push_back(0);
		}
		else std::runtime_error("wrong operation number");
	}

	return result;
}

void test() {

	vector<int> v;

	v = freqQuery({ {1,1}, {2,2}, {3,2}, {1,1 }, {1,1}, {2,1}, {3,2} });
	print(v.data(), v.size());

	v = freqQuery({ {1,5}, {1,6}, {3,2}, {1,10}, {1,10}, {1,6}, {2,5}, {3,2} });
	print(v.data(), v.size());

	v = freqQuery({ {3,4}, {2, 1003}, {1,16}, {3,1} });
	print(v.data(), v.size());

	v = freqQuery({ {1,3}, {2,3}, {3,2}, {1,4}, {1,5}, {1,5}, {1,4}, {3,2}, {2,4}, {3,2} });
	print(v.data(), v.size());
}

int main()
{
	test();

	system("pause");

	return 0;
}