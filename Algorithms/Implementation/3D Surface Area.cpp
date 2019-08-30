#define NOMINMAX

#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <string>


using namespace std;

int surfaceHiddenArea(vector<vector<int>> a, int max_height) {
	
	int res = 0;

	bool in_body = false;
	bool out_body = false;

	//find out hidden areas by shooting rays at the left surface
	for (size_t h = 1; h <= max_height; h++) 
		for (size_t j = 0; j < a[0].size(); j++) {
			for (size_t i = 0; i < a.size(); i++)
			{
				if (a[i][j] >= h && out_body && in_body) {
					//in_body = true;
					out_body = false;
					res++;
				}
				else if (a[i][j] < h && !out_body && in_body)
					out_body = true;
				else  if (a[i][j] >= h)
					in_body = true;
			}
			in_body = out_body = false;
		}

	//find out hidden areas by shooting rays at the front surface
	for (size_t h = 1; h <= max_height; h++)
		for (size_t i = 0; i < a.size(); i++) {
			for (size_t j = 0; j < a[0].size(); j++)
			{
				if (a[i][j] >= h && out_body && in_body) {
					//in_body = true;
					out_body = false;
					res++;
				}
				else if (a[i][j] < h && !out_body && in_body)
					out_body = true;
				else  if (a[i][j] >= h)
					in_body = true;
			}
			in_body = out_body = false;
		}

	return res*2;
}

// Complete the surfaceArea function below.
int surfaceArea(vector<vector<int>> a) {

	vector<int> left_t;;	// to calculate surfaces[0]
	vector<int> front_t;	// to calculate surfaces[1]
	int top_t =	0;			// to calculate surfaces[2]
	int max_height = 0;		// it needs to call surfaceHiddenArea();

	//initialization left_t and front_t by 0 (zero)
	left_t.resize(a[0].size());
	front_t.resize(a.size());
	fill(left_t.begin(), left_t.end(), 0);
	fill(front_t.begin(), front_t.end(), 0);

	//calculate left_t, front_t and top_t values 
	for (size_t i = 0; i < a.size(); i++)
		for (size_t j = 0; j < a[0].size(); j++)
		{
			left_t[j] = std::max(left_t[j], a[i][j]);
			front_t[i] = std::max(front_t[i], a[i][j]);
			if (a[i][j] != 0) top_t++;
			max_height = max(max_height, a[i][j]);
		}

	int result = 0, temp = 0;
	for_each(left_t.begin(), left_t.end(), [&temp](int &i) {temp += i; });
	result += temp * 2; //got 2 sides;

	temp = 0;
	for_each(front_t.begin(), front_t.end(), [&temp](int &i) {temp += i; });
	result += temp * 2; //got 2 sides;

	result += top_t * 2; //got 2 sides;

	result += surfaceHiddenArea(a, max_height);

	return result;
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void test1() {

	vector<vector<int>> input = { {1} }; /*{ vector<int>{} };
	input[0].push_back(1);*/

	int res = surfaceArea(input);

	if (res == 6)
		cout << "OK\t" << "test1" << endl;
	else 
		cout << "FAILED\t" << "test1 with value = " << res << endl;
}

void test2() {

	vector<vector<int>> input = { {1,3,4}, {2,2,3}, {1,2,4} };

	int res = surfaceArea(input);

	if (res == 60)
		cout << "OK\t" << "test1" << endl;
	else
		cout << "FAILED\t" << "test1 with value = " << res << endl;
}

void test(string name, int result) {

	string path = ExePath();

	ifstream fs{};
	fs.open(path + "\\" + name, ios::in);

	int h, w;

	fs >> h;
	fs >> w;

	int buffer;
	int buc_w = w;
	vector<vector<int>> a;
	vector<int> current = vector<int>{};
	while (!fs.eof()) {
		fs >> buffer;
		current.push_back(buffer);
		buc_w--;
		if (buc_w == 0) {
			a.push_back(current);
			current = vector<int>{};
			buc_w = w;
		}
	}

	int res = surfaceArea(a);

	if (res == result)
		cout << "OK\t" << name << endl;
	else
		cout << "FAILED\t" << name << " with value = " << res << endl;

	fs.close();
}

int main()
{
	test1();
	test2();
	test("data1.txt", 1482);
	test("data2.txt", 1276);
	test("data4.txt", 13388);

	system("pause");

	return 0;
}