#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>

using std::cout;

using namespace std;

struct node_info {
public:
	int size;
	int root;

	node_info() : size{ 1 }, root{ -1 } {};
	node_info(int i) : size{ 1 }, root{ i } {}
	node_info(const node_info &n) :size{ n.size }, root{ n.root } {}
};

class mdisjoint_union {

public:

	unordered_map<int, node_info> m;

	//return new group size
	int union_(int a, int b) {
		
		auto fres_a = m.find(a);
		auto fres_b = m.find(b);

		if (fres_a == m.end() && fres_b == m.end()) {
			node_info anode{ a };
			node_info bnode{ b };
			bnode.size = 2;
			anode.root = b;

			m.insert(make_pair(a, anode));
			m.insert(make_pair(b, bnode));

			return 2;
		}
		else if (fres_a == m.end() ) {
			node_info anode{ a };
			int root_b = root(fres_b->first);
			node_info &root = m[root_b];
			anode.root = root_b;
			root.size++;
			m.insert(make_pair(a, anode));
		
			return root.size;			
		}
		else if (fres_b == m.end()) {
			node_info bnode{ b };
			int root_a = root(fres_a->first);
			node_info &root = m[root_a];
			bnode.root = root_a;
			root.size++;
			m.insert(make_pair(b, bnode));

			return root.size;
		}
		else {
			int root_a = root(a);
			int root_b = root(b);

			if (root_a == root_b)
				return m[root_a].size;
			
			if (m[root_a].size > m[root_b].size) {
				m[root_a].size += m[root_b].size;
				m[root_b].root = root_a;
				return m[root_a].size;
			}
			else {
				m[root_b].size += m[root_a].size;
				m[root_a].root = root_b;
				return m[root_b].size;
			}
		}
		return 0;
	}

	int root(int i) {

		auto ptr = m.find(i);
		
		if (ptr == m.end()) return i;

		while (i != m[i].root) {
			
			auto next = m.find(ptr->second.root);
			next = m.find(next->second.root);
			ptr->second.root = next->second.root; //Union path compression
			i = next->second.root;
		}

		return i;
	}
};

/*
explanation here: https://www.hackerearth.com/ru/practice/notes/disjoint-set-union-union-find/
*/

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {

	mdisjoint_union data_ {};
	vector<int> result;

	result.push_back(2);
	data_.union_(queries[0][0], queries[0][1]);

	for (size_t i = 1; i < queries.size(); i++)
	{
		auto a = queries[i][0];
		auto b = queries[i][1];
		auto size = data_.union_(a, b);
		size = max(size, *(result.end() - 1));
		result.push_back(size);		
	}

	return  result;
}

int main()
{
	//vector<vector<int>> v = { {1,2}, {3,4}, {1,3}, {5,7}, {5,6}, {7,4} };
	vector<vector<int>> v = { { 6,4 },{ 5,9 },{ 8,5 },{ 4,1 },{ 1,5 },{ 7,2 }, {4,2}, {7,6} };

	auto res = maxCircle(v);
	cout << endl;
	cout << "tarsk result:" << endl;
	for_each(res.begin(), res.end(), [](int &a) {cout << a << endl; });

	system("pause");

	return 0;
}