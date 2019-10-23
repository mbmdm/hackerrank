#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <fstream>

using namespace std;

template <class T>
int hight_bit_idx(T a) {

	int index = -1;
	T test = 1;

	for (int i = 0; i < sizeof(size_t) * 8; i++) {
		if (a & test) index = i;
		test = test << 1;
	}

	return index;
}

template <class T>
bool mbit(T a, int index) {
	
	uint64_t test = 1;
	test = test << index;

	if (a & test) return true;
	else return false;
}

template <class T>
int lowest_joint_bit(T a, T b) {

	uint64_t test = 1;
	test = test << sizeof(T) * 8 - 1;

	for (int i = sizeof(T) * 8 - 1; i >= 0; i--) {
		
		bool flag1 = a & test;
		bool flag2 = b & test;

		if (flag1 != flag2)
			return i + 1;

		test = test >> 1;
	}

	return -1;
}

template <class T>
T fill_bit(T val, bool flag, int from, int to = 0) {
	
	uint64_t ref = 0;
	uint64_t test = 1;
	test = test << from;

	while (from >= to) {
		ref = ref | test;
		test >>= 1;
		from--;
	}

	if (flag)
		return val | ref;
	else {
		ref = ~ref;
		return val & ref;
	}
}

size_t best_value(size_t q, size_t max_of_arr) {

	if (q == 0) return max_of_arr;
	if (max_of_arr == 0) return 0;

	size_t right, left = 0;
	int hbit1, hbit2, hbit;

	hbit1 = hight_bit_idx(q);
	hbit2 = hight_bit_idx(max_of_arr);

	right = ~q;
	right = right << (sizeof(size_t) * 8 - hbit1 - 1);
	right = right >> (sizeof(size_t) * 8 - hbit1 - 1);

	if (hbit1 <= hbit2) {
		left = max_of_arr;
		left = left >> hbit1 + 1;
		left = left << hbit1 + 1;
	}
	else if (hbit2 != -1) {
		right = right << (sizeof(size_t) * 8 - hbit2 - 1);
		right = right >> (sizeof(size_t) * 8 - hbit2 - 1);
	}

	return right | left;
}

template <class Itr, class T>
T get_max_module2(Itr begin, Itr end, T q) {
	
	T max = numeric_limits<T>::min();

	while (begin != end) {
		
		max = std::max(max, *begin ^ q);
		begin++;
	}

	return max;
}

vector<int> maxXor(vector<int> arr, vector<int> queries) {

	vector<int> result;
	
	sort(arr.begin(), arr.end());
	auto max_of_arr = *(arr.end() - 1);

	for (int j = 0; j < queries.size(); j++) {

		int best = best_value((size_t)queries[j], (size_t)max_of_arr);
		auto target = lower_bound(arr.begin(), arr.end(), best);

		if (target != arr.end() && best == *target) {
			result.push_back(best ^ queries[j]);
			continue;
		}

		if (target == arr.end()) target--;

		int joint_bit = lowest_joint_bit(best, *target);

		auto v1 = fill_bit(best, false, joint_bit - 1); 
		auto v2 = fill_bit(best, true, joint_bit - 1);

		auto begin = lower_bound(arr.begin(), arr.end(), v1);
		auto end = lower_bound(arr.begin(), arr.end(), v2);

		if (end != arr.end()) end++;

		result.push_back(get_max_module2(begin, end, queries[j]));
	}

	return result;
}

void simple_tests() {

	vector<int> res;
	
	res = maxXor({ 9 }, { 20 });
	for_each(res.begin(), res.end(), [](int &a) {cout << a << " ";  });
	cout << endl;

	res = maxXor({ 0,1,2 }, { 3,7,2 });
	for_each(res.begin(), res.end(), [](int &a) {cout << a << " ";  });
	cout << endl;

	res = maxXor({ 5,1,7,4,3 }, { 2,0 });
	for_each(res.begin(), res.end(), [](int &a) {cout << a << " ";  });
	cout << endl;
	
	res = maxXor({ 1, 3, 5, 7 }, { 17,6 });
	for_each(res.begin(), res.end(), [](int &a) {cout << a << " ";  });
	cout << endl;
}

int compare(vector<int> &a, vector<int> &b) {

	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i]) return i;

	return -1;
}

int main()
{
	simple_tests();

	system("pause");

	return 0;
}