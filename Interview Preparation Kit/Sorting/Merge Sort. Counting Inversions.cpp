#include <iostream>
#include <vector>

#define mtest

using namespace std;

void print(int *ptr, int size) {
	cout << "[ ";
	for (int i = 0; i < size; i++)
		cout << ptr[i] << " ";
	cout << "]";
}

void bubblesort(int *arr, int size, long *counter, int *buffer) {

	int mid = size / 2;

	int *left = arr;
	int *right = arr + mid;
	int lsize = mid;
	int rsize = size - mid;

	if (size > 1) {
		bubblesort(left, lsize, counter, buffer);
		bubblesort(right, rsize, counter, buffer);
	}
	else return;

#ifdef mtest

	cout << "merge: ";
	print(left, lsize);
	cout << " and ";
	print(right, rsize);
	cout << endl;

#endif // !mtest

	//merge
	int i = 0;
	while (lsize && rsize) {

		int &a = *left;
		int &b = *right;

		if (a > b) {
			buffer[i] = b;
			rsize--;
			if (rsize) right++;
			(*counter) += lsize;
		}
		else {
			buffer[i] = a;
			lsize--;
			if (lsize) left++;
		}
		i++;
	}

	while (lsize) {
		buffer[i] = *left;
		lsize--;
		if (lsize) left++;
		i++;
	}

	while (rsize) {
		buffer[i] = *right;
		rsize--;
		if (rsize) right++;
		i++;
	}

	memcpy(arr, buffer, size*sizeof(int));

#ifdef mtest

	cout << "result: ";
	print(arr, size);
	cout << ", counter = " << *counter << endl;

#endif // !mtest
}

long countInversions(vector<int> arr) {

	int *buffer = new int[arr.size()];
	int *sorted = new int[arr.size()];
	memcpy(sorted, arr.data(), arr.size() * sizeof(int));
	int counter = 0;
	bubblesort(sorted, arr.size(), &counter, buffer);
	return counter;
}

void test() {
	
	vector<int> v1 = { 2,4,1 };
	cout << "start task: ";	
	print(v1.data(), v1.size());
	cout << endl;
	cout << countInversions(v1) << " (right result 2)" << endl << endl;

	vector<int> v2 = { 1, 1, 1, 2, 2 };
	cout << "start task: ";
	print(v2.data(), v2.size());
	cout << endl;
	cout << countInversions(v2) << " (right result 0)" << endl << endl;

	vector<int> v3 = { 2, 1, 3, 1, 2 };
	cout << "start task: ";
	print(v3.data(), v3.size());
	cout << endl;
	cout << countInversions(v3) << " (right result 4)" << endl << endl;

	vector<int> v4 = { 7, 5, 3, 1 };
	cout << "start task: ";
	print(v4.data(), v4.size());
	cout << endl;
	cout << countInversions(v4) << " (right result 6)" << endl << endl;

}

int main()
{
	test();

	system("pause");

	return 0;
}