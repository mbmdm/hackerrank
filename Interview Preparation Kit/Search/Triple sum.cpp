#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

#define mdebug

void prepare_arrys(vector<int> &a, vector<int> &b, vector<int> &c) {

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());

	//remove the same
	a.erase(unique(a.begin(), a.end()), a.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	c.erase(unique(c.begin(), c.end()), c.end());
}

// Complete the triplets function below.
long long triplets(vector<int> a, vector<int> b, vector<int> c) {

	prepare_arrys(a, b, c);

	long long res = 0;
	int a_idx = 0;
	int b_idx = 0;
	int c_idx = 0;

	for (; b_idx < b.size(); b_idx++) {
		int &q = b[b_idx];

		for (; a_idx < a.size() && a[a_idx] <= q; a_idx++);
		for (; c_idx < c.size() && c[c_idx] <= q; c_idx++);

		res += (long long)a_idx * c_idx;
	}

	return res;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test(string fname, long long result) {

#ifdef mdebug

	vector<int> a, b, c;

	int asize, bsize, csize, temp;

	string path = ExePath();

	ifstream fs{};
	fs.open(path + "\\" + fname, ios::in);

	fs >> asize >> bsize >> csize;

	while (asize && fs >> temp) {
		a.push_back(temp);
		asize--;
	}

	while (bsize && fs >> temp) {
		b.push_back(temp);
		bsize--;
	}

	while (csize && fs >> temp) {
		c.push_back(temp);
		csize--;
	}

	auto r = triplets(a, b, c);

	if (result != r)
		cout << "test case " << fname << " failed" << endl << "wrong value: " << r << endl << "right value: " << result << endl;
	else {
		cout << "test case " << fname << " done" << endl;
		cout << "result: " << r << endl;
	}

	cout << endl;

#else
	cout << "define mbebug" << endl;
#endif

}

int main()
{
	test("data4.txt", 145333908482693);

	system("pause");

	return 0;
}