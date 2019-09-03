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

bool right_position(vector<int> &arr, int i) {
	if (arr[i] == i + 1) return true;
	else return false;
}

int get_to_swap(vector<int> &arr, int index) {
	for (size_t i = index + 1; i < arr.size(); i++)
		if (arr[i] == index + 1) return i;
	return -1;
}

int minimumSwaps(vector<int> arr) {
	int counter = 0;
	for (size_t i = 0; i < arr.size(); i++) {
		if (right_position(arr, i))
			continue;
		int j = get_to_swap(arr, i);
		swap(arr[i], arr[j]);
		counter++;
	}
	return counter;
}

using namespace std;

void test() {
	vector<int> v1 = { 7, 1, 3, 2, 4, 5, 6 }; //5
	print(v1);
	cout << minimumSwaps(v1) << endl << endl;

	vector<int> v2 = { 4, 3, 1, 2 }; //3
	print(v2);
	cout << minimumSwaps(v2) << endl << endl;

	vector<int> v3 = { 2, 3, 4, 1, 5 }; //3
	print(v3);
	cout << minimumSwaps(v3) << endl << endl;

	vector<int> v4 = { 1, 3, 5, 2, 4, 6, 7 }; //3
	print(v4);
	cout << minimumSwaps(v4) << endl << endl;
}

int main()
{
	test();

	system("pause");

	return 0;
}