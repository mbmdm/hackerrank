/*
https://www.hackerrank.com/challenges/castle-on-the-grid/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct point {
	int x, y;
};

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {

	int n = grid.size();

	vector<vector<int>> desc(n, vector<int>(n, 0));

	for (size_t i = 0; i < n; i++) 
		for (size_t j = 0; j < n; j++) 
			if (grid[i][j] == 'x' || grid[i][j] == 'X')
				desc[i][j] = -1;

	queue<point> s;
	s.push(point{startX, startY});

	while (!s.empty()) {
	
		auto pos = s.front();
		s.pop();

		auto target = desc[pos.x][pos.y];

		// right pass throught x axis
		for (int x = pos.x + 1; x < n; x++) {

			auto& val = desc[x][pos.y];

			if (val == -1)
				break;

			if (target + 1 > val && val != 0)
				break;

			val = target + 1;
			s.push(point{ x, pos.y });
		}

		// left pass throught x axis
		for (int x = pos.x - 1; x >= 0; x--) {

			auto& val = desc[x][pos.y];

			if (val == -1)
				break;

			if (target + 1 > val && val != 0)
				break;

			val = target + 1;
			s.push(point{ x, pos.y });
		}

		// right pass throught y axis
		for (int y = pos.y + 1; y < n; y++) {

			auto& val = desc[pos.x][y];

			if (val == -1)
				break;

			if (target + 1 > val && val != 0)
				break;

			val = target + 1;
			s.push(point{ pos.x, y });
		}

		// left pass throught y axis
		for (int y = pos.y - 1; y >= 0; y--) {

			auto& val = desc[pos.x][y];

			if (val == -1)
				break;

			if (target + 1 > val && val != 0)
				break;

			val = target + 1;
			s.push(point{ pos.x, y });
		}
	}

	return desc[goalX][goalY];
}

void sample_tests(bool debug = true) {

	cout << "Sample tests" << endl;

	vector<string> grid;
	int startX, startY, goalX, goalY, output;

	grid = { ".X.", ".X.", "..." }; //Sample Input
	startX = 0, startY = 0, goalX = 0, goalY = 2, output = 3;
	auto res = minimumMoves(grid, startX, startY, goalX, goalY);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	grid = { ".X.", ".X.", "..." }; //Sample Input
	startX = 0, startY = 0, goalX = 0, goalY = 2, output = 3;
	auto res = minimumMoves(grid, startX, startY, goalX, goalY);
	if (debug || res != output)
		cout << "output: " << res << ", expected: " << output << endl;

	cout << endl;
}


int main() {


	sample_tests(true);

	cout << endl << "done." << endl;

	return 0;
}