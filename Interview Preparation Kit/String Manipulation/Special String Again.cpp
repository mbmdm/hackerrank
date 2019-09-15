#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <Windows.h>

using namespace std;

#define mdebug

template <class T>
void print(T *ptr, int size, bool endline = true) {

#ifdef mdebug

	cout << "{ ";

	for (size_t i = 0; i < size; i++)
	{
		cout << ptr[i] << " ";
	}

	cout << "}\t";

	if (endline)
		cout << endl;

#endif // mdebug

}

void print(string s, int start, int end) {
	
#ifdef mdebug

	cout << start << "..." << end;
	cout << " - { ";
	while (start != end) {
		cout << s[start];
		start++;
	}
	cout << s[end] << " }";

#endif // mdebug

}

bool is_special(string &s, size_t &start, size_t &end) {

	bool condition1 = true;
	bool condition2 = true;

	int pivot = -1;

	//condition 1
	for (size_t i = start + 1; i <= end; i++) {
		if (condition1 && s[i] != s[i - 1]) {
			condition1 = false;
			pivot = i;
			break;
		}
	}

	//condition 2
	if (pivot - start != end - pivot)
		condition2 = false;
	
	else {
		for (size_t i = pivot + 1; i <= end; i++) {

			if (s[start] != s[i]) {
				condition2 = false;
				break;
			}
		}
	}

	return condition1 || condition2;
}

// Complete the substrCount function below.
long substrCount_1(int n, string s) {

	int counter = s.size();

	for (int i = 0; i < n; i++)
		print(s, i, i);

	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			if (is_special(s, i, j)) {
				//print(s, i, j);
				counter++;
			}
		}

	}

	return counter;
}

// Complete the substrCount function below.
long substrCount_2(int n, string s) {

	int counter = s.size();

	for (int i = 0; i < n; i++)
		print(s, i, i);

	for (size_t l = 2; l <= n; l++)
	{
		for (size_t i = 0; i <= n - l; i++)
		{
			size_t j = i + l - 1;
			if (is_special(s, i, j)) {
				print(s, i, j);
				counter++;
			}
		}

	}

	return counter;
}

// Complete the substrCount function below.
long substrCount(int n, string s) {

	int counter = s.size();

	//condition 1
	char target = '\0';
	size_t local_counter = 0;
	for (size_t i = 0; i < n; i++) {

		if (target == s[i]) {
			local_counter++;
			//print(s, i - local_counter + 1, i);
			//cout << ", strings = " << local_counter - 1 << endl;
			counter += local_counter - 1;
		}
		else {
			target = s[i];
			local_counter = 1;
		}
	}

	//condition 2
	target = s[0];
	local_counter = 1;
	for (size_t i = 1; i < n - 1; i++) {
		
		if (s[i] != target) {

			char *ptr1 = &s[i - local_counter];
			char *ptr2 = &s[i + 1];

			if (i + local_counter >= n)
				local_counter = n - 1 - i;

			while (local_counter) {

				auto cmp = memcmp(ptr1, ptr2, local_counter * sizeof(char));

				if (cmp == 0) {
					//print(s, i - local_counter, i + local_counter);
					//cout << endl;
					counter++;
				}
			
				local_counter--;
			}

			target = s[i];
			local_counter = 1;
		}
		else {
			local_counter++;
		}
	}

	return counter;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test() {

	string s1 = "ccccbc";
	cout << substrCount(s1.size(), s1) << "" << endl;
	
	
	cout << substrCount(4, "aaaa") << " / 10" << endl;
	cout << substrCount(7, "abcbaba") << " / 10" << endl;
	cout << substrCount(5, "asasd") << " / 7" << endl;
	cout << substrCount(8, "mnonopoo") << " / 12" << endl;

	
}

void test(string file, int expected_result) {

	cout << "start test from " << file << ":" << endl;

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + file, ios::in);

	int n;
	string str;

	fs_data >> n;
	str.resize(n);
	fs_data >> str;

	fs_data.close();

	auto start = chrono::system_clock::now();
	cout << substrCount(n, str) << " / " << expected_result;
	auto end = chrono::system_clock::now();
	cout << ", time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

}

int main()
{
	//test();

	test("data2.txt", 1272919);
	
	test("data4.txt", 1220450);

	system("pause");

	return 0;
}