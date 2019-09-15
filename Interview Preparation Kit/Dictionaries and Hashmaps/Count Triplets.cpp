#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <Windows.h>

using namespace std;

void print(unordered_map<long, long> &map) {

	//cout << "{ ";
	auto ptr = map.begin();

	while (ptr != map.end()) {
		cout << ptr->first << "\t-\t" << ptr->second << endl;
		ptr++;
	}

	//cout << "}" << endl;
	cout << endl;
}

// Complete the countTriplets function below.
long long countTriplets_wrong(vector<long> arr, long r) {

	if (r == 1)
		return arr.size() * (arr.size() - 1) * (arr.size() - 2) / 6; //combination 3 of (n - 1);

	unordered_map<long, long> map;

	auto ptr = arr.begin();

	while (ptr != arr.end()) {
		map[*ptr]++;
		ptr++;
	}

	long long result = 0;
	int iteration = 0;

	//print(map);

	for (long index = 0; index < arr.size()/* - 2*/; index++) {
		
		long a = arr[index];
		long b = a * r;
		long c = b * r;

		auto ptr_a = map.find(a);
		auto ptr_b = map.find(b);
		auto ptr_c = map.find(c);

		long count_a = ptr_a->second;

		//if (ptr_a->second == 0)
		//	cout << "error1" << endl;

		ptr_a->second--;

		//if (ptr_a->second == 0)
		//	cout << ptr_a->first <<  " become 0" << endl;

		if (ptr_a == map.end() || ptr_b == map.end() || ptr_c == map.end())
			continue;

		//if (ptr_a->second < 0 || ptr_b->second < 0 || ptr_c->second < 0) {
		//	cout << "error2" << endl;
		//}

		long count_b = ptr_b->second;
		long count_c = ptr_c->second;

		if (count_a == 0 || count_b == 0 || count_c == 0)
			continue;
		
		//if (r == 1)
		//	result += count_b * (count_b - 1) / 2; //formula combination 2 of (n - 1);
		//else
		
		iteration++;

		result += count_c * count_b;
	}

	//cout << endl;
	//print(map);
	//cout << endl;

	return result;
}

// Complete the countTriplets function below.
long long countTriplets(vector<long> arr, long r) {

	unordered_map<long, long> map2;
	unordered_map<long, long> map3;

	long long result = 0;

	for (size_t i = 0; i < arr.size(); i++)	{

		long a = arr[i];
		long b = a * r;
		long c = b * r;

		if (map3.find(a) != map3.end())
			result += map3[a];

		if (map2.find(a) != map2.end())
			map3[b] += map2[a];

		map2[b]++;
	}

	return result;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test(string file, long long expected_result) {
	
	cout << "start test from " << file << ":" << endl;

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + file, ios::in);

	long size;
	long r;
	long temp;

	fs_data >> size;
	fs_data >> r;

	vector<long> arr;
	while (fs_data >> temp) {
		arr.push_back(temp);
	}

	fs_data.close();

	auto start = chrono::system_clock::now();
	cout << countTriplets(arr, r) << " / " << expected_result;
	auto end = chrono::system_clock::now();
	cout << ", time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
}

void test() {

	cout << countTriplets({ 1, 2, 2, 4 }, 2) << " \ 2" << endl;
	cout << countTriplets({ 1, 3, 9, 9, 27, 81 }, 3) << " \ 6" << endl;
	cout << countTriplets({ 1, 5, 5, 25, 125 }, 5) << " \ 4" << endl;
	cout << countTriplets({ 1, 2, 1, 2, 4 }, 2) << " \ 3" << endl;

	//test case 2
	vector<long> v;
	v.resize(100);
	fill(v.begin(), v.end(), 1);
	cout << countTriplets(v, 1) << " \ 161700" << endl;
}

int main()
{
	test("data10.txt", 1339347780085);
	test("data6.txt", 2325652489);

	test();

	system("pause");

	return 0;
}