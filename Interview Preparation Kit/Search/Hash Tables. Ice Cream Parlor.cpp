#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

#define mdebug

typedef vector<int>::iterator mitr;

//bynary search. return the index of element
int bsearch(mitr begin, mitr end, int v) {

	if (begin == end) return -1;

	mitr mid = begin + (end - begin) / 2;

	if (*mid == v) return mid - begin;

	if (begin == mid) return -1;

	if (*mid > v)
		return bsearch(begin, mid, v);
	else {
		auto temp = bsearch(mid + 1, end, v);
		if (temp == -1) return temp;
		else return (mid - begin) + temp + 1;
	}
}

int bsearch(int *arr, size_t size, int v) {
	
	if (size == 0) return -1;
	if (size == 1 && *arr != v) return -1;

	int *mid = arr + size / 2;

	if (*mid == v) return mid - arr;

	if (*mid > v)
		return bsearch(arr, mid - arr, v);
	else if (mid != arr + size - 1) {
		auto temp = bsearch(mid + 1, size - (mid - arr + 1), v);
		if (temp == -1) return temp;
		else return (mid - arr) + temp + 1;
	}
	else return -1;
}


//return two lements (there values) of array cost
pair<int, int> mfind(vector<int> &cost, int money) {

	vector<int> v;
	v.resize(cost.size());
	copy(cost.begin(), cost.end(), v.begin());

	sort(v.begin(), v.end());

	for (size_t i = 0; i < v.size() - 1; i++) {
		int a = v[i];
		int j = bsearch(v.begin() + i + 1, v.end(), money - a);

		if (j != -1) {
			int b = v[i + j + 1];
			return make_pair(a, b);
		}
	}

	return make_pair(-1, -1);
}

// Complete the whatFlavors function below.
#ifdef mdebug
	string whatFlavors(vector<int> cost, int money) {
#else
	void whatFlavors(vector<int> cost, int money) {
#endif
	
	//find indexes of two elements
	auto p = mfind(cost, money);
	if (p.first == -1 || p.second == -1)
#ifdef mdebug
		return "errors";
#else
		cout << "error" << endl;
#endif

	
	auto result = pair<int, int>{-1, -1};
	for (size_t i = 0; i < cost.size(); i++)
	{
		if (cost[i] == p.first && result.first == -1)
			result.first = i + 1;
		else if (cost[i] == p.second && result.second == -1)
			result.second = i + 1;
	}

	int i1 = min(result.first, result.second);
	int i2 = max(result.first, result.second);

#ifdef mdebug
	return to_string(i1) + " " + to_string(i2);
#else
	cout << i1 << " " << i2 << endl;
#endif
}

	void bsearch_test() {
	
		/*vector<int> temp = { 0,1,2 };

		int r1 = bsearch(temp.data(), temp.size(), 0);
		int r2 = bsearch(temp.data(), temp.size(), 1);
		int r3 = bsearch(temp.data(), temp.size(), 2);
		int r4 = bsearch(temp.data(), temp.size(), 99);

		return;*/

		vector<int> v;
		cout << "v.size() = " << v.size() << endl;
		cout << bsearch(v.data(), v.size(), 0) << endl << endl;

		int n = 10, i = 0;

		while (i != n) {
			
			v.push_back(i);
			cout << "v.size() = " << v.size() << endl;
			for (size_t j = 0; j <= v.size(); j++)
			{
				cout << bsearch(v.data(), v.size(), j) << " ";
			}
			
			cout << endl << endl;
			i++;		
		}

	}

void test() {

#ifdef mdebug

	string case_number;
	vector<int> input;
	string result, output;
	int money;
	
	//################################################################
	case_number = "0.1";
	input = { 1,4,5,3,2 };
	money = 4;
	result = "1 4";
	output = whatFlavors(input, money);
	if (output != result)
		cout << "test case " << case_number << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << case_number << " done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//################################################################
	case_number = "0.2";
	input = { 2,2,4,3 };
	money = 4;
	result = "1 2";
	output = whatFlavors(input, money);
	if (output != result)
		cout << "test case " << case_number << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << case_number << " done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//################################################################
	case_number = "1";
	input = {1,2,3,5,6};
	money = 5;
	result = "2 3";
	output = whatFlavors(input, money);
	if (output != result) 
		cout << "test case " << case_number << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << case_number << " done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

	//################################################################
	case_number = "2";
	input = { 7,2,5,4,11 };
	money = 12;
	result = "1 3";
	output = whatFlavors(input, money);
	if (output != result)
		cout << "test case " << case_number << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << case_number << " done" << endl;
		cout << "result: " << output << endl;
	}
	cout << endl;

#else
	cout << "define mdebug" << endl;
#endif
}

int main()
{
	bsearch_test();

	test();

	system("pause");

	return 0;
}