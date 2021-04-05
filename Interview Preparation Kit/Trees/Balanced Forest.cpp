/*
https://www.hackerrank.com/challenges/balanced-forest/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=trees
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

template <class itr>
void print(itr begin, itr end){
    cout << "{ ";
    for_each(begin, end, [](auto &a){
        cout << a << " ";
    });
    cout << "}" << endl;
}

template <class T>
void print(vector<T> &v) {
    print(v.begin(), v.end());
}

template <class T>
ostream &operator<<(ostream &ost, vector<T> &v){
    print(v.begin(), v.end());
    return ost;
}

template <class T>
ostream &operator<<(ostream &ost, const pair<const T, T> &p){
    cout << "{" << p.first << ", " << p.second << "}";
    return ost;
}

#include <numeric>
#include <algorithm>

struct node {

	unsigned int idx;
	unsigned int root_idx;
	unsigned int weight;

	vector<unsigned int> children;
};

vector<uint64_t> calc_weights(const vector<node>& tree) {

	vector<uint64_t> weights(tree.size(), 0);

	for (size_t i = 0; i < tree.size(); i++)
		weights[i] = tree[i].weight;

	vector<int> processed(tree.size(), 0);

	for (int i = 0; i < tree.size(); i++) {

		if (tree[i].children.size() != 0)
			continue;

		uint32_t curr_idx = tree[i].idx; //const node* curr = &tree[i];
		uint64_t sum = 0;

		while(tree[curr_idx - 1].root_idx) { //while (curr->root_idx) {

			uint32_t root_idx = tree[curr_idx - 1].root_idx; //const node* root = &tree[curr->root_idx - 1];

			if (processed[root_idx - 1] && sum == 0)
				sum = weights[curr_idx - 1]; //curr->subtree_weight;

			if (sum != 0)
				weights[root_idx - 1] += sum; //weights[root->idx - 1] += sum;
			else
				weights[root_idx - 1] += weights[curr_idx - 1]; //curr->subtree_weight;

			curr_idx = root_idx; //curr = root;
			processed[root_idx - 1]++;
		}
	}

	return weights;
}

void increase_weights(const vector<node>& tree, vector<uint64_t>& weights, unsigned int node_idx) {

	auto curr_idx = node_idx;
	uint64_t amount = weights[node_idx - 1];

	while (tree[curr_idx - 1].root_idx) {
		
		auto root_idx = tree[curr_idx - 1].root_idx;
		weights[root_idx - 1] += amount;
		curr_idx = root_idx;
	}
}

void decrease_weights(const vector<node>& tree, vector<uint64_t>& weights, unsigned int node_idx) {

	auto curr_idx = node_idx;
	uint64_t amount = weights[node_idx - 1];

	while (tree[curr_idx - 1].root_idx) {

		auto root_idx = tree[curr_idx - 1].root_idx;
		weights[root_idx - 1] -= amount;
		curr_idx = root_idx;
	}
}

void erase_subtree(unsigned int idx, vector<node> &tree) {

	node& curr = tree[idx - 1];
	node& root = tree[curr.root_idx - 1];

	auto ptr = root.children.begin();
	while (ptr != root.children.end()) {
	
		if (*ptr == curr.idx) {
			root.children.erase(ptr);
			break;
		}

		ptr++;
	}
	
	curr.root_idx = 0;
}

void restore_tree(vector<node>& tree, unsigned int root_idx, unsigned int node_idx) {

	node& n = tree[node_idx - 1]; //node
	node& r = tree[root_idx - 1]; //root

	r.children.push_back(n.idx);
	n.root_idx = r.idx;
}

///converts c and edges into vector<node>
vector<node> prepare_tree(const vector<int> &c, const vector<vector<int>> &edges){
	
	vector<node> tree;
	tree.resize(c.size());

	for (size_t i = 0; i < c.size(); i++) {
		tree[i].weight = c[i];
		tree[i].idx = i + 1;
	}

	for_each(edges.begin(), edges.end(), [&](auto& v) {
		
		auto a = static_cast<size_t>(v[0]);
		auto b = static_cast<size_t>(v[1]);

		tree[a - 1].children.push_back(b);
		tree[b - 1].children.push_back(a);
		});

	vector<int> level_current, level_next;

	level_next.push_back(1);

	while (level_next.size() != 0) {
	
		level_current.clear();
		level_current.swap(level_next);

		for (size_t i = 0; i < level_current.size(); i++) {

			auto& curr_node = tree[level_current[i] - 1];
			auto child_ptr = curr_node.children.begin();

			while (child_ptr != curr_node.children.end()) {
				
				auto& child_node = tree[(*child_ptr) - 1];

				if (child_node.idx == curr_node.root_idx) {
				
					child_ptr = curr_node.children.erase(child_ptr);
					continue;
				}

				child_node.root_idx = curr_node.idx;
				level_next.push_back(*child_ptr);
				child_ptr++;
			}
		}
	}

	return tree;
}

int find_weight(vector<node>& tree, vector<uint64_t> &weights, uint64_t target_w, unsigned int root_idx = 1) {

	vector<unsigned int> current, next{ root_idx };

	while (next.size() != 0) {

		current.clear();
		current.swap(next);

		for (size_t i = 0; i < current.size(); i++) {

			auto curr_idx = current[i];

			if (weights[curr_idx - 1] == target_w)
				return curr_idx;

			if (weights[root_idx - 1] - weights[curr_idx - 1] == target_w)
				return curr_idx;

			next.insert(next.end(), tree[curr_idx - 1].children.begin(),
									tree[curr_idx - 1].children.end());
		}
	}

	return 0;
}

int64_t pass01(vector<node> &tree, vector<uint64_t> weights, vector<uint32_t> idxes /*sorted indexes of weights*/) {
	
	uint64_t best_subtree_weight = weights[0] / 3;
	if (weights[0] % 3 != 0)
		best_subtree_weight++;

	auto idx_es_ptr = idxes.begin();
	while (idx_es_ptr != idxes.end()) {
		if (weights[*idx_es_ptr - 1] >= best_subtree_weight) {
			best_subtree_weight = weights[*idx_es_ptr - 1];
			break;
		}
		idx_es_ptr++;
	}

	uint32_t root1_idx = 1;
	uint32_t root2_idx, rootroot2_idx;
	uint32_t root3_idx, rootroot3_idx;

	while (idx_es_ptr != idxes.end() - 1) {

		root2_idx = *idx_es_ptr;
		rootroot2_idx = tree[root2_idx - 1].root_idx;
		root3_idx = 0;
		rootroot3_idx = 0;
		best_subtree_weight = weights[root2_idx - 1];

		decrease_weights(tree, weights, root2_idx);
		erase_subtree(root2_idx, tree);

		if (weights[root2_idx - 1] > weights[root1_idx - 1]) {

			restore_tree(tree, rootroot2_idx, root2_idx);
			increase_weights(tree, weights, root2_idx);
			break;
		}

		root3_idx = find_weight(tree, weights, best_subtree_weight);

		if (root3_idx) {

			auto w3 = weights[root3_idx - 1];
			auto w2 = weights[root2_idx - 1];
			auto w1 = weights[root1_idx - 1] - w3;

			int64_t res;

			if (w3 == w2)
				res = w3 - w1;

			else
				res = w1 - w3;

			restore_tree(tree, rootroot2_idx, root2_idx);
			increase_weights(tree, weights, root2_idx);

			return res;
		}

		restore_tree(tree, rootroot2_idx, root2_idx);
		increase_weights(tree, weights, root2_idx);

		idx_es_ptr++;
	}

	return -1;
}

int64_t pass03(vector<node>& tree, vector<uint64_t> weights, vector<uint32_t> idxes /*sorted indexes of weights*/) {

	auto idx_es_ptr = idxes.begin() + 1;
	while (idx_es_ptr != idxes.end()) {
		 
		auto w2 = weights[*idx_es_ptr - 1];
		auto w1 = weights[0] - w2;

		if (w2 > w1) break;

		idx_es_ptr++;
	}	

	if (idx_es_ptr == idxes.end() - 1 || idx_es_ptr == idxes.end())
		return -1;

	uint32_t root1_idx = 1;
	uint32_t root2_idx, rootroot2_idx;
	uint32_t root3_idx, rootroot3_idx;
	uint64_t best_subtree_weight;

	do {
		root2_idx = *idx_es_ptr;
		rootroot2_idx = tree[root2_idx - 1].root_idx;
		root3_idx = 0;
		rootroot3_idx = 0;
		best_subtree_weight = weights[root1_idx - 1] - weights[root2_idx - 1];

		decrease_weights(tree, weights, root2_idx);
		erase_subtree(root2_idx, tree);

		root3_idx = find_weight(tree, weights, best_subtree_weight, root2_idx);

		if (root3_idx)
			//return best_subtree_weight - weights[root3_idx - 1];
			return 2 * best_subtree_weight - weights[root2_idx - 1];

		restore_tree(tree, rootroot2_idx, root2_idx);
		increase_weights(tree, weights, root2_idx);

		idx_es_ptr--;

	} while (idx_es_ptr != idxes.begin());

	return -1;
}

int64_t balancedForest(vector<int> c, vector<vector<int>> edges) {

	auto tree = prepare_tree(c, edges);
	auto weights = calc_weights(tree);
	vector<uint32_t> idx_es(c.size(), 0);
	std::iota(idx_es.begin(), idx_es.end(), 1);

	std::sort(idx_es.begin(), idx_es.end(), [&weights](auto& a, auto& b) {
		return weights[a - 1] < weights[b - 1];
		});

	auto res1 = pass01(tree, weights, idx_es);
	auto res2 = pass03(tree, weights, idx_es);

	if (res1 != -1 && res2 != -1)
		return std::min(res1, res2);
	else if (res1 != -1 || res2 != -1)
		return std::max(res1, res2);
	else
		return -1;
}

void run_tests(string filename, vector<int64_t> output){

    ifstream fs;
    fs.open(filename.c_str());

    if (!fs.is_open()){
        cout << "problem with openning file: " << filename.c_str() << endl;
        return;
    }

    int q, n, relations, temp, temp1;
    vector<int> c;
    vector<vector<int>> e;

    fs >> q;

    for(int i = 0; i < output.size(); i++){

        c.clear();
        e.clear();

        fs >> n;
        relations = n - 1;

        while(n) {
            fs >> temp;
            c.push_back(temp);
            n--;
        }

        while(relations){
            fs >> temp >> temp1;
            e.push_back({temp, temp1});
            relations--;
        }

		auto start = std::chrono::system_clock::now();
		auto t1 = std::chrono::system_clock::to_time_t(start);
		//cout << "start time: " << std::ctime(&t1) << endl;
        auto res = balancedForest(c, e);
		auto end = std::chrono::system_clock::now();
		auto t2 = std::chrono::system_clock::to_time_t(end);
		//cout << "end time: " << std::ctime(&t2) << endl;
		cout << "output: " << res << ", expected: " << output[i]
			<< "\t takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
    }

    fs.close();
	
}

void test_case_01(){

	vector<int> c;
	vector<vector<int>> e;
	int res;

    cout << "Test case 01" << endl;
    c = {7,7,4,1,1,1};
    e = {{1,2}, {3,1}, {2,4}, {2,5}, {2,6}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: -1" << endl;

    c = {1,1,1,18,10,11,5,6};
    e = {{1,2}, {1,4}, {2,3}, {1,8}, {8,7}, {7,6}, {5,7}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 10" << endl;

    c = {12, 7, 11, 17, 20, 10};
    e = {{1,2}, {2,3}, {4,5}, {6,5}, {1,4}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 13" << endl;

    c = {10, 4, 1, 5, 6, 4, 5, 5};
    e = {{1,2}, {2,3}, {1,4}, {5,4}, {5,6}, {7,8}, {7,5}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 5" << endl;

    c = {100, 100, 99, 99, 98, 98};
    e = {{1,3}, {3,5}, {1,2}, {2,4}, {4,6}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 297" << endl;

    cout << endl;
}

void test_case_02() {

	cout << "Test case 02" << endl;
	//run_tests("/home/mbm/Documents/qt/projects/test/test2.txt", {1112, 2041, 959, -1, -1});
	run_tests("..\\tests\\test2.txt", { 1112, 2041, 959, -1, -1 });
	cout << endl;
}

void test_case_05() {

	cout << "Test case 05" << endl;
	run_tests("..\\tests\\test5.txt", { 24999687487500, 16217607772, 4, 0, -1 });
	cout << endl;
}

void sample_test00(){

    cout << "Sample 00" << endl;
    
	vector<int> c;
	vector<vector<int>> e;
	int64_t res;

	c = {1,2,2,1,1};
    e = {{1,2}, {1,3}, {3,5}, {1,4}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 2" << endl;

    c = {1,3,5};
    e = {{1,3}, {1,2}};
    res = balancedForest(c, e);
    cout << "output: " << res << ", expected: -1" << endl;

    cout << endl;
}

void sample_test01(){

    cout << "Sample 01" << endl;
    vector<int> c = {15,12,8,14,13};
    vector<vector<int>> e = {{1,2}, {1,3}, {1,4}, {4,5}};
    auto res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 19" << endl;

    cout << endl;
}

void sample_test02(){

    cout << "Sample 02" << endl;
    vector<int> c = {12,10,8,12,14,12};
    vector<vector<int>> e = {{1,2}, {1,3}, {1,4}, {2,5}, {4,6}};
    auto res = balancedForest(c, e);
    cout << "output: " << res << ", expected: 4" << endl;

    cout << endl;
}

int main() {

	sample_test00();
	sample_test01();
	sample_test02();
	
	test_case_01();
	test_case_02();

	test_case_05();

    return 0;
}

