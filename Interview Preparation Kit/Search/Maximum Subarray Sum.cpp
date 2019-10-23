#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Brutal Force algotithm. it work O(n^2)
int64_t maximumSum_BF(vector<int64_t> a, int64_t m) {

	vector<int64_t> prefix_sum;
	prefix_sum.resize(a.size());
	prefix_sum[0] = a[0];

	for (int64_t i = 1; i < a.size(); i++) {
		prefix_sum[i] = (prefix_sum[i - 1] + a[i]);
	}

	int64_t max = INT64_MIN;

	for (int64_t i = 0; i < a.size(); i++) {
		for (int64_t j = i; j < a.size(); j++) {

			int64_t a = (i - 1 < 0) ? 0 : prefix_sum[i - 1];
			int64_t sum = prefix_sum[j] - a;

			max = std::max(sum % m, max);
		}
	}

	return max;
}

// Optimal algotithm. it work O( n*lg(n) )
int64_t maximumSum(vector<int64_t> a, int64_t m) {

	int64_t current_sum = a[0] % m;
	int64_t max = current_sum;

	multiset<int64_t> prefix;

	prefix.insert(current_sum);

	for (int64_t i = 1; i < a.size(); i++) {
		current_sum += a[i];
		current_sum %= m;

		auto upper_it = prefix.upper_bound(current_sum);

		if (upper_it != prefix.end())
			max = std::max(max, m - ((*upper_it) - current_sum));

		max = std::max(max, current_sum);

		prefix.insert(current_sum);
	}

	return max;
}