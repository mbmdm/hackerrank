/*
	https://www.hackerrank.com/challenges/find-the-nearest-clone/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=graphs
*/

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef typename tuple<int, vector<int>, vector<int>, vector<int64_t>, int> input_type;

bool is_there_no_solution(const vector<int64_t>& ids, int val) {
	
	int counter = 0;

	std::for_each(ids.begin(), ids.end(), [&counter, &val](const int& a) {
		if (a == val)
			counter++;
		});

	if (counter <= 1)
		return true;
	
	return false;
}

struct node {

	size_t idx;
	size_t color;
	vector<size_t> links;

	node(size_t i, size_t c) : idx{ i }, color{ c }{}
};

typedef vector<node> tree;

tree make_tree(vector<int> graph_from, vector<int> graph_to, vector<int64_t> ids) {

	tree outcome;
	
	for (size_t i = 0; i < ids.size(); i++)
		outcome.emplace_back( i + 1, ids[i]);

	for (size_t i = 0; i < graph_from.size(); i++) {
		auto a = graph_from[i];
		auto b = graph_to[i];

		outcome[a - 1].links.push_back(b);
		outcome[b - 1].links.push_back(a);
	}

	return outcome;
}

size_t calc_len_(tree& t, size_t curr_idx, size_t color, vector<bool>& markers) {
	
	auto& curr = t[curr_idx - 1];
	size_t len = std::numeric_limits<size_t>::max();

	markers[curr_idx - 1] = true;

	if (curr.color != color) {

		for (size_t i = 0; i < curr.links.size(); i++) {

			auto& next = t[curr.links[i]- 1];
			if (markers[next.idx - 1])
				continue;

			auto l = calc_len_(t, next.idx, color, markers);
			len = std::min(l, len);
		}

		if (len == std::numeric_limits<size_t>::max())
			return len;
		else
			return len + 1;
	}
	else
		return 1;
}

size_t calc_len(tree& t, size_t curr_idx, size_t color) {
	
	vector<bool> markers(t.size(), false);
	markers[curr_idx - 1] = true;
	auto& curr = t[curr_idx - 1];
	size_t len = std::numeric_limits<size_t>::max();

	for (size_t i = 0; i < curr.links.size(); i++) {

		auto& next = t[curr.links[i] - 1];
		auto l = calc_len_(t, next.idx, color, markers);
		if (l != numeric_limits<size_t>::max())
			len = std::min(len, l);
	}

	return len;
}

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<int64_t> ids, int val) {
	
	if (is_there_no_solution(ids, val))
		return -1;

	tree t = make_tree(graph_from, graph_to, ids);
	size_t len = std::numeric_limits<size_t>::max();

	for (size_t i = 0; i < t.size(); i++) {

		auto& n = t[i];
		if (n.color == val)
			len = std::min(len, calc_len(t, n.idx, val));

		cout << "";
	}

	if (len == std::numeric_limits<size_t>::max())
		return -1;

	return len;
}

template <class func>
void run_test(string case_name, func f, input_type input, int output, bool debug = true, string endstr = "\n") {

	int graph_nodes, val;
	vector<int> graph_from, graph_to;
	vector<int64_t> ids;
	std::tie(graph_nodes, graph_from, graph_to, ids, val) = input;

	auto start = std::chrono::system_clock::now();
	auto res = f(graph_nodes, graph_from, graph_to, ids, val);
	auto end = std::chrono::system_clock::now();

	cout << case_name << ":\t";

	if (debug) {
		if (res == output) cout << "OK" << endl;
		else cout << "FAILED" << endl;

		cout << "output: " << res << ", expected: " << output;
		cout << ", time(milli sec): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		cout << ", time(micro sec): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		cout << endl;
	}
	else if (res != output)
		cout << "FAILED\n" << "output: " << res << ", expected: " << output << endl;

	else
		cout << "OK" << endl;

	cout << endstr;
}

void run_tests(bool debug = true) {

	string endstr = (debug) ? "\n" : "";

	cout << "Sample tests" << endl << endl;

	run_test("in description 1",	findShortest, { 5, {1,2,2,3}, {2,3,4,5}, {1,2,3,1,3}, 1 }, 2, debug, endstr);
	run_test("in description 2",	findShortest, { 5, {1,2,2,3}, {2,3,4,5}, {1,2,3,1,3}, 2 }, -1, debug, endstr);
	run_test("in description 3",	findShortest, { 5, {1,2,2,3}, {2,3,4,5}, {1,2,3,1,3}, 3 }, 1, debug, endstr);
	run_test("my 1",				findShortest, { 10, {1,2,3,4,4,5,6,7,8,9}, {2,3,4,5,10,6,7,8,9,10}, {1,2,3,4,5,1,7,8,9,1}, 1 }, 3, debug, endstr);
	run_test("Sample Input 0",		findShortest, { 4, {1,1,4}, {2,3,2}, {1,2,1,1}, 1 }, 1, debug, endstr);
	run_test("Sample Input 1",		findShortest, { 4, {1,1,4}, {2,3,2}, {1,2,3,4}, 2 }, -1, debug, endstr);
	run_test("Sample Input 2",		findShortest, { 5, {1,1,2,3}, {2,3,4,5}, {1,2,3,3,2}, 2 }, 3, debug, endstr);

	//Test from files
	//auto test19 = read_file<vector<int>, int>("..\\tests\\test19_in.txt", "..\\tests\\test19_out.txt");
	//run_test("Test case 19", poisonousPlants, test19.input, test19.output, debug, endstr);
}

int main() {

	run_tests(true);

	cout << "done." << endl;

	int temp;
	cin >> temp;

	return 0;
}