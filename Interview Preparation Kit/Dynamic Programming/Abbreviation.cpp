/*
https://www.hackerrank.com/challenges/abbr/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <numeric>
#include <unordered_map>

using namespace std;

template<class itr>
void catstr(itr& a1, itr& a2, itr& b1, itr& b2) {

	if (a1 == a2) return;
	if (b1 == b2) return;

	while (a1 != a2 && b1 != b2) {
	
		if (*a1 == *b1) {
			a1++;
			b1++;
		}
		else if (isupper(*a1))
			break;
		else if (toupper(*a1) == *b1)
			break;
		else
			a1++;	
	}
}

template<class itr>
bool has_upper(itr a1, itr a2) {
	
	if (a1 == a2)
		return false;

	while (a1 != a2) {
		
		if (isupper(*a1))
			return true;

		a1++;
	}

	return false;
}

template<class itr>
bool pass(itr a1, itr a2, itr b1, itr b2) {

	catstr(a1, a2, b1, b2);

	if (b1 == b2) {	
		if (has_upper(a1, a2))
			return false;
		else
			return true;
	}

	if (a1 == a2)
		return false;

	if (std::distance(a1, a2) < std::distance(b1, b2))
		return false;

	if (isupper(*a1))
		return false;

	return pass(a1 + 1, a2, b1 + 1, b2) || pass(a1 + 1, a2, b1, b2);
}

//abbreviation_brutal
string abbreviation_brutal(string a, string b) {
	
	if (pass(a.begin(), a.end(), b.begin(), b.end()))
		return "YES";

	else
		return "NO";
}

string abbreviation(string a, string b) {

	vector<vector<bool>> table(b.size() + 1, vector<bool>(a.size() + 1, false));

	table[0][0] = true;

	for (size_t i = 1; i < table[0].size(); i++)
		if (islower(a[i - 1]) && table[0][i - 1])
			table[0][i] = true;

	for (size_t i = 1; i <= b.size(); i++) 
		for (size_t j = 1; j <= a.size(); j++) {
			
			if (isupper(a[j - 1])) {

				if (a[j - 1] == b[i - 1])
					table[i][j] = table[i - 1][j - 1];
				else
					table[i][j] = false;
			}
			else {
			
				if (toupper(a[j-1]) == b[i-1])
					table[i][j] = table[i - 1][j - 1] || table[i][j - 1];
				else 
					table[i][j] = table[i][j - 1];
			}
		}

	if (table[b.size()][a.size()] == 1)
		return "YES";
	else return "NO";
}

void run_tests(string filename, vector<string> output) {

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

		fs >> temp1;
		fs >> temp2;

		n--;

		auto start = std::chrono::system_clock::now();
		auto t1 = std::chrono::system_clock::to_time_t(start);
		//cout << "start time: " << std::ctime(&t1) << endl;
		auto res = abbreviation(temp1, temp2);
		auto end = std::chrono::system_clock::now();
		auto t2 = std::chrono::system_clock::to_time_t(end);
		//cout << "end time: " << std::ctime(&t2) << endl;
		cout << "output: " << res << ", expected: " << output[i]
			<< "\t takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;

		i++;
	}

	fs.close();
}

void sample_tests() {

	cout << "Sample tests" << endl;

	string a, b, res;

	a = "daBcd"; //Sample Test case 0
	b = "ABC";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "AbCdE"; //Sample Test case 1.1
	b = "AFE";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: NO" << endl;

	a = "beFgH"; //Sample Test case 1.2
	b = "EFG";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: NO" << endl;

	a = "beFgH"; //Sample Test case 1.3
	b = "EFH";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "ERr"; //my
	b = "ER";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "aCbc"; //my
	b = "ABC";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: NO" << endl;

	a = "aaaa"; //my
	b = "AAA";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "abcB"; //my
	b = "ABC";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: NO" << endl;

	a = "aAAA"; //my
	b = "AAAA";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "ERreErR"; //my
	b = "ERREERR";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	a = "AAAa"; //my
	b = "AAAA";
	res = abbreviation(a, b);
	cout << "output: " << res << ", expected: YES" << endl;

	cout << endl;
}

void test_case_01() {

	cout << "Test case 01" << endl;
	run_tests("..\\tests\\test01.txt", { "YES", "NO", "NO", "YES", "NO", "YES", "YES", "YES", "NO", "NO" });
	cout << endl;
}

void test_case_13() {

	cout << "Test case 13" << endl;
	//run_tests("..\\tests\\test13.1.txt", { "YES"});
	run_tests("..\\tests\\test13.txt", { "YES", "NO", "YES", "NO", "NO", "NO", "YES", "YES", "NO", "YES" });
	cout << endl;
}

int main() {

	sample_tests();
	test_case_01();
	test_case_13();	
	
	return 0;
}