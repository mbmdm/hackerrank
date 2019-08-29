#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

bool box_con_compare(vector<int> &a, vector<int> &b) {

	if (a.size() != b.size())
		return false;

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	for (size_t i = 0; i < a.size(); i++) {

		if (a[i] != b[i])
			return false;
	}

	return true;
}

string organizingContainers(vector<vector<int>> container) {

	vector<int> balls;
	balls.resize(container[0].size());
	fill(balls.begin(), balls.end(), 0);

	vector<int> box;
	box.resize(container.size());
	fill(box.begin(), box.end(), 0);

	for (size_t i = 0; i < container.size(); i++) {
		for (size_t j = 0; j < balls.size(); j++)
		{
			balls[j] += container[i][j];
			box[i]   += container[i][j];
		}
	}

	if (box_con_compare(balls, box))
		return "Possible";
	else return "Impossible";
}

int main()
{
	vector<vector<int>> v1 = { {1, 1}, {1, 1} };
	vector<vector<int>> v2 = { { 0, 2 }, { 1, 1 } };
	vector<vector<int>> v3 = { {1,3,1}, {2,1,2}, {3,3,3} };
	vector<vector<int>> v4 = { {0,2,1}, {1,1,1}, {2,0,0} };

	cout << organizingContainers(v1) << endl;
	cout << organizingContainers(v2) << endl;
	cout << organizingContainers(v3) << endl;
	cout << organizingContainers(v4) << endl;

	system("pause");

	return 0;
}