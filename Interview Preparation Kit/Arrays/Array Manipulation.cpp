#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>
#include <chrono>

using namespace std;

void print(vector<long long> &v) {
	cout << "source { ";
	for_each(v.begin(), v.end(), [](long long &i) { cout << i << " "; });
	cout << "}" << endl;
}

inline bool contains(vector<int> &v, int &a) {
	if (a >= +v[0] && a <= v[1]) return true;
	else return false;
}

// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int>> &queries) {

	vector<long long> buffer1;
	buffer1.resize(n);
	fill(buffer1.begin(), buffer1.end(), 0);

	vector<long long> buffer2;
	buffer2.resize(n);
	fill(buffer2.begin(), buffer2.end(), 0);

	for (size_t i = 0; i < queries.size(); i++) {
		
		int a = queries[i][0];
		int b = queries[i][1];
		int k = queries[i][2];

		buffer1[a - 1] += k;
		buffer2[b - 1] += k;
	}

	for (size_t i = 1; i < n; i++) {
		buffer1[i] += buffer1[i - 1];
	}

	for (int i = n-2; i >= 0; i--) {
		buffer2[i] += buffer2[i + 1];
	}

	int ai = 0;
	long long tempi = 0;

	for (size_t i = 0; i < n; i++) {

		buffer2[i] += buffer1[i];

		if (buffer2[i] > tempi) {
			tempi = buffer2[i];
			ai = i+1;
		}
	}

	long long sum = 0;

	for (size_t i = 0; i < queries.size(); i++) {
		
		vector<int> &v = queries[i];

		int a = v[0];
		int b = v[1];
		int k = v[2];

		if (contains(queries[i], ai))
			sum += queries[i][2];

	}

	return sum;
}

// Complete the arrayManipulation function below.
long long arrayManipulation_primitive(int n, vector<vector<int>> &queries) {

	vector<long long> buffer;
	buffer.resize(n);
	fill(buffer.begin(), buffer.end(), 0);

	for (size_t i = 0; i < queries.size(); i++) {
		int a = queries[i][0];
		int b = queries[i][1];
		int k = queries[i][2];

		for (size_t j = a; j <= b; j++)
			buffer[j - 1] += k;
	}

	nth_element(buffer.begin(), buffer.begin() + buffer.size() - 1, buffer.end());

	return *(buffer.end() - 1);
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test() {

	vector<vector<int>> v1 = { {1,5,3}, {4,8,7}, {6,9,1} };
	cout << "result = " << arrayManipulation(10, v1) << endl; //10

	vector<vector<int>> v2 = { { 2,6,8 },{ 3,5,7 },{ 1,8,1 },{5,9,15} };
	cout << "result = " << arrayManipulation(10, v2) << endl; //31
}

void test(string file) {

	cout << "start test from " << file << ":" << endl;

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + file, ios::in);

	int n;
	int temp;
	vector<vector<int>> queries;

	fs_data >> n;
	fs_data >> temp;

	int x, y, z;
	while (!fs_data.eof()) {
		fs_data >> x;
		fs_data >> y;
		fs_data >> z;
		queries.push_back({ x,y,z });
	}
	fs_data.close();

	auto start = chrono::system_clock::now();
	cout << arrayManipulation(n, queries) << endl;
	auto end = chrono::system_clock::now();
	cout << ", time: " << chrono::duration_cast<chrono::seconds>(end - start).count() << endl;

}

int main()
{
	test("data7.txt");

	system("pause");

	return 0;
}