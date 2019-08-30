#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

enum class h_position {left, center, right, none};
enum class v_position {above, center, bottom, none};

h_position get_hposition(int r_q, int c_q, vector<int> &obstacle) {
	
	if (obstacle[1] == c_q)
		return h_position::center;

	else if ((r_q - obstacle[0] == c_q - obstacle[1]) ||
		(r_q + c_q == obstacle[0] + obstacle[1])) {
		if (obstacle[1] > c_q)
			return h_position::right;
		else
			return h_position::left;
	}
	else if (r_q == obstacle[0] && c_q > obstacle[1])
		return h_position::left;
	else if (r_q == obstacle[0] && c_q < obstacle[1])
		return h_position::right;
	else 
		return h_position::none;
}

v_position get_vposition(int r_q, int c_q, vector<int> &obstacle) {
	
	if (obstacle[0] == r_q)
		return v_position::center;

	else if ((r_q - obstacle[0] == c_q - obstacle[1]) ||
		(r_q + c_q == obstacle[0] + obstacle[1])) {

		if (obstacle[0] > r_q)
			return v_position::above;
		else
			return v_position::bottom;
	}
	else if (c_q == obstacle[1] && r_q < obstacle[0])
		return v_position::above;
	else if (c_q == obstacle[1] && r_q > obstacle[0])
		return v_position::bottom;
	else 
		return v_position::none;
}

struct pt {
	int row;
	int column;
};

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {

	pt top = { n, c_q };
	pt bottom = { 1, c_q };
	pt left = { r_q, 1 };
	pt right = { r_q, n };
	pt left_top;
	{
		int dx = min(n - r_q, c_q - 1);
		left_top.row = r_q + dx;
		left_top.column = c_q - dx;
	}
	pt right_top;
	{
		int dx = n - max(r_q, c_q);
		right_top.row = r_q + dx;
		right_top.column = c_q + dx;
	}
	pt left_bottom;
	{
		int dx = min(r_q, c_q) - 1;
		left_bottom.row = r_q - dx;
		left_bottom.column = c_q - dx;
	}
	pt right_bottom;
	{
		int dx = min(n - c_q, r_q - 1);
		right_bottom.row = r_q - dx;
		right_bottom.column = c_q + dx;
	}

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		pt obst{ obstacles[i][0] , obstacles[i][1] };
		h_position hp = get_hposition(r_q, c_q, obstacles[i]);
		v_position vp = get_vposition(r_q, c_q, obstacles[i]);

		if (hp == h_position::center && vp == v_position::above)
			top.row = min(obst.row - 1, top.row);
		else if (hp == h_position::center && vp == v_position::bottom)
			bottom.row = max(obst.row + 1, bottom.row);
		else if (hp == h_position::left && vp == v_position::center)
			left.column = max(obst.column + 1, left.column);
		else if (hp == h_position::right && vp == v_position::center)
			right.column = min(obst.column - 1, right.column);
		else if (hp == h_position::left && vp == v_position::above) {
			if (left_top.row > obst.row - 1) {
				left_top.row = obst.row - 1;
				left_top.column = obst.column + 1;
			}
		}
		else if (hp == h_position::right && vp == v_position::above) {
			if (right_top.row > obst.row - 1) {
				right_top.row = obst.row - 1;
				right_top.column = obst.column - 1;
			}
		}
		else if (hp == h_position::left && vp == v_position::bottom) {
			if (left_bottom.row < obst.row + 1) {
				left_bottom.row = obst.row + 1;
				left_bottom.column = obst.column + 1;
			}
		}
		else if (hp == h_position::right && vp == v_position::bottom) {
			if (right_bottom.row < obst.row + 1) {
				right_bottom.row = obst.row + 1;
				right_bottom.column = obst.column - 1;
			}
		}
	}

	int sum = 0;

	sum += right.column - left.column; //calc by horizontal
	sum += top.row - bottom.row; //calc by vertical
	sum += right_top.column - left_bottom.column; //calc by 1st diagonal
	sum += right_bottom.column - left_top.column; //calc by 2nd diagonal

	return sum;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
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
		cout << "OK\t" << "test3" << endl;
	else
		cout << "FAILED\t" << "test3 with value = " << res << endl;
}

void test4() {

	vector<vector<int>> obstacles = { {5,5}, {4,2}, {2,3} };
	int n = 5;
	int k = 3;
	int r_q = 4;
	int c_q = 3;

	int res = queensAttack(n, 0, r_q, c_q, obstacles);

	if (res == 10)
		cout << "OK\t" << "test4" << endl;
	else
		cout << "FAILED\t" << "test4 with value = " << res << endl;
}

void test5(string name, int result) {

	string path = ExePath();

	ifstream fs{};
	fs.open(path + "\\" + name, ios::in);

	int n, k, r_q, c_q;

	fs >> n;
	fs >> k;
	fs >> r_q;
	fs >> c_q; 

	int x, y;

	vector<vector<int>> obstacles;
	while (!fs.eof()) {
		fs >> x;
		fs >> y;
		obstacles.push_back({x,y});
	}

	int res = queensAttack(n, k, r_q, c_q, obstacles);

	if (res == result)
		cout << "OK\t" << "test5" << endl;
	else
		cout << "FAILED\t" << "test5 with value = " << res << endl;

	fs.close();
}

int main()
{
	test1();
	test2();
	test3();
	test4();

	test5("data13.txt", 307303);
	test5("data6.txt", 40);

	system("pause");

	return 0;
}