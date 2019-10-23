#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <Windows.h>

#define mdebug
#define show_done

using namespace std;

char min_counter(vector<int> &counter, char start = 'a') {
	
	for (size_t i = start - 'a'; i < counter.size(); i++) 
		if (counter[i] != 0)
			return 'a' + i;

	return -1;
}

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {

	vector<int> counter, ratio;
	int last_pushed_index = s.size();
	char min_char, max_char;
	string result;
	string::iterator ptr_s = s.end();

	ratio.resize(s.size());
	counter.resize('z' - 'a' + 1);

	for (size_t i = 0; i < s.size(); i++) {
		counter[s[i] - 'a']++;
		ratio[i] = counter[s[i] - 'a'];
	}

	for_each(counter.begin(), counter.end(), [](auto &a) { a /= 2; });

	min_char = min_counter(counter);

#ifdef mdebug

	fstream fs{};
	fs.open("test.txt", ios::out);
	for (size_t i = 0; i < counter.size(); i++)
		fs << (char)(i + 'a') << " - " << counter[i] << endl;
	fs << endl;

#endif
	
	for (int i = s.size() - 1; i >=0; i--) {

		char	i_char		= s[i];
		int &	i_ratio		= ratio[i];
		int &	i_counter	= counter[i_char - 'a'];

#ifdef mdebug
		fs << "i" << i << ": '" << i_char << "', left " << ratio[i] << ", need " << counter[i_char - 'a'];
#endif
		if (i_char == min_char) {

			result.push_back(i_char);
			last_pushed_index = i;
			i_counter--;
#ifdef mdebug
			fs << ", pushed (min_char)";
#endif
			if (i_counter == 0) {
				min_char = min_counter(counter, min_char + 1);
#ifdef mdebug
				fs << ", min_char = " << min_char;
#endif
			}
		}

		else if (i_ratio == i_counter) {

			string::iterator min_ptr	= s.end();
			string::iterator ptr		= s.begin() + last_pushed_index - 1;
			string::iterator stop		= s.begin() + i;
			
			//init min_ptr
			while (ptr != stop) {

				if (*ptr <= i_char && counter[*ptr - 'a'] != 0) {
					min_ptr = ptr;
					ptr--;
					break;
				}

				ptr--;
			}

			//init the best choise for min_ptr
			while (ptr != stop) {

				if (*ptr < *min_ptr && counter[*ptr - 'a'] != 0) {
					min_ptr = ptr;
				}

				ptr--;
			}

			if (min_ptr == s.end()) {
				result.push_back(i_char);
				last_pushed_index = i;
				i_counter--;
#ifdef mdebug
				fs << ", pushed (must)";
#endif
			}
			else {
				i = min_ptr - s.begin();
				result.push_back(*min_ptr);
				last_pushed_index = i;
				counter[*min_ptr - 'a']--;
#ifdef mdebug
				fs << ", pushed by get_back (must)";
#endif
			}
		}
		
#ifdef mdebug
		fs << endl;
		fs << "step result: " << result << endl;
		fs << "step till last pushed: " << s.substr(i, last_pushed_index - i) << endl;
		fs << endl;
		fs.flush();
#endif
	}
#ifdef mdebug
	fs << "result: " << result << endl;
	fs.close();
#endif

	return result;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

string mread(string file) {

	string path = ExePath();

	ifstream fs{};
	fs.open(path + "\\" + file, ios::in);

	string result;

	fs >> result;

	fs.close();

	return result;
}

void test() {

	string input, result, output;

#ifdef show_done
	//common cases
	cout << reverseShuffleMerge("eggegg") << " / egg" << endl;
	cout << reverseShuffleMerge("abcdefgabcdefg") << " / agfedcb" << endl;
	cout << reverseShuffleMerge("aeiouuoiea") << " / aeiou" << endl;
	cout << endl;

	//test case 1
	input = "bdabaceadaedaaaeaecdeadababdbeaeeacacaba";
	result = "aaaaaabaaceededecbdb";
	output = reverseShuffleMerge(input);
	if (output != result)
		cout << "test case 1 failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case 1 done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//test case 2
	input  = "djjcddjggbiigjhfghehhbgdigjicafgjcehhfgifadihiajgciagicdahcbajjbhifjiaajigdgdfhdiijjgaiejgegbbiigida";
	result = "aaaaabccigicgjihidfiejfijgidgbhhehgfhjgiibggjddjjd";
	output = reverseShuffleMerge(input);
	if (output != result)
		cout << "test case 2 failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case 2 done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//test case 3
	input = mread("data3_source.txt");
	result = mread("data3_result.txt");
	output = reverseShuffleMerge(input);
	if (output != result) {
		cout << "test case 3 failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
#ifdef mdebug
		for (size_t i = 0; i < result.size(); i++)
		{
			if (result[i] != output[i]) {
				cout << "start wrong index " << i << endl;
				cout << "right substr - " << output.substr(0, i) << endl;
				break;
			}
		}
#endif
	}
	else {
		cout << "test case 3 done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//test case 4
	input = mread("data4_source.txt");
	result = mread("data4_result.txt");
	output = reverseShuffleMerge(input);
	if (output != result) {
		cout << "test case 4 failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
#ifdef mdebug
		for (size_t i = 0; i < result.size(); i++)
		{
			if (result[i] != output[i]) {
				cout << "start wrong index " << i << endl;
				cout << "right substr - " << output.substr(0, i) << endl;
				break;
			}
		}
#endif
	}
	else {
		cout << "test case 4 done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//test case 10
	input = "aegeaggg";
	result = "gaeg";
	output = reverseShuffleMerge(input);
	if (output != result) {
		cout << "test case 10 failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
#ifdef mdebug
		for (size_t i = 0; i < result.size(); i++)
		{
			if (result[i] != output[i]) {
				cout << "start wrong index " << i << endl;
				cout << "right substr - " << output.substr(0, i) << endl;
				break;
			}
		}
#endif
	}
	else {
		cout << "test case 10 done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;
#endif

}

int main()
{
	test();

	system("pause");

	return 0;
}