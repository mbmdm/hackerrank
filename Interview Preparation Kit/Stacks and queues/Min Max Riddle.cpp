/*
https://www.hackerrank.com/challenges/min-max-riddle/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <map>

using namespace std;

// brutal variant
vector<int64_t> riddle_brutal(vector<int64_t> arr) {

	vector<int64_t> result;

	for (size_t w = 1; w <= arr.size(); w++) {
		
		vector<int64_t> v;
		auto ptr = arr.begin();
		do {
			
			auto minw = std::min_element(ptr, ptr + w);
			v.push_back(*minw);
			ptr++;
		} while (ptr - 1 + w != arr.end());

		auto maxw = max_element(v.begin(), v.end());
		result.push_back(*maxw);
	}


	return result;
}

vector<int64_t> riddle_DP(vector<int64_t> arr) {

	vector<int64_t> result, w_prev, w_next;
	vector<int64_t>::iterator ptr;
	int64_t local_max;

	copy(arr.begin(), arr.end(), back_inserter(w_prev));
	ptr = max_element(arr.begin(), arr.end());
	result.push_back(*ptr);

	while (w_prev.size() != 1) {

		ptr = w_prev.begin();
		local_max = std::numeric_limits<int64_t>::min();
		while (ptr + 1 != w_prev.end()) {

			auto r = min(*ptr, *(ptr + 1));
			w_next.push_back(r);
			local_max = max(local_max, r);
			ptr++;
		}

		w_prev.clear();
		w_prev.swap(w_next);
		result.push_back(local_max);
	}

	return result;
}

unsigned int count_max_window(vector<int64_t>& arr, vector<int64_t>::iterator pivot) {
	
	if (pivot == arr.end()) return 0;

	unsigned int count = 1;
	vector<int64_t>::iterator ptr;

	//move left
	ptr = (pivot != arr.begin()) ? pivot -1 : arr.end();
	while (ptr != arr.end()) {

		if (min(*ptr, *pivot) == *pivot)
			count++;
		else break;

		ptr = (ptr == arr.begin()) ? arr.end() : ptr - 1;
	}

	//move right
	ptr = pivot + 1;
	while (ptr != arr.end()) {
		
		if (min(*ptr, *pivot) == *pivot)
			count++;
		else break;

		ptr++;
	}

	return count;
}

template <class T>
struct mless {

	bool operator()(const T& a, const T& b) const {
		return a > b;
	}
};

vector<int64_t> riddle(vector<int64_t> arr) {

	vector<int64_t> result;
	map<unsigned int, int64_t, mless<unsigned int>> map1;

	auto ptr = arr.begin();
	while (ptr != arr.end()) {

		auto len = count_max_window(arr, ptr);
		map1[len] = std::max(map1[len], *ptr);
		ptr++;
	}

	//correct map. 
	//there is the situation when a > b, but in map1 stored 3:a and 2:b.
	//in this situation we must replace the value by key=2 with a 
	auto ptr2 = map1.begin();
	auto ptr3 = map1.begin();
	ptr3++;
	while (ptr3 != map1.end()) {
		
		if (ptr2->second > ptr3->second)
			ptr3->second = ptr2->second;

		ptr2++;
		ptr3++;
	}

	ptr2 = map1.begin();
	auto left = arr.size();
	while (left && ptr2 != map1.end()) {

		auto w = (*ptr2).first;
		auto num = (*ptr2).second;

		if (left == w) {
			result.push_back(num);
			ptr2++;
		}
		else {
			auto prev_val = result[result.size() - 1];
			result.push_back(prev_val);
		}

		left--;
	}

	auto val = result[result.size() - 1];
	while (left) {
		result.push_back(val);
		left--;
	}

	std::reverse(result.begin(), result.end());

	return result;
}

void run_tests(string filename_in, string filename_out, bool debug = true) {

	ifstream fs_in, fs_out;
	fs_in.open(filename_in.c_str());
	fs_out.open(filename_out.c_str());

	if (!fs_in.is_open()) {
		cout << "problem with openning file: " << filename_in.c_str() << endl;
		return;
	}

	if (!fs_out.is_open()) {
		cout << "problem with openning file: " << filename_out.c_str() << endl;
		return;
	}

	int n;
	vector<int64_t> input, output;

	fs_in >> n;

	int64_t temp;
	while (fs_in >> temp)
		input.push_back(temp);

	while (fs_out >> temp)
		output.push_back(temp);

	fs_in.close();
	fs_out.close();

	auto start = std::chrono::system_clock::now();
	auto t1 = std::chrono::system_clock::to_time_t(start);
	//cout << "start time: " << std::ctime(&t1) << endl;
	auto result = riddle(input);
	auto end = std::chrono::system_clock::now();
	auto t2 = std::chrono::system_clock::to_time_t(end);

	
	bool flag = true;
	for (size_t i = 0; i < output.size(); i++) 
		if (output[i] != result[i]) {
			flag = false;
			break;
		}

	if (flag)
		cout << "OK\t";
	else
		cout << "FAILED\t";

	cout << "test case has done for "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
}

void test_case_02(bool debug = true) {

	cout << "Test case 02" << endl;
	run_tests("..\\tests\\test02_in.txt", "..\\tests\\test02_out.txt", debug);
	cout << endl;
}

void test_case_05(bool debug = true) {

	cout << "Test case 05" << endl;
	run_tests("..\\tests\\test05_in.txt", "..\\tests\\test05_out.txt", debug);
	cout << endl;
}

void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl << endl;

	vector<int64_t> input, output, res;
	string case_name;

	case_name = "my 2";
	input = { 1,1,1,0,99,99,99 }; //my
	output = { 99,99,99,0,0,0,0 };
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	case_name = "my 1";
	input = { 1,1,1 }; //my
	output = { 1,1,1 };
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	case_name = "Description input";
	input = { 6,3,5,1,12 }; //Description input
	output = { 12,3,3,1,1 };
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	case_name = "Sample Input 0";
	input = { 2,6,1,12 }; //Sample Input 0
	output = {12,2,1,1};
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	case_name = "Sample Input 1";
	input = { 1, 2, 3, 5, 1, 13, 3 }; //Sample Input 1
	output = { 13, 3, 2, 1, 1, 1, 1 };
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	case_name = "Sample Input 2";
	input = { 3, 5, 4, 7, 6, 2 }; //Sample Input 2
	output = { 7, 6, 4, 4, 3, 2, };
	res = riddle(input);
	cout << case_name << ":" << endl;
	if (res.size() != output.size())
		cout << "result size is incorrect" << endl;
	else {
		for (size_t i = 0; i < output.size(); i++)
			if (debug || res[i] != output[i])
				cout << "output: " << res[i] << ", expected: " << output[i] << endl;
	}
	cout << "done" << endl << endl;

	cout << endl;
}

int main() {

	sample_tests(false);
	test_case_02(false);
	test_case_05(false);

	cout << endl << "done." << endl;

	int temp;

	cin >> temp;

	return 0;
}