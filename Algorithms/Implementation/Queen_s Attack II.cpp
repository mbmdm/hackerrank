#include <iostream>
#include <vector>

using namespace std;

#define BOARD(x, y)  buffer[(y-1) + BOARD_size*(x-1)]

char *buffer = nullptr;
int BOARD_size;

/*
1 - queen
2 - obstacle
3 - posible queen way
4 - imposible queen way
*/

enum class h_position {left, center, right, none};
enum class v_position {above, center, bottom, none};

void init(int n) {

	if (buffer != nullptr)
		delete[] buffer;

	buffer = new char[n*n];

	BOARD_size = n;

	auto ptr = buffer;

	int temp = n*n;

	while (temp) {
		*ptr = 0;
		ptr++;
		temp--;
	}
}

void print_board() {

	for (size_t i = 1; i <= BOARD_size; i++)
	{
		for (size_t j = 1; j <= BOARD_size; j++)
		{
			char *ptr = &BOARD(i, j);
			cout << (int)*ptr << " ";
		}
		cout << endl;
	}

	cout << endl;

}

void mark_possible_ways(int r_q, int c_q, int marker, h_position hp, v_position vp) {
	
	int row_p, colmn_p;

	//mark possible ways by horisontal left
	if ((hp == h_position::left && vp == v_position::center) || 
		(hp == h_position::none && vp == v_position::none)) {
		colmn_p = c_q - 1;
		while (colmn_p) {
			BOARD(r_q, colmn_p) = marker;
			colmn_p--;
		}
	}

	//mark possible ways by horisontal right
	if ((hp == h_position::right && vp == v_position::center) ||
		(hp == h_position::none && vp == v_position::none)) {
		colmn_p = c_q + 1;
		while (colmn_p <= BOARD_size) {
			BOARD(r_q, colmn_p) = marker;
			colmn_p++;
		}
	}

	//mark possible ways by vertical bottom
	if ((hp == h_position::center && vp == v_position::bottom) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q - 1;
		while (row_p) {
			BOARD(row_p, c_q) = marker;
			row_p--;
		}
	}

	//mark possible ways by vertical above
	if ((hp == h_position::center && vp == v_position::above) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q + 1;
		while (row_p <= BOARD_size) {
			BOARD(row_p, c_q) = marker;
			row_p++;
		}
	}

	//mark possible ways by diagonal (left/bottom)
	if ((hp == h_position::left && vp == v_position::bottom) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q - 1;
		colmn_p = c_q - 1;
		while (row_p && colmn_p) {
			BOARD(row_p, colmn_p) = marker;
			row_p--;
			colmn_p--;
		}
	}

	//mark possible ways by diagonal (right/above)
	if ((hp == h_position::right && vp == v_position::above) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q + 1;
		colmn_p = c_q + 1;
		while (row_p <= BOARD_size && colmn_p <= BOARD_size) {
			BOARD(row_p, colmn_p) = marker;
			row_p++;
			colmn_p++;
		}
	}

	//mark possible ways by diagonal (left/above)
	if ((hp == h_position::left && vp == v_position::above) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q + 1;
		colmn_p = c_q - 1;
		while (row_p <= BOARD_size && colmn_p) {
			BOARD(row_p, colmn_p) = marker;
			row_p++;
			colmn_p--;
		}
	}

	//mark possible ways by diagonal (right/bottom)
	if ((hp == h_position::right && vp == v_position::bottom) ||
		(hp == h_position::none && vp == v_position::none)) {
		row_p = r_q - 1;
		colmn_p = c_q + 1;
		while (row_p && colmn_p <= BOARD_size) {
			BOARD(row_p, colmn_p) = marker;
			row_p--;
			colmn_p++;
		}
	}
}

h_position get_hposition(int c_q, vector<int> &obstacle) {
	if (obstacle[1] == c_q)
		return h_position::center;
	else if(obstacle[1] > c_q)
		return h_position::right;
	else return h_position::left;
}

v_position get_vposition(int r_q, vector<int> &obstacle) {
	if (obstacle[0] == r_q)
		return v_position::center;
	else if (obstacle[0] > r_q)
		return v_position::above;
	else return v_position::bottom;
}

void past_obstacles(int r_q, int c_q, vector<vector<int>> &obstacles) {
	
	for (size_t i = 0; i < obstacles.size(); i++) {
		if (BOARD(obstacles[i][0], obstacles[i][1]) == 3) {
			BOARD(obstacles[i][0], obstacles[i][1]) = 2;

			h_position hp = get_hposition(c_q, obstacles[i]);
			v_position vp = get_vposition(r_q, obstacles[i]);

			mark_possible_ways(obstacles[i][0], obstacles[i][1], 2, hp, vp);
		}
		else BOARD(obstacles[i][0], obstacles[i][1]) = 2; //just for visualization
	}

}

int calc_queen_ways() {

	int result = 0;

	for (size_t i = 0; i < pow(BOARD_size, 2); i++)
		if (buffer[i] == 3)
			result++;

	return result;
}

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {

	init(n);

	BOARD(r_q, c_q) = 1; // queen position
	
	mark_possible_ways(r_q, c_q, 3, h_position::none, v_position::none); //possible queen ways
	
	past_obstacles(r_q, c_q, obstacles); //exclude possible queen ways by obstacles
	
	return calc_queen_ways();
}

void test1() {

	vector<vector<int>> obstacles = {};
	int n = 8;
	int k = 0;
	int r_q = 4;
	int c_q = 4;
	
	int res = queensAttack(n, 0, r_q, c_q, obstacles);

	if (res == 27)
		cout << "OK\t" << "test1" << endl;
	else 
		cout << "FAILED\t" << "test1 with value = " << res << endl;
}

void test2() {

	vector<vector<int>> obstacles = { {3,5} };
	int n = 8;
	int k = 0;
	int r_q = 4;
	int c_q = 4;

	int res = queensAttack(n, 0, r_q, c_q, obstacles);

	if (res == 24)
		cout << "OK\t" << "test2" << endl;
	else
		cout << "FAILED\t" << "test2 with value = " << res << endl;
}

void test3() {

	vector<vector<int>> obstacles = {  };
	int n = 4;
	int k = 0;
	int r_q = 4;
	int c_q = 4;

	int res = queensAttack(n, 0, r_q, c_q, obstacles);

	if (res == 9)
		cout << "OK\t" << "test2" << endl;
	else
		cout << "FAILED\t" << "test2 with value = " << res << endl;
}

void test4() {

	vector<vector<int>> obstacles = { {5,5}, {4,2}, {2,3} };
	int n = 5;
	int k = 3;
	int r_q = 4;
	int c_q = 3;

	int res = queensAttack(n, 0, r_q, c_q, obstacles);

	if (res == 10)
		cout << "OK\t" << "test2" << endl;
	else
		cout << "FAILED\t" << "test2 with value = " << res << endl;
}

int main()
{
	test1();
	test2();
	test3();
	test4();

	system("pause");

	return 0;
}