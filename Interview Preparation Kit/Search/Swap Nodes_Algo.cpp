#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define mdebug

struct node {

	node *left;
	node *right;
	node *root;
	int val;

	node(int v, node *parent) :
		left{ nullptr },
		right{ nullptr },
		root(parent),
		val{ v }
	{
	}
};

void make_tree(vector<vector<int>> &indexes, node *tree) {

	deque<node *> que;
	que.push_back(tree);

	auto ptr = indexes.begin();

	while (ptr != indexes.end()) {

		auto root = que.front();
		que.pop_front();

		node *temp = nullptr;

		if ((*ptr)[0] != -1) {
			temp = new node{ (*ptr)[0], root };
			root->left = temp;
			que.push_back(temp);
		}
		if ((*ptr)[1] != -1) {
			temp = new node{ (*ptr)[1], root };
			root->right = temp;
			que.push_back(temp);
		}

		ptr++;
	}
}

vector<int> to_array(node *n) {

	if (n == nullptr) return vector<int>{};

	vector<int> v = to_array(n->left);
	v.push_back(n->val);
	auto temp = to_array(n->right);
	v.resize(v.size() + temp.size());
	copy(temp.begin(), temp.end(), v.begin() + v.size() - temp.size());
	
	return v;
}

#ifdef mdebug
void print(node *n) {

	if (n == nullptr) return;

	print(n->left);
	cout << n->val << " ";
	print(n->right);
}
#endif

void mswap(node *root, int query, int current_level = 1) {
	
	if (root == nullptr)
		return;

	if (current_level % query == 0) {
		node *a = root->left;
		node *b = root->right;
		root->left = b;
		root->right = a;
	}
	
	current_level++;

	mswap(root->left, query, current_level);
	mswap(root->right, query, current_level);
}

/*
* Complete the swapNodes function below.
*/
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {

	vector<vector<int>> result;

	node *tree = new node{ 1, nullptr };

	make_tree(indexes, tree);

#ifdef mdebug
	print(tree);
	cout << endl;
#endif

	for (size_t i = 0; i < queries.size(); i++) {
		mswap(tree, queries[i]);
		result.push_back(to_array(tree));

#ifdef mdebug
		print(tree);
		cout << endl;
#endif
	}

	return result;
}

void test() {
	
#ifdef mdebug

	vector<vector<int>> indexes;
	vector<int> queries;

	indexes = { {2,3}, {4,-1}, {5,-1}, {6,-1}, {7,8}, {-1,9}, {-1,-1}, {10,11}, { -1,-1 },{ -1,-1 },{ -1,-1 } };
	queries = { 2,4 };
	
	swapNodes(indexes, queries);

#else
	cout << "define mbebug" << endl;
#endif
		
}

int main() {

	test();

	system("pause");

	return 0;
}