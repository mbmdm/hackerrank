#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>

#include <sstream>

using namespace std;

string encryption(string s) {

	double val_ = s.size();
	val_ = sqrt(val_);

	int rows = floor(val_);
	int columns = ceil(val_);

	if (rows*columns < s.size())
		rows++;

	/*for (size_t i = 0; i < s.size(); i++) {
		
		if (i%columns == 0) cout << endl;
		cout << s[i];
	}
	cout << endl;*/

	stringstream ss;

	for (size_t i = 0; i < columns; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			int index = i + j * columns;
			if (index < s.size()) ss << s[index];
		}

		ss << " ";
	}

	return ss.str();
}

int main() {
	
	//if man was meant to stay on the ground god would have given us roots
	string s1 = "ifmanwasmeanttostayonthegroundgodwouldhavegivenusroots";
	string res1 = encryption(s1);
	cout << res1 << endl;

	string s2 = "haveaniceday";
	string res2 = encryption(s2);
	cout << res2 << endl;

	string s3 = "feedthedog";
	string res3 = encryption(s3);
	cout << res3 << endl;
	
	string s4 = "chillout";
	string res4 = encryption(s4);
	cout << res4 << endl;

	system("pause");
	return 0;

}