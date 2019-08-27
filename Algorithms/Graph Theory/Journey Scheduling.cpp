#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct node
{
	size_t id;
	//size_t was_here;
	vector<node *> links;
	int max_path_1; //max path from this node to start/end of graph diamenter
	int max_path_2; //max path from this node to start/end of graph diamenter (another way)
	node *root;

	node(size_t index) :id{ index }, max_path_1{ -1 }, root{nullptr} {}

	friend ostream &operator<<(ostream &ost, const node &n) {
		ost << "id = " << n.id << ", path1 = " << n.max_path_1 << ", path2 = " << n.max_path_2;
		return ost;
	}

};

vector<node> tree; //represent graph
long long max_len; //graph diamenter length

node *max_path_iterative(node *v, vector<node> &tree) {
	//recursive way leads to a very deep recursion level

	node *output = v; //this node represets start/end of graph diameter
	v->max_path_1 = 0;

	vector<bool> used_nodes; //nodes which current algorithm has already processed
	used_nodes.resize(tree.size());
	fill(used_nodes.begin(), used_nodes.end(), false);
	used_nodes[v->id - 1] = true;

	vector<node *> buffer; //collection of non precessed nodes
	for (size_t i = 0; i < v->links.size(); i++) {
		node *temp = v->links[i];
		temp->root = v; //needs to get graph diameter
		temp->max_path_1 = 1;
		buffer.push_back(temp);
	}

	while (buffer.size() != 0) {

		node *ptr = *buffer.begin();

		for (size_t i = 0; i < ptr->links.size(); i++) {

			node *temp = ptr->links[i];

			if (used_nodes[temp->id-1])
				continue;
			
			temp->root = ptr;
			temp->max_path_1 = ptr->max_path_1 + 1;
			buffer.push_back(temp);
		}

		if (ptr->max_path_1 > output->max_path_1)
			output = ptr;

		//ptr->was_here = 0;
		used_nodes[ptr->id - 1] = true;
		buffer.erase(buffer.begin());
	}

	return output;
}

//create tree of graph
void init_start_tree(int n, vector<vector<int>> &roads) {
	
	//create nodes
	for (size_t i = 1; i <= n; i++)
		tree.push_back(node{ i });

	//create tree with roads
	for (size_t i = 0; i < roads.size(); i++) {
		node *n1 = &tree[roads[i][0] - 1];
		node *n2 = &tree[roads[i][1] - 1];

		n1->links.push_back(n2);
		n2->links.push_back(n1);
	}
}

//this part of realization represent tree dynamic programming.
//it fills node attributes that needed in sum calculation at journeyScheduling()
void init_fin_tree(int start_index) {

	//find start/end of graph diameter
	node *target1 = max_path_iterative(&tree[0], tree);

	//revise all nodes
	for_each(tree.begin(), tree.end(), [](node &n) {
		n.max_path_1 = -1; 
		n.root = nullptr; 
	});

	//find another diameter node
	node *target2 = max_path_iterative(&tree[target1->id-1], tree);

	max_len = target2->max_path_1; //diameter length

	//switch node:max_path before next step
	for_each(tree.begin(), tree.end(), [](node &n) {
		n.max_path_2 = n.max_path_1;
		n.max_path_1 = -1;
		n.root = nullptr;
	});

	//go reverse way to fill node::max_path_1 again
	node *target3 = max_path_iterative(&tree[target2->id - 1], tree);
}

vector<long long> journeyScheduling(int n, vector<vector<int>> roads, vector<vector<int>> journeys) {

	init_start_tree(n, roads);
	init_fin_tree(0);

	vector<long long> output{};

	for (size_t i = 0; i < journeys.size(); i++)
	{
		int v = journeys[i][0];
		int k = journeys[i][1];

		long long sum = max(tree[v - 1].max_path_1, tree[v - 1].max_path_2);
		sum += (k - 1)*max_len;
		output.push_back(sum);
	}

	return output;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test() {

	int n = 8;
	vector<vector<int>> roads = { { 2,1 },{ 3,2 },{ 4,2 },{ 5,1 },{ 6,1 },{ 7,1 },{ 8,7 } };
	vector<vector<int>> journeys = { { 4,6 },{ 3,4 },{ 6,3 },{ 7,6 },{ 4,6 },{ 7,1 },{ 2,6 } };
	//vector<vector<int>> journeys = { { 7,2 } };

	auto res = journeyScheduling(n, roads, journeys);

	for (size_t i = 0; i < res.size(); i++)
		cout << res[i] << endl;
}

void test2(string fname) {

	int x, y, n, m;
	vector<vector<int>> roads;
	vector<vector<int>> journeys;

	string file = ExePath();
	file = file + "\\" + fname;

	ifstream fs{};
	fs.open(file, ios::in);

	fs >> n;
	fs >> m;

	int line = 0;
	while (line < n - 1) {

		fs >> x;
		fs >> y;

		roads.push_back({ x,y });

		line++;
	}

	line = 0;
	while (line < m) {

		fs >> x;
		fs >> y;

		journeys.push_back({ x,y });

		line++;
	}

	vector<vector<int>> journeys2;
	journeys2.resize(m);

	copy(journeys.begin(), journeys.begin()+m, journeys2.begin());

	auto res = journeyScheduling(n, roads, journeys2);

	for (size_t i = 0; i < res.size(); i++)
		cout << res[i] << endl;
}

int main()
{
	//test();
	
	test2("data14.txt");

	system("pause");

	return 0;
}