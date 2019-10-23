#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <queue>
#include <chrono>

using namespace std;

//brutal force algorithm
void stepPerms_counter1(int n, int *counter) {
	
	if (n == 0) {
		*counter += 1;
		return;
	}
	
	if (n >= 3)
		stepPerms_counter1(n - 3, counter);
	if (n >= 2)
		stepPerms_counter1(n - 2, counter);
	if (n >= 1) 
		stepPerms_counter1(n - 1, counter);

}

//recursive method replaced by while cycle
int stepPerms_counter2(int n) {

	deque<char> steps;
	
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else if (n == 3)
		return 4;

	steps.push_back(n);

	uint64_t counter = 0;

	while (steps.size() != 0) {
		
		auto a = steps.front(); //a can't be zero {0}
		steps.pop_front();

		auto b1 = a - 1;
		auto b2 = a - 2;
		auto b3 = a - 3;

		if (b1 >= 0) {
			if (b1 != 0) steps.push_back(b1);
			else counter++;
		}
		if (b2 >= 0) {
			if (b2 != 0) steps.push_back(b2);
			else counter++;
		}
		if (b3 >= 0) {
			if (b3 != 0) steps.push_back(b3);
			else counter++;
		}		
	}

	return counter;
}

//algorithm uses dynamic programming approach
int stepPerms_counter3(int n) {

	vector<int> cache;
	
	cache.resize(37); //cache[0] doesn't use

	cache[1] = 1;
	cache[2] = 2;
	cache[3] = 4;

	for (size_t i = 4; i <= n; i++) {

		cache[i] += cache[i - 3];
		cache[i] += cache[i - 2];
		cache[i] += cache[i - 1];
	}

	return cache[n];
}

// Complete the stepPerms function below.
int stepPerms(int n) {

	uint64_t m = 1e10 + 7; 

	int count = stepPerms_counter3(n);

	return count % m;
}

int main()
{	
	for (size_t i = 1; i < 14; i++)
	{
		auto start = chrono::system_clock::now();

		try {
			cout << "step i = " << i << ", result = " <<  stepPerms(i) << endl;
		}
		catch (bad_alloc &a) {
			cout << "step i = " << i << ", cought bad_alloc exception" << endl;
			break;
		}
		catch(...){
			cout << "step i = " << i << ", cought some exception" << endl;
			break;
		}

		auto end = chrono::system_clock::now();

		cout << "time = " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
	}

	cout << stepPerms(5) << endl;
	cout << stepPerms(1) << endl;
	cout << stepPerms(3) << endl;
	cout << stepPerms(7) << endl;

	system("pause");

	return 0;
}