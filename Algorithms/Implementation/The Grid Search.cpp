#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>
#include <chrono>

using namespace std;

inline bool find_pattern(vector<string> &g, vector<string> &p, int i_, int j_) {

	int r = p.size();
	int c = p[0].size();

	for (size_t i = 0; i < r; i++) {
		int r_comp = memcmp(g[i_+i].data() + j_, p[i].data(), c);
		if (r_comp != 0)
			return false;			
	}

	return true;
}

// Complete the gridSearch function below.
string gridSearch(vector<string> G, vector<string> P) {

	int R = G.size();
	int C = G[0].size();
	int r = P.size();
	int c = P[0].size();

	string start_p = P[0];

	for (size_t i = 0; i < R-r+1; i++) {

		for (size_t j = 0; j < C-c+1; j++) {

			if (find_pattern(G, P, i, j))
				return "YES";
		}
	}

	return "NO";
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test() {
	
	vector<string> g = 
	{
		"7283455864",
		"6731158619",
		"8988242643",
		"3830589324",
		"2229505813",
		"5633845374",
		"6473530293",
		"7053106601",
		"0834282956",
		"4607924137"
	};

	//vector<string> p =
	//{
	//	"7283",
	//	"6731",
	//	"8988"
	//};

	vector<string> p =
	{
		"9505",
		"3845",
		"3530"
	};

	cout << gridSearch(g, p) << endl;
}

void test(string file) {

	cout << "start test from " << file << ":" << endl;

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + file, ios::in);

	int t;

	fs_data >> t;


	while (t) {

		int R, r, C, c;
		vector<string> g;
		vector<string> p;
		string temp;
		char buf;

		//init g
		fs_data >> R;
		fs_data >> C;
		fs_data >> buf;
		if (isdigit(buf)) fs_data.putback(buf);

		for (size_t i = 0; i < R; i++)
		{
			getline(fs_data, temp);
			g.push_back(temp);
			temp.clear();
		}

		//init p
		fs_data >> r;
		fs_data >> c;
		fs_data >> buf;
		if (isdigit(buf)) fs_data.putback(buf);

		for (size_t i = 0; i < r; i++)
		{
			getline(fs_data, temp);
			p.push_back(temp);
			temp.clear();
		}

		auto start = chrono::system_clock::now();
		cout << gridSearch(g, p);
		auto end = chrono::system_clock::now();
		cout << ", time: " <<chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

		t--;
	}
	fs_data.close();
}

int main()
{
	test("data4.txt");

	system("pause");

	return 0;
}