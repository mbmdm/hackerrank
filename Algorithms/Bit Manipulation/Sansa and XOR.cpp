#include <iostream>
#include <vector>

using namespace std;

// Complete the sansaXor function below.
int sansaXor_brutal(vector<int> arr) {

	if (arr.size() == 2)
		return arr[0] ^ arr[1];

	int result = 0;

	//aren't considering subarrays with size 1 and arr.size(). Operation ^ on each element of those subarrays gives us 0
	for (int l = 2; l < arr.size(); l++)
		for (int start = 0; start < arr.size() - l + 1; start++)
			for (int i = start; i < start + l; i++)
				result = result ^ arr[i];

	return result;
}

/**
	Function count how many times element with given index will met into all the subarrays
*/
size_t mcount(int pos, size_t size) {
	
	//aren't considering subarrays with size 1 and arr.size(). Operation ^ on each element of those subarrays gives us 0
	size_t result = 2;

	int l = 2;
	while (l != size) {
		
		int res = l;
		int start_idx = pos - l + 1;
		int end_idx = pos + l - 1;

		if (start_idx < 0)
			res += start_idx;
		if (end_idx >= size)
			res -= (end_idx - size - 1);

		result += res;
		l++;
	}

	return result;
}

// Complete the sansaXor function below.
int sansaXor_slow(vector<int> arr) {

	int result = 0;

	for (size_t i = 0; i < arr.size(); i++) {
		auto n = mcount(i, arr.size());
		if (n % 2 == 1)
			result = result ^ arr[i];
	}

	return result;
}

// Complete the sansaXor function below.
int sansaXor(vector<int> arr) {

	if (arr.size() % 2 == 0)
		return 0;

	int result = 0;

	auto n = mcount(0, arr.size());
	bool flag = (n % 2 == 0);

	for (size_t i = 0; i < arr.size(); i++) {
		if (!flag)
			result = result ^ arr[i];
		flag = !flag;
	}

	return result;
}


int main()
{
	cout << sansaXor({ 1,2,3 }) << endl;
	cout << sansaXor({ 4,5,7,5 }) << endl;
	cout << sansaXor({ 98,74,12 }) << endl;
	cout << sansaXor({ 50,13,2 }) << endl;

	system("pause");

	return EXIT_SUCCESS;
}

