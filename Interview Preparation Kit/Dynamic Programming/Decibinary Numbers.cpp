/*
https://www.hackerrank.com/challenges/decibinary-numbers/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <fstream>

using namespace std;

static const int d_max = 285113;
static const int m_max = 20;

vector<vector<uint64_t>> table1(d_max, vector<uint64_t>(m_max));
vector<uint64_t> table2(d_max, 0);

uint64_t pow10(int n) {
	
	static vector<uint64_t> v;

	if (v.size() == 0) {

		v.resize(19, 1);

		for (size_t i = 1; i < v.size(); i++) {
			v[i] = v[i - 1] * 10;
		}
	}

	return v[n];
}

inline uint64_t set_digit(uint64_t digit, uint8_t n, uint8_t pos) {

	uint64_t right = digit % pow10(pos);
	uint64_t left = (digit - right) / pow10(pos);

	left -= left % 10;
	left += n;
	left *= pow10(pos);

	return left + right;
}

inline int get_digit(uint64_t digit, uint8_t pos) {

	uint64_t right = digit % pow10(pos + 1);
	right -= right % pow10(pos);
	return right / pow10(pos);
}

inline uint64_t to_decimal(uint64_t decibinary) {

	if (decibinary < 10)
		return decibinary;

	uint64_t res = decibinary % 10;
	int m = 1;

	decibinary -= decibinary % 10;
	decibinary /= 10;

	while (decibinary) {

		int digit = get_digit(decibinary, 0);
		res += (1 << m) * digit;

		decibinary -= decibinary % 10;
		decibinary /= 10;

		m++;
	}

	return res;
}

void init() {

	//with help from this link:
	//https://math.stackexchange.com/questions/3540243/whats-the-number-of-decibinary-numbers-that-evaluate-to-given-decimal-number/3545775#3545775

	for (size_t d = 0; d < d_max; d++) {
		table1[d][0] = d < 10;

		for (size_t m = 1; m < m_max; m++) {

			for (int p = 0; p < 10; p++) {

				int left = d - p * (1 << m);

				if (left < 0) break;

				table1[d][m] += table1[left][m - 1];
			}
		}
	}

	table2[0] = 1;
	for (size_t d = 1; d < d_max; d++)
		table2[d] = table1[d][m_max - 1] + table2[d - 1];
}

uint64_t min_decibinary(uint64_t decimal, int m) {

	if (m == 1 && decimal < 10)
		return decimal;
	else if (m == 1)
		return std::numeric_limits<uint64_t>::max();

	//set top digit
	uint64_t decibinary = 1;
	int digit = 1;

	while (digit != 10) {
	
		int64_t left = decimal - digit * (1 << (m - 1));

		if (decimal < digit * (1 << (m - 1)))
			return std::numeric_limits<uint64_t>::max();

		if (m - 1 - 1 >= 0 && table1[left][m - 1 - 1]) {
			
			decibinary = digit;
			break;
		}

		digit++;
	}

	if (digit == 10)
		return std::numeric_limits<uint64_t>::max();

	digit = 0;
	uint64_t left = decimal - decibinary * (1 << (m - 1));
	m--;

	while (left > 9 && digit != 10) {

		auto temp = left;
		temp -= digit * (1 << (m - 1));

		auto m_next = m - 1;

		if (m - 1 - 1 >= 0 && table1[temp][m - 1 - 1]) {
			left = temp;
			decibinary *= 10;
			decibinary += digit;
			m--;
			digit = 0;
			continue;
		}
		digit++;
	}

	if (digit == 10)
		return std::numeric_limits<uint64_t>::max();

	while (m) {
		decibinary *= 10;
		m--;
	}

	return decibinary + left;
}

uint64_t next_decibinary(uint64_t decimal, uint64_t decibinary, int m) {

	uint64_t result = set_digit(decibinary, 0, 0);

	//upward pass
	int i = 1;

	while (i < m) {

		auto temp = get_digit(result, i);

		if (temp == 9) {
			result = set_digit(result, 0, i);
		}
		else {
			result = set_digit(result, temp + 1, i);
			auto x = to_decimal(result);
			if (to_decimal(result) <= decimal)
				break;
		}

		result = set_digit(result, 0, i);
		i++;
	}

	if (result == 0)
		return std::numeric_limits<uint64_t>::max();

	//downward pass
	i--;

	int digit = 0;
	uint64_t left = decimal - to_decimal(result);

	while(i > 0){
	
		auto temp = left;
		temp -= digit * (1 << i);

		if (i - 1 >= 0 && table1[temp][i - 1]) {
			left = temp;
			result = set_digit(result, digit, i);
			i--;
			digit = 0;
			continue;
		}
		digit++;
	}

	if (digit == 10)
		return std::numeric_limits<uint64_t>::max();

	return result + left;
}

uint64_t get_decibinary(uint64_t decimal, int m, int64_t idx) {

	if (m == 1 && decimal < 10 && idx == 0)
		return decimal;
	else if (m == 1)
		return std::numeric_limits<uint64_t>::max();

	uint64_t result = 0;
	int n = m - 1;
	int64_t max_solutions = 0, 
		prev_solutions = 0, 
		start_solution = -1;

	for (size_t d = 0; d < 10; d++) {

		auto left = decimal - d * (1 << n);

		if (table1[left][n - 1] == 0)
			continue; //there's no solutions with this digit

		if (d == 0)
			max_solutions = table1[decimal][n - 1];
		else {
			prev_solutions = max_solutions;
			max_solutions += table1[left][n - 1];
		}

		if (idx >= max_solutions) {
			continue;
		}
		else {

			result = d;
			result *= pow10(n);

			return result + get_decibinary(left, m - 1, idx - prev_solutions);
		}
	}




	return result + decimal;
}

// Complete the decibinaryNumbers fleft_valion below.
uint64_t decibinaryNumbers(uint64_t x) {

	auto ptr = lower_bound(table2.begin(), table2.end(), x);

	auto decimal = ptr - table2.begin();
	
	int64_t idx;

	if (ptr == table2.begin())
		return 0;

	else if (*(ptr - 1) == x) 
		idx = 1;

	else 
		idx = x - *(ptr - 1);

	auto& temp = table1[decimal];

	auto m_ptr = lower_bound(table1[decimal].begin(), table1[decimal].end(), idx);
	auto m = m_ptr - table1[decimal].begin() + 1;

	idx--;

	return get_decibinary(decimal, m, idx);

	/*auto decibinary = min_decibinary(decimal, m);

	while (idx) {
		
		decibinary = next_decibinary(decimal, decibinary, m);
		idx--;
	}

	return decibinary;*/
}

void tests(string filename, vector<string> output) {

	ifstream fs;
	fs.open(filename.c_str());

	if (!fs.is_open()) {
		cout << "problem with openning file: " << filename.c_str() << endl;
		return;
	}

	int n, i = 0;
	string temp1, temp2;

	fs >> n;


	while(n) {

		temp1.clear();
		temp2.clear();

		//fs >> temp1;
		//fs >> temp2;

		n--;

		//auto start = std::chrono::system_clock::now();
		//auto t1 = std::chrono::system_clock::to_time_t(start);
		////cout << "start time: " << std::ctime(&t1) << endl;
		//auto res = abbreviation(temp1, temp2);
		//auto end = std::chrono::system_clock::now();
		//auto t2 = std::chrono::system_clock::to_time_t(end);
		////cout << "end time: " << std::ctime(&t2) << endl;
		//cout << "output: " << res << ", expected: " << output[i]
		//	<< "\t takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;

		i++;
	}

	fs.close();
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
	vector<uint64_t> input, output;
	vector<pair<uint64_t, uint64_t>> to_show;

	fs_in >> n;

	while (n) {

		uint64_t x, res;
		fs_in >> x;
		fs_out >> res;

		input.push_back(x);
		output.push_back(res);
		n--;
	}

	fs_in.close();
	fs_out.close();

	auto start = std::chrono::system_clock::now();
	auto t1 = std::chrono::system_clock::to_time_t(start);
	//cout << "start time: " << std::ctime(&t1) << endl;

	for (size_t i = 0; i < input.size(); i++) {
		//cout << '\r' << i;
		auto result = decibinaryNumbers(input[i]);
		if (debug || result != output[i])
			to_show.push_back(make_pair(result, output[i]));
	}

	auto end = std::chrono::system_clock::now();
	auto t2 = std::chrono::system_clock::to_time_t(end);
	//cout << "end time: " << std::ctime(&t2) << endl;

	for (size_t i = 0; i < to_show.size(); i++) {

		cout << "output: " << to_show[i].first << ", expected: " << to_show[i].second << endl;
	}

	cout << "test case has done for " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
}

void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl;

	vector<uint64_t> input, ouput;

	input = {1,2,3,4,10}; //Sample Input 0
	ouput = {0,1,2,10,100};
	for (size_t i = 0; i < input.size(); i++) {
		auto res = decibinaryNumbers(input[i]);
		if (debug || res != ouput[i])
			cout << "output: " << res << ", expected: " << ouput[i] << endl;
	}

	input = { 8,23,19,16,26,7,6 }; //Sample Input 1
	ouput = { 12,23,102,14,111,4,11 };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = decibinaryNumbers(input[i]);
		if (debug || res != ouput[i])
			cout << "output: " << res << ", expected: " << ouput[i] << endl;
	}

	input = { 19,25,6,8,20,10,27,24,30,11 }; //Sample Input 2
	ouput = { 102,103,11,12,110,100,8,31,32,5 };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = decibinaryNumbers(input[i]);
		if (debug || res != ouput[i])
			cout << "output: " << res << ", expected: " << ouput[i] << endl;
	}


	input = { 666,114,234 }; //My
	ouput = { 10018,118,1018 };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = decibinaryNumbers(input[i]);
		if (debug || res != ouput[i])
			cout << "output: " << res << ", expected: " << ouput[i] << endl;
	}

	input = { 1032 }; //My
	ouput = { 615 };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = decibinaryNumbers(input[i]);
		if (debug || res != ouput[i])
			cout << "output: " << res << ", expected: " << ouput[i] << endl;
	}

	cout << endl;
}

void test_case_03(bool debug = true) {

	cout << "Test case 03" << endl;
	run_tests("..\\tests\\test03_in.txt", "..\\tests\\test03_out.txt", debug);
	cout << endl;
}

void test_case_06(bool debug = true) {

	cout << "Test case 06" << endl;
	run_tests("..\\tests\\test06_in.txt", "..\\tests\\test06_out.txt", debug);
	cout << endl;
}

void test_case_07(bool debug = true) {

	cout << "Test case 07" << endl;
	run_tests("..\\tests\\test07_in.txt", "..\\tests\\test07_out.txt", debug);
	cout << endl;
}

void make_brutal_table(uint64_t size) {

	vector<vector<uint64_t>> v(d_max, vector<uint64_t>{});

	for (uint64_t i = 0; i < size; i++) {

		auto d = to_decimal(i);
		v[d].push_back(i);
	}

	//for (size_t i = 0; i < v.size(); i++)
	//{
	//	if (v[i].size() !=0)
	//		cout << i << '\t' <<  v[i][0] << endl;
	//}


	//for (size_t i = 0; i <= 10; i++)
	//{
	//	for (size_t n = 20; n < 30; n++)
	//	{
	//		if (v[n].size() != 0)
	//			cout << std::setw(3) << v[n][i] << ' ';
	//	}
	//	cout << endl;
	//}

	cout << endl << endl;


	fstream fs;
	fs.open("..\\tests\\some_log.txt", 'w');

	if (!fs.is_open()) {
		cout << "problem with openning file" << endl;
		return;
	}

	for (size_t i = 0; i <= 20; i++)
	{
		fs << setw(2) << i << ": ";

		for (size_t d = 0; d < 100; d++)
		{
			if (d < v[i].size()) {
				if (v[i][d] < 99999)
					fs << setw(5) << v[i][d] << " ";
			}
			else break;
		}
		fs << endl;

	}

	fs.close();

	cout << endl << endl;
	

	cout << "done." << endl;
}

int main() {

	init();

	sample_tests(false);
	test_case_03(false);
	test_case_06(false);
	test_case_07(false);

	cout << endl << "done." << endl;

	int a;
	cin >> a;

	return 0;
}