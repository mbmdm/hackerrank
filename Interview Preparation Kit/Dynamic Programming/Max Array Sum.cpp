/*
https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

int maxSubsetSum(vector<int> arr) {

	vector<int> buffer(arr.size(), 0);
	
	if (arr[0] < 0)
		buffer[0] = 0;
	else buffer[0] = arr[0];

	if (arr.size() == 1) return buffer[0];

	buffer[1] = std::max(arr[1], buffer[0]);
		
	for (size_t i = 2; i < arr.size(); i++) {

		if (arr[i] > 0)
			buffer[i] = std::max((buffer[i - 2] + arr[i]), buffer[i - 1]);
		else
			buffer[i] = buffer[i - 1];
	}

	return *std::max_element(buffer.begin(), buffer.end());
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
		auto res = maxSubsetSum(arr);
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

	arr = { 2,1,5,8,4 }; //test case 31
	res = maxSubsetSum(arr);
	cout << "output: " << res << ", expected: 11" << endl;

	arr = { 3,7,4,6,5 }; //test case 30
	res = maxSubsetSum(arr);
	cout << "output: " << res << ", expected: 13" << endl;

	arr = { -2,1,3,-4,5 };
	res = maxSubsetSum(arr);
	cout << "output: " << res << ", expected: 8" << endl;

	arr = { 3,5,-7,8,10 }; //test case 32
	res = maxSubsetSum(arr);
	cout << "output: " << res << ", expected: 15" << endl;

}

void test_case_29() {

	cout << "Test case 29" << endl;
	run_tests("..\\tests\\test29.txt", { 185747029 });
	cout << endl;
}

int main() {

	sample_tests();
	test_case_29();

	return 0;
}