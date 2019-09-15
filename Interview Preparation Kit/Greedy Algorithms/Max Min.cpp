#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;

// Complete the maxMin function below.
int maxMin(int k, vector<int> arr) {

	int min = INT32_MAX;

	sort(arr.begin(), arr.end());

	for (int i = 0; i <= arr.size() - k; i++) {

		int a = arr[i];
		int b = arr[i + k - 1];
		min = min(b-a, min);
	}

	return min;
}


void test() {
	
	cout << maxMin(3, { 10,100,300,200,1000,20,30 }) << " / 20" << endl;
	cout << maxMin(4, { 1,2,3,4,10,20,30,40,100,200 }) << " / 3" << endl;
	cout << maxMin(2, { 1,2,1,2,1 }) << " / 0" << endl;
}

int main()
{
	test();

	system("pause");

	return 0;
}