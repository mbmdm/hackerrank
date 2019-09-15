#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;

//#define mdebug

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

void print(string s, int start, int end) {

#ifdef mdebug

	cout << start << "..." << end;
	cout << " - { ";
	while (start != end) {
		cout << s[start];
		start++;
	}
	cout << s[end] << " }";

#endif // mdebug

}

void print(vector<vector<int>> &v) {

#ifdef mdebug

	for (size_t i = 0; i < v.size(); i++) {
		cout << "{ ";

		for_each(v[i].begin(), v[i].end(), [](int &a) {
			cout << setw(2) << a;
		});

		cout << " }" << endl;
	}
	cout << endl;


#endif // mdebug
}

string commonChild_very_slow(string s1, string s2, int end1, int end2) {
	
	if (s1[end1] == s2[end2]) {
		if (end1 != 0 && end2 != 0)
			return commonChild_very_slow(s1, s2, end1 - 1, end2 - 1) + s1[end1];
		else return
			string{ s1[end1] };
	}
	else {
		
		string r1, r2;

		if (end1 != 0)
			r1 = commonChild_very_slow(s1, s2, end1 - 1, end2);

		if (end2 != 0)
			r2 = commonChild_very_slow(s1, s2, end1, end2 - 1);

		if (r1.size() > r2.size())
			return r1;

		else return r2;
	}
}

// Complete the commonChild function below.
int commonChild(string s1, string s2) {

	int n = s1.size();
	int m = s2.size();

	vector<vector<int>> buffer;
	buffer.resize(n);
	for_each(buffer.begin(), buffer.end(), [m](vector<int> &v) {
		v.resize(m);
		//v[0] = 0; //init fist column
	});

	//init fist row
	//fill(buffer[0].begin(), buffer[0].end(), 0);

	//calculation buffer
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++)
		{
			char ch1 = s1[i];
			char ch2 = s2[j];

			if (s1[i] == s2[j]) {
				if (i && j)
					buffer[i][j] = buffer[i - 1][j - 1] + 1;
				else 
					buffer[i][j] = 1;
			}
			else {
				int max_ = 0;
				if (j)
					max_ = buffer[i][j - 1];
				if (i)
					max_ = max(max_, buffer[i - 1][j]);

				buffer[i][j] = max_;
			}
		}
	}

	print(buffer);

	return buffer[n - 1][m - 1];
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test() {

	//source 
	cout << commonChild("ABCD", "ABDC") << endl; // ABC - 3
	cout << commonChild("AA", "BB") << endl; // 0
	cout << commonChild("ABCDEF", "FBDAMN") << endl; // BD - 2
	cout << commonChild("HARRY", "SALLY") << endl; // AY - 2
	cout << commonChild("SHINCHAN", "NOHARAAA") << endl; // NHA - 3	
	
	//test caset 1
	string s1 = "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS";
	string s2 = "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC";
	cout << commonChild(s1, s2) << endl; // 15
}

int main() 
{
	test();

	system("pause");

	return 0;
}