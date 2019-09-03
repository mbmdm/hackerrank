#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

void print(vector<int> &v) {

	for_each(v.begin(), v.end(), [](int &i) {cout << i << " "; });
}

void print(char *ptr, int size) {

	while (size) {
		cout << *ptr << " ";
		ptr++;
		size--;
	}
}

// Complete the absolutePermutation function below.
vector<int> absolutePermutation(int n, int k) {

	//char *buf = new char[n];
	vector<int> buf;
	buf.resize(n);
	fill(buf.begin(), buf.end(), 0);

	vector<int> res;
	
	for (size_t i = 1; i <= n; i++) {
		
		int v1 = (int)i - k;
		int v2 = (int)i + k;
		int fin;	

		int check_index = v1 - k - 1;

		if (v1 <= 0)
			fin = v2;
		else if (check_index >= 0 && buf[check_index] == v1)
			fin = v2;
		else
			fin = v1;

		buf[i - 1] = fin;
		res.push_back(fin);

		if (fin > n) {
			res.clear();
			res.push_back(-1);
			break;
		}
	}

	return res;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test(int n, int k, vector<int> result, int test_number){
	
	auto v = absolutePermutation(n, k);

	bool flag = true;

	for (size_t i = 0; i < v.size(); i++) {
		
		if (v[i] != result[i]) {
			flag = false;
			break;
		}
	}

	if (flag)
		cout << "OK\t" << "test" << test_number << endl;
	else {
		cout << "FAILED\t" << "test" << test_number << ", result is:" << endl;
		print(v);
		cout << endl;
	}

}

void test(string file) {

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + file, ios::in);

	int temp;

	fs_data >> temp;

	int n;
	int k;
	vector<vector<int>> input;
	int x, y;
	while (!fs_data.eof()) {
		fs_data >> x;
		fs_data >> y;
		input.push_back({ x, y });
	}

	fs_data.close();

	cout << "test " << file << " result is:" << endl;

	for_each(input.begin(), input.end(), [](vector<int> &v) {
		
		auto result = absolutePermutation(v[0], v[1]);
		print(result);
		cout << endl;	
	});
}

int main()
{
	setlocale(LC_ALL, "Russian"); //test

	test(4, 2, { 3,4,1,2 }, 1);
	test(2, 1, { 2,1 }, 2);
	test(3, 0, { 1,2,3 }, 3);
	test(3, 2, { -1 }, 4);

	test(10, 1, { 2, 1, 4, 3, 6, 5, 8, 7, 10, 9 }, 4);

	test("data2.txt");

	system("pause");

	return 0;
}