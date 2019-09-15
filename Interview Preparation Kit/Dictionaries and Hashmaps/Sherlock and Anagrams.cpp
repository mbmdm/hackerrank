#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

using namespace std;

void print(unordered_map<string, int> &map) {
	
	cout << "{ ";
	auto ptr = map.begin();

	while (ptr != map.end()) {
		cout << ptr->first << " - " << ptr->second << endl;
		ptr++;
	}

	cout << "}" << endl;

}

int sherlockAndAnagrams(string s) {

	unordered_map<string, int> map;

	for (size_t l = 1; l < s.size(); l++)
		for (int i = 0; i + l - 1 < s.size(); i++) {
			string str = s.substr(i, l);
			sort(str.begin(), str.end());
			map[str]++;
		}

	int counter = 0;
	auto ptr = map.begin();

	while (ptr != map.end()) {
		if (ptr->second == 2)
			counter++;
		else if (ptr->second > 2) { 
			string str = ptr->first;
			int n = ptr->second;
			int result = (n - 1) * n / 2; //Комбинаторика (сочетания из n по 2-а)
			counter += result;
		}
		ptr++;
	}

	//print(map);
	return counter;
}

void test() {
	
	cout << "result: \t" << sherlockAndAnagrams("abba") << " / 4" <<endl;
	cout << "result: \t" << sherlockAndAnagrams("abcd") << " / 0" << endl;
	cout << "result: \t" << sherlockAndAnagrams("ifailuhkqq") << " / 3" << endl;
	cout << "result: \t" << sherlockAndAnagrams("kkkk") << " / 10" << endl;

	cout << "result: \t" << sherlockAndAnagrams("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") << " / 166650" << endl;
}

int main()
{
	test();

	system("pause");

	return 0;
}