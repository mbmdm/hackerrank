/*
https://www.hackerrank.com/challenges/candies/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <numeric>

using namespace std;

void pass01(const vector<int>& rank, vector<int64_t>& candies) {
	
	candies[0] = 1;

	for (size_t curr = 1; curr < rank.size(); curr++) {

		auto prev = curr - 1;

		if (rank[curr] < rank[prev]) 
			candies[curr] = 1;

		else if (rank[curr] == rank[prev])
			candies[curr] = 1;

		else
			candies[curr] = candies[prev] + 1;

	}
}

void pass02(const vector<int>& rank, vector<int64_t>& candies) {

	auto n = rank.size()-1;

	while (n) {
	
		auto curr = n - 1;
		auto prev = curr + 1;

		if (rank[curr] > rank[prev]) {
			if (candies[curr] <= candies[prev]) 
				candies[curr] = candies[prev] + 1;
		}
		n--;
	}
}

int64_t candies(int n, vector<int> rank) {
	
	vector<int64_t> candies(rank.size(), 0);
	
	pass01(rank, candies);
	pass02(rank, candies);

	return std::accumulate<vector<int64_t>::iterator, int64_t>(candies.begin(), candies.end(), 0);
}

void run_tests(string filename, vector<int64_t> output) {

	ifstream fs;
	fs.open(filename.c_str());

	if (!fs.is_open()) {
		cout << "problem with openning file: " << filename.c_str() << endl;
		return;
	}

	int n, temp;
	vector<int> arr;

	for (int i = 0; i < output.size(); i++) {

		arr.clear();

		fs >> n;

		while (n) {
			fs >> temp;
			arr.push_back(temp);
			n--;
		}

		auto start = std::chrono::system_clock::now();
		auto t1 = std::chrono::system_clock::to_time_t(start);
		//cout << "start time: " << std::ctime(&t1) << endl;
		auto res = candies(arr.size(), arr);
		auto end = std::chrono::system_clock::now();
		auto t2 = std::chrono::system_clock::to_time_t(end);
		//cout << "end time: " << std::ctime(&t2) << endl;
		cout << "output: " << res << ", expected: " << output[i]
			<< "\t takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
		
	}

	fs.close();
}

void sample_tests() {

	cout << "Sample tests" << endl;

	vector<int> arr;
	int res;

	arr = { 2,4,2,6,1,7,8,9,2,1 }; //Sample Input 1
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 19" << endl;

	//arr = { 4,3,2,2,1,5 }; //my test
	//res = candies_(arr.size(), arr);
	//cout << "output: " << res << ", expected: 14" << endl;

	arr = { 1,1,3,3,1 }; //my test
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 7" << endl;

	arr = { 1,1,3,3,1 }; //my test
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 7" << endl;

	arr = { 1,1,4,2,1 }; //my test
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 8" << endl;

	arr = { 1,2,2 }; //Sample Input 0
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 4" << endl;

	arr = { 4,6,4,5,6,2 }; //Example
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 10" << endl;

	arr = { 2,4,3,5,2,6,4,5 }; //Sample Input 2
	res = candies(arr.size(), arr);
	cout << "output: " << res << ", expected: 12" << endl;

	cout << endl;
}

void test_case_15() {

	cout << "Test case 15" << endl;
	run_tests("..\\tests\\test15.txt", { 205598 });
	cout << endl;
}

void test_case_01() {

	cout << "Test case 01" << endl;
	run_tests("..\\tests\\test01.txt", { 33556 });
	cout << endl;
}

void test_case_11() {

	cout << "Test case 11" << endl;
	run_tests("..\\tests\\test11.txt", { 5000050000 });
	cout << endl;
}

int main() {

	sample_tests();

	test_case_01();
	test_case_11();	
	test_case_15();

	return 0;
}