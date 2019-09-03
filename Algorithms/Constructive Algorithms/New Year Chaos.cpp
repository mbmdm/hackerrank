#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>
#include <chrono>


using namespace std;

void print(vector<int> &v) {
	cout << "source { ";
	for_each(v.begin(), v.end(), [](int &i) { cout << i << " "; });
	cout << "}" << endl;
}

int next_index(vector<int> &q, int index) {

	for (size_t i = index+1; i < q.size(); i++)
	{
		if (q[i] - q[index] == 1)
			return i;
	}

	return -1;
}

int index_of(vector<int> &q, int val) {
	
	for (size_t i = 0; i < q.size(); i++) {

		if (q[i] == val)
			return i;
	}

	return -1;
}

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {

	vector<int> bribes;
	bribes.resize(q.size());
	fill(bribes.begin(), bribes.end(), 0);

	int index = index_of(q, 1); //index of 1 into input array

	while (true) {

		int i = index;
		for (; i > 0; i--) {

			if (q[i - 1] > q[i]) {
				bribes[q[i - 1]-1]++;

				if (bribes[q[i - 1]-1] > 2) {
					cout << "Too chaotic" << endl;
					return;
				}

				swap(q[i - 1], q[i]);
			}
			else
				break;
		}

		index = next_index(q, i);

		if (index == q.size() - 1 && q[index] == index + 1)
			break;
	}

	int num = 0;
	for (size_t i = 0; i < q.size(); i++) {
		num += bribes[i];
	}

	cout << num << endl;
}

void test() {
	
	vector<int> v1 = { 2, 1, 5, 3, 4 };
	print(v1);
	minimumBribes(v1); //3

	vector<int> v2 = { 2, 5, 1, 3, 4 };
	print(v2);
	minimumBribes(v2); //Too chaotic

	vector<int> v3 = { 1, 2, 5, 3, 7, 8, 6, 4 };
	print(v3);
	minimumBribes(v3); //7
}

void test(vector<int> &v) {	
	minimumBribes(v);
}

int main()
{
	test();

	system("pause");

	return 0;
}