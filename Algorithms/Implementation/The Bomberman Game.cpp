#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

void print(vector<string> v);

struct bomb{
	size_t timer;
	size_t i, j;
	bool exist;
	bool ready_to_explode;

	bomb() :exist(false), ready_to_explode{false} {};

	void reset() { timer = 3; }

	void make_bomb(int i, int j) {
		this->make_bomb(i, j, 3);
	}

	void make_bomb(int i, int j, size_t time) {
		this->i = i;
		this->j = j;
		this->timer = time;
		exist = true;
		ready_to_explode = false;
	}

	void clear_bomb() {
		exist = false;
		ready_to_explode = false;
	}

	void up_timer() {
		timer--;
		if (timer == 0) ready_to_explode = true;
	}

	char to_char() {
		if (exist) return 'O';
		else return '.';
	}
};

typedef vector<vector<bomb>> board;

void set_bombs_and_explode(board &grid) {
	int rws = grid.size();
	int clmns = grid[0].size();

	vector<bomb*> to_explode;

	//bomberman place new bombs
	for (size_t i = 0; i < rws; i++)
	{
		for (size_t j = 0; j < clmns; j++)
		{
			bomb &b = grid[i][j];

			if (b.exist)
				b.up_timer();
			else
				b.make_bomb(i, j);

			if (b.ready_to_explode)
				to_explode.push_back(&b);
		}
	}

	//explode_some_bombs
	for (size_t i = 0; i < to_explode.size(); i++) {

		bomb &b = *to_explode[i];

		bool top = (int)b.i - 1 >= 0;
		bool bottom = (int)b.i + 1 < rws;
		bool left = (int)b.j - 1 >= 0;
		bool right = (int)b.j + 1 < clmns;

		if (top)
			grid[b.i - 1][b.j].clear_bomb();
		if (bottom)
			grid[b.i + 1][b.j].clear_bomb();
		if (left)
			grid[b.i][b.j-1].clear_bomb();
		if (right) 
			grid[b.i][b.j + 1].clear_bomb();

		/*if (top && left)
			grid[b.i - 1][b.j - 1].clear_bomb();
		if (top && right)
			grid[b.i - 1][b.j + 1].clear_bomb();
		if (bottom && left)
			grid[b.i + 1][b.j - 1].clear_bomb();
		if (bottom && right)
			grid[b.i + 1][b.j + 1].clear_bomb();*/

		b.clear_bomb();
	}
}

string to_string(vector<bomb> &v) {
	
	string temp;

	temp.resize(v.size());

	for (size_t j = 0; j < temp.size(); j++)
		temp[j] = v[j].to_char();
	
	return temp;
}

vector<string> to_vstring(vector<vector<bomb>> &v) {
	
	vector<string> result;

	for (size_t i = 0; i < v.size(); i++)
		result.push_back(to_string(v[i]));

	return result;
}

board to_board(vector<string> grid) {

	int rws = grid.size();
	int clmns = grid[0].size();
	
	board mgrid;
	mgrid.resize(rws);

	for_each(mgrid.begin(), mgrid.end(), [clmns](vector<bomb> &v) {v.resize(clmns); });

	for (size_t i = 0; i < rws; i++)
		for (size_t j = 0; j < clmns; j++)
			if (grid[i][j] != '.')
				mgrid[i][j].make_bomb(i, j, 2);

	return mgrid;
}

vector<string> gen_state2(vector<string> &grid) {

	string temp;
	temp.resize(grid[0].size());
	fill(temp.begin(), temp.end(), 'O');
	vector<string> res;
	res.resize(grid.size());
	generate(res.begin(), res.end(), [temp]() { return temp; });
	return res;
}

// Complete the bomberMan function below.
vector<string> bomberMan(int n, vector<string> grid) {

#ifdef Debug

	auto grid_state2 = to_vvbomb(grid); //state after 2 second
	set_bombs_and_explode(grid_state2);
	
	auto grid_state3 = to_vvbomb(grid); //state after 3 second
	set_bombs_and_explode(grid_state3);
	set_bombs_and_explode(grid_state3);
	
	auto grid_state4 = to_vvbomb(grid); //state after 4 second
	set_bombs_and_explode(grid_state4);
	set_bombs_and_explode(grid_state4);
	set_bombs_and_explode(grid_state4);
	
	auto grid_state5 = to_vvbomb(grid); //state after 5 second
	set_bombs_and_explode(grid_state5);
	set_bombs_and_explode(grid_state5);
	set_bombs_and_explode(grid_state5);
	set_bombs_and_explode(grid_state5);

	cout << "state 1:" << endl;
	print(grid);
	cout << endl;

	cout << "state 2:" << endl;
	print(to_vstring(grid_state2));
	cout << endl;

	cout << "state 3:" << endl;
	print(to_vstring(grid_state3));
	cout << endl;

	cout << "state 4:" << endl;
	print(to_vstring(grid_state4));
	cout << endl;

	cout << "state 5:" << endl;
	print(to_vstring(grid_state5));
	cout << endl;

#endif

	if (n == 1)
		return grid;
	else if (n % 4 == 3) {
		auto state = to_board(grid); //state after 3 second. The same board at 7, 11 and so on...
		set_bombs_and_explode(state);
		set_bombs_and_explode(state);
		return to_vstring(state);
	}
	else if (n % 4 == 1) {
		auto state = to_board(grid); //state after 5 second. The same board at 9, 13 and so on...
		set_bombs_and_explode(state);
		set_bombs_and_explode(state);
		set_bombs_and_explode(state);
		set_bombs_and_explode(state);
		return to_vstring(state);
	}
	else 
		return gen_state2(grid); // states after 2, 4, 6...
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void print(vector<string> v) {
	for_each(v.begin(), v.end(), [](string &s) { cout << s << endl; });
}

void test1() {

	vector<string> input =
	{
		"...",
		".O.",
		"..."
	};

	auto res = bomberMan(3, input);

	print(res);
	cout << endl;
}

void test2() {

	vector<string> input =
	{
		".......",
		"...O...",
		"....O..",
		".......",
		"OO.....,",
		"OO....."
	};

	auto res = bomberMan(3, input);

	print(res);
	cout << endl;
}

void test3() {

	vector<string> input =
	{
		".......",
		"...O.O.",
		"....O..",
		"..O....",
		"OO...OO",
		"OO.O..."
	};

	auto res = bomberMan(5, input);
	
	print(res);
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian"); 

	test1();
	test2();
	test3();

	system("pause");

	return 0;
}