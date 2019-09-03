#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

void print(vector<int> &v) {
	for_each(v.begin(), v.end(), [](int &i) {cout << i << " "; });
	cout << endl;
}

// Complete the climbingLeaderboard function below.
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {

	vector<int> result;

	vector<int>::iterator ptr = scores.begin();
	ptr++;

	while (ptr != scores.end()) {
		
		auto prev_ptr = ptr - 1;

		if (*ptr == *prev_ptr)
			ptr = scores.erase(ptr);
		else 
			ptr++;
	}

	//to use upper_bound() elements at the array must be sorted according operator<
	std::reverse(scores.begin(), scores.end());	

	for (size_t i = 0; i < alice.size(); i++) {
		//complexity of upper_bound() is O(lg(n))
		auto res = std::upper_bound(scores.begin(), scores.end(), alice[i]);
		result.push_back(scores.end() - res + 1);
	}

	return result;
}

void test() {
	vector<int> scores = { 100,100,50,40,40,20,10 };
	vector<int> alice = { 5,25,50,120 };

	auto result = climbingLeaderboard(scores, alice);
	print(result);
	cout << endl;

	scores = { 100, 90, 90, 80, 75, 60 };
	alice = { 50, 65, 77, 90, 102 };
	result = climbingLeaderboard(scores, alice);
	print(result);
	cout << endl;

}

int main()
{
	setlocale(LC_ALL, "Russian"); //test

	cout << "The program started" << endl;

	//Enter your code here
	test();

	system("pause");

	return 0;
}