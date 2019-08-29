#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>

#include <sstream>

//

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w) {

	char *begin = new char[w.size() + 1];
	char *end = begin + w.size();
	memcpy(begin, w.c_str(), w.size());
	*end = 127;

	int flag = -1;
	char *pivot = nullptr;
	for (char *ptr = (end-1); ; ptr--) {

		if (*ptr >= flag) {
			pivot = ptr;
			flag = *ptr;
		}
		else break;

		if (ptr == begin)
			break;
	}

	if (pivot == begin) 
		return "no answer";
	else if (pivot == end - 1) {
		swap(*(pivot - 1), *pivot);
	}
	else {
		char *swap1 = pivot - 1;
		char *swap2 = pivot;
		for (char *ptr = pivot + 1; ptr < end; ptr++) {
			if (*ptr < *swap2 && *ptr > *swap1) {
				swap2 = ptr;
			}
		}
		swap(*swap1, *swap2);
		sort(pivot, end); //here we can reverse the sequence {pivot ... end} by O(n) insted of using sort()
	}

	*end = '\0';
	string output{ begin };
	int i = output.size();
	delete[] begin;
	return output;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}


bool test(string source, string result) {

	string temp = biggerIsGreater(source);

	if (result != temp) {
		cout << "FAILED\t" << "next str for source \"" << source << "\" shoud be \"" << result << "\", but we got \"" << temp << "\"" << endl;
		return false;
	}
	else {
		cout << "OK\t" << "next str for source \"" << source << "\" is \"" << temp << "\"" << endl;
		return true;
	}
}

void test2(string data_file, string result_file) {

	string path = ExePath();

	ifstream fs_data{};
	fs_data.open(path + "\\" + data_file, ios::in);

	ifstream fs_result{};
	fs_result.open(path + "\\" + result_file, ios::in);

	string data, result;

	while (!fs_data.eof()) {

		getline(fs_data, data);
		getline(fs_result, result);

		if (test(data, result)) {}
		else
		{
			cout << "!!!!!!!!!!!!" << endl;
		}
	}

	fs_data.close();
	fs_result.close();
}

int main() {
	
	test("megcc", "mgcce");

	cout << endl;

	test("ab", "ba");
	test("bb", "no answer");
	test("hefg", "hegf");
	test("dhck", "dhkc");
	test("dkhc", "hcdk");

	cout << endl;
	
	test("lmno", "lmon");
	test("dcba", "no answer");
	test("dcbb", "no answer");
	test("abdc", "acbd");
	test("abcd", "abdc");
	test("fedcbabcd", "fedcbabdc");
	
	cout << endl;

	test("zyyyvvvvvuttsrqqokjjheedccb", "no answer");
	test("vvvygfabrsqeitgelpxwodhdfyypoyufxnecmrtkbzbhzfbtvnffcmikqoosfzoozssonomkgmtdqfecrqtps",
		 "vvvygfabrsqeitgelpxwodhdfyypoyufxnecmrtkbzbhzfbtvnffcmikqoosfzoozssonomkgmtdqfecrqtsp");
	test("zzzzyyxxxwvvvvusssrrrrqqqqqqqppoonnnnmmmmllllkjiiigfccccbbba", "no answer");

	cout << endl;

	test2("data2.txt", "results2.txt");

	system("pause");

	return 0;
}