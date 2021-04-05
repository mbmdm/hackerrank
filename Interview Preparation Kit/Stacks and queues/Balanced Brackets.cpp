/*
https://www.hackerrank.com/challenges/balanced-brackets/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

inline char get_opposite(char ch) {

	switch (ch)
	{
	case ')':
		return '(';
	case '}':
		return '{';
	case ']':
		return '[';
	default:
		return '\0';
	}
}

// Complete the isBalanced function below.
string isBalanced(string s) {

	stack<char> st;
	st.push(s[0]);

	for (size_t i = 1; i < s.size(); i++) {

		if (!st.empty() && st.top() == get_opposite(s[i]))
			st.pop();
		else
			st.push(s[i]);
	}

	return st.empty() ? "YES" : "NO";
}


void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl;

	vector<string> input, output;

	input = { "{[()]}", "{[(])}", "{{[[(())]]}}" }; //Sample Input
	output = { "YES", "NO", "YES" };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = isBalanced(input[i]);
		if (debug || res != output[i])
			cout << "output: " << res << ", expected: " << output[i] << endl;
	}

	input = { "{(([])[])[]}", "{(([])[])[]]}", "{(([])[])[]}[]" }; //Tast case 2
	output = { "YES", "NO", "YES" };
	for (size_t i = 0; i < input.size(); i++) {
		auto res = isBalanced(input[i]);
		if (debug || res != output[i])
			cout << "output: " << res << ", expected: " << output[i] << endl;
	}

	cout << endl;
}

int main() {

	sample_tests(true);

	cout << endl << "done." << endl;

	return 0;
}