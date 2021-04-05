/*
https://www.hackerrank.com/challenges/largest-rectangle/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Complete the largestRectangle function below.
int64_t largestRectangle_01(vector<int> h) {

	vector<int64_t> areas;

	for (size_t i = 0; i < h.size(); i++) {

		int height = h[i];

		size_t j = i + 1;

		for (; j < h.size(); j++) {

			if (h[j] >= height)
				continue;

			int64_t area1 = height * (j - i);
			int64_t area2 = h[j] * (j - i + 1);

			if (area2 > area1)
				height = h[j];
			else
				break;
		}
		areas.push_back(height* (j - i));
	}

	int64_t result = 0;

	for_each(areas.begin(), areas.end(), [&result](auto& a) {
		if (a > result)
			result = a;
		});


	return result;
}

// brutal variant
int64_t largestRectangle_brutal(vector<int> h) {

	vector<int64_t> areas;

	for (size_t i = 0; i < h.size(); i++) {

		int min_height = h[i];
		int height = h[i];
		int64_t max_area = h[i];

		for (size_t j = i + 1; j < h.size(); j++) {

			if (h[j] >= height && height == min_height) {
				max_area += min_height;
				continue;
			}

			if (h[j] < min_height)
				min_height = h[j];
				
			int64_t area = min_height * (j - i + 1);

			if (area > max_area) {
				max_area = area;
				height = std::min(min_height, h[j]);
				min_height = height;
			}
		}
		areas.push_back(max_area);
	}

	int64_t result = 0;

	for_each(areas.begin(), areas.end(), [&result](auto& a) {
		if (a > result)
			result = a;
		});

	return result;
}

template <class itr>
void move_next(itr& left, itr& right, itr start, itr end) {
	
	if (right == end)
		return;

	if (left == start && right + 1 == end) {
		right++;
		return;
	}

	int left_val, right_val;
	left_val = right_val = numeric_limits<int>::min();

	if (left != start)
		left_val = *(left - 1);

	if (right + 1 != end)
		right_val = *(right + 1);

	if (left_val > right_val)
		left--;
	else
		right++;
}

template <typename itr>
int64_t largestRectangle(itr start, itr end, itr pivot) {

	if (start == end)
		return 0;

	itr left = pivot;
	itr right = pivot;

	int min_height = *pivot;
	int curr_height = *pivot;
	int64_t max_area = *pivot;

	do {

		auto height = std::min(*left, *right);
		auto len = std::distance(left, right) + 1;

		if (height >= curr_height && min_height == curr_height)
			max_area = len * curr_height;
		else {
			min_height = std::min(height, min_height);
			auto area = min_height * len;

			if (area > max_area) {
				curr_height = height;
				max_area = area;
			}
		}

		move_next(left, right, start, end);

	} while (right != end);
	
	return max_area;
}

template <typename itr>
int64_t largestRectangle(itr start, itr end) {

	if (start == end)
		return 0;

	int mid = (end - start) / 2;

	auto area1 = largestRectangle(start, end, start + mid);
	auto area2 = largestRectangle(start + mid + 1, end);
	auto area3 = largestRectangle(start, start + mid);
	
	return max(max(area1, area2), area3);
}

int64_t largestRectangle(vector<int> h) {

	return largestRectangle(h.begin(), h.end());
}

void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl;

	vector<int> h;
	int output;
	int64_t res;

	h = { 6320, 6020, 6098, 1332, 7263, 672, 9472, 2838, 3401, 9494 }; //Test case 2
	output = 18060;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	h = { 8979, 4570, 6436, 5083, 7780, 3269, 5400, 7579, 2324, 2116 }; //Test case 1
	output = 26152;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	h = { 1,2,3,4,5 }; //Sample Input
	output = 9;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	h = { 11,11,10,10,10 }; //Sample test case 2
	output = 50;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	h = { 5,4,3,2,1 }; //My
	output = 9;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	h = { 1,1,5,5,5,2,2,2,2,2,2 }; //My
	output = 18;
	res = largestRectangle(h);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	cout << endl;
}

int main() {

	sample_tests(true);

	cout << endl << "done." << endl;

	return 0;
}