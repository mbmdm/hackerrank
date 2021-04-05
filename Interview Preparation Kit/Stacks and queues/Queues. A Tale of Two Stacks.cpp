/*
https://www.hackerrank.com/challenges/ctci-queue-using-two-stacks/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <stack>

using namespace std;

//brutal queue
class MyQueue_ {

public:
	stack<int> stack_newest_on_top, stack_oldest_on_top;
	void push(int x) {
		stack_newest_on_top.push(x);
		stack<int> temp;
		while (!stack_oldest_on_top.empty()) {
			temp.push(stack_oldest_on_top.top());
			stack_oldest_on_top.pop();
		}
		temp.push(x);
		while (!temp.empty()) {
			stack_oldest_on_top.push(temp.top());
			temp.pop();
		}
	}

	void pop() {
		stack_oldest_on_top.pop();
		stack<int> temp;
		while (!stack_newest_on_top.empty()) {
			temp.push(stack_newest_on_top.top());
			stack_newest_on_top.pop();
		}
		temp.pop();
		while (!temp.empty()) {
			stack_newest_on_top.push(temp.top());
			temp.pop();
		}
	}

	int front() {
		return stack_oldest_on_top.top();
	}
};

class MyQueue {

public:
	stack<int> stack_newest_on_top, stack_oldest_on_top;
	int poisoned = 0;
	void push(int x) {
		stack_newest_on_top.push(x);
		if (stack_oldest_on_top.empty())
			stack_oldest_on_top.push(x);
	}

	void pop() {
		stack_oldest_on_top.pop();

		poisoned++;

		if (!stack_oldest_on_top.empty())
			return;

		stack<int> temp;
		while (!stack_newest_on_top.empty()) {
			temp.push(stack_newest_on_top.top());
			stack_newest_on_top.pop();
		}
		
		while (poisoned) {
			temp.pop();
			poisoned--;
		}

		stack_oldest_on_top = temp;

		while (!temp.empty()) {
			stack_newest_on_top.push(temp.top());
			temp.pop();
		}
	}

	int front() {
		return stack_oldest_on_top.top();
	}
};

void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl;

	vector<vector<int>> input;
	vector<int> output;
	vector<int>::iterator ptr;
	MyQueue q;

	input = { {1,35}, {1,15}, {3,0}, {2,0},{3,0} }; //example
	output = { 35,15 };
	q = MyQueue{};
	ptr = output.begin();
	for (size_t i = 0; i < input.size(); i++) {

		int res, out;

		switch (input[i][0])
		{
		case 1:
			q.push(input[i][1]);
			break;
		case 2:
			q.pop();
			break;
		case 3:
			res = q.front();
			out = *ptr;
			ptr++;
			if (res != out || debug)
				cout << "output: " << res << ", expected: " << out << endl;
		default:
			break;
		}
	}


	input = { {1,42}, {2,0}, {1,14}, {3,0}, {1,28}, {3,0}, {1,60}, {1,78}, {2, 0}, {2, 0} }; //Sample Input
	output = { 14,14 };
	q = MyQueue{};
	ptr = output.begin();
	for (size_t i = 0; i < input.size(); i++) {

		int res, out;

		switch (input[i][0])
		{
		case 1:
			q.push(input[i][1]);
			break;
		case 2:
			q.pop();
			break;
		case 3:
			res = q.front();
			out = *ptr;
			ptr++;
			if (res != out || debug)
				cout << "output: " << res << ", expected: " << out << endl;
		default:
			break;
		}
	}

	cout << endl;
}

int main() {

	sample_tests(true);

	cout << endl << "done." << endl;

	return 0;
}