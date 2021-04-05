#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

enum class orientation { horizontal, vertical};

struct point {
	size_t i, j;
	bool end;

	point() :i{ 0 }, j{ 0 }, end{ false } {}
	
	point operator++(int) {

		if (j == 9) {
			j = 0;
			i++;
		}
		else
			j++;

		if (i == 10) {
			i = 0;
			end = true;
		}

		return *this;
	}
};

vector<string> parce_words(string& words) {
	
	vector<string> output;

	auto ptr = words.begin();
	while (true) {

		auto res = std::find(ptr, words.end(), ';');

		output.push_back(string{ ptr, res });

		if (res == words.end()) break;
		if (*res == ';') ptr = ++res;
	}

	

	return output;
}

template <class t>
string to_string(const vector<t> &words)  {

	stringstream ss;

	std::for_each(words.begin(), words.end(), [&ss](const t& s) {
		ss << s << ";";
		});

	string temp = ss.str();

	return temp.substr(0, temp.size() - 1);
}

inline bool is_plus(char ch) {
	if (ch == '+' || ch == 'x' || ch == 'X')
		return true;
	return false;
}

inline bool is_minus(char ch) {
	if (ch == '-')
		return true;
	return false;
}

bool is_horizontal(size_t i, size_t j, vector<string>& crossword) {
	
	if (is_plus(crossword[i][j]))
		return false;

	if (j != 0 && !is_plus(crossword[i][j - 1]))
		return false;

	if (is_plus(crossword[i][j + 1]))
		return false;

	j++;
	while(j != 10) {
		
		char& ch = crossword[i][j];

		if (ch >= 'A' && ch <= 'Z') {
			j++; 
			continue;
		}

		if (is_minus(ch))
			return true;
	}

	return false;
}

bool is_vertical(size_t i, size_t j, vector<string>& crossword) {

	if (is_plus(crossword[i][j])) 
		return false;

	if (i != 0 && !is_plus(crossword[i - 1][j])) 
		return false;

	if (is_plus(crossword[i + 1][j]))
		return false;

	i++;
	while (i != 10) {

		char& ch = crossword[i][j];

		if (ch >= 'A' && ch <= 'Z') {
			i++;
			continue;
		}

		if (is_minus(ch))
			return true;

	}

	return false;
}

bool run(vector<string> &crossword, string words)
{
	point crossword_pos;
	auto word_ptr = words.begin();

	while (!crossword_pos.end) {

		if (is_horizontal(crossword_pos.i, crossword_pos.j, crossword)) {

			auto j = crossword_pos.j;

			while (word_ptr != words.end() && *word_ptr != ';') {
				
				if (crossword[crossword_pos.i][j] == *word_ptr) { }

				else if (is_minus(crossword[crossword_pos.i][j])) //(crossword[crossword_pos.i][j] == '-') 
					crossword[crossword_pos.i][j] = *word_ptr;

				else return false;

				j++;
				word_ptr++;
			}

			if (word_ptr == words.end()) break;
			if (*word_ptr == ';') word_ptr++;
		}
		if (is_vertical(crossword_pos.i, crossword_pos.j, crossword)) {
			
			auto i = crossword_pos.i;

			while (word_ptr != words.end() && *word_ptr != ';') {

				if (crossword[i][crossword_pos.j] == *word_ptr) { }

				else if (is_minus(crossword[i][crossword_pos.j]))  //(crossword[i][crossword_pos.j] == '-') 
					crossword[i][crossword_pos.j] = *word_ptr;

				else return false;

				i++;
				word_ptr++;
			}

			if (word_ptr == words.end()) break;
			if (*word_ptr == ';') word_ptr++;
		}
		crossword_pos++;
	}

	return true;
}

// Complete the crosswordPuzzle function below.
vector<string> crosswordPuzzle(vector<string> crossword, string words) {

	vector<string> v_words = parce_words(words);
	sort(v_words.begin(), v_words.end());
	vector<string> crossword_cp;

	while (true) {

		crossword_cp.clear();
		string w = to_string(v_words);
		copy(crossword.begin(), crossword.end(), std::back_inserter(crossword_cp));
		bool flag = run(crossword_cp, w);

		if (flag) break;

		std::next_permutation(v_words.begin(), v_words.end());
	}

	return crossword_cp;
}

void test() {

	vector<string> crossword = {
		"++++++++++",
		"+------+++",
		"+++-++++++",
		"+++-++++++",
		"+++-----++",
		"+++-++-+++",
		"++++++-+++",
		"++++++-+++",
		"++++++-+++",
		"++++++++++"
	};

	string words = "POLAND;LHASA;SPAIN;INDIA";

	auto res = crosswordPuzzle(crossword, words);

	std::for_each(res.begin(), res.end(), [](string& s) {cout << s << endl; });
}

void test00() {

	vector<string> crossword = {
		"+-++++++++",
		"+-++++++++",
		"+-++++++++",
		"+-----++++",
		"+-+++-++++",
		"+-+++-++++",
		"+++++-++++",
		"++------++",
		"+++++-++++",
		"+++++-++++"
	};

	string words = "LONDON;DELHI;ICELAND;ANKARA";

	auto res = crosswordPuzzle(crossword, words);

	std::for_each(res.begin(), res.end(), [](string& s) {cout << s << endl; });
}

void test02() {

	vector<string> crossword = {
		"XXXXXX-XXX",
		"XX------XX",
		"XXXXXX-XXX",
		"XXXXXX-XXX",
		"XXX------X",
		"XXXXXX-X-X",
		"XXXXXX-X-X",
		"XXXXXXXX-X",
		"XXXXXXXX-X",
		"XXXXXXXX-X"
	};

	string words = "ICELAND;MEXICO;PANAMA;ALMATY";

	auto res = crosswordPuzzle(crossword, words);

	std::for_each(res.begin(), res.end(), [](string& s) {cout << s << endl; });
}


void testXX() {

	vector<string> crossword = {
		"+----+++++",
		"+-++++++++",
		"+-++++++++",
		"+-++++++++",
		"+-++++++++",
		"+-++++++++",
		"++++++++++",
		"++++++++++",
		"++++++++++",
		"++++++++++"
	};


	string words = "ABCD;ADCBEF";

	auto res = crosswordPuzzle(crossword, words);

	std::for_each(res.begin(), res.end(), [](string& s) {cout << s << endl; });
}

int main() {

	test();
	cout << endl;
	test00();
	cout << endl;
	test02();
	cout << endl;
	testXX();
}