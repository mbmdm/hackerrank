#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <Windows.h>
#include <map>
#include <set>

#define mdebug

using namespace std;

// Complete the getMinimumCost function below.
int getMinimumCost(int k, vector<int> c) {

	int i		= 0;
	int price	= 0;
	int pk		= 0;
	int bought	= 0;
	int k_		= k;

	sort(c.begin(), c.end(), [](int &a, int &b) {return a > b; });

	while (bought != c.size()) {

		price += c[i] * (1 + pk);

		k_--;
		i++;
		i = i % c.size();

		if (k_ == 0) {
			pk++;
			k_ = k;
		}

		bought++;
	}

	return price;
}

void test() {

	cout << getMinimumCost(3, {2,5,6}) << " / 13" << endl;
	cout << getMinimumCost(3, { 1,3,5,7,9 }) << " / 29" << endl;

}

int main()
{
	test();

	system("pause");

	return 0;
}