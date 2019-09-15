#include <iostream>
#include <vector>

using namespace std;

int makeAnagram(string a, string b) {

	int alph_size = 'z' - 'a' + 1;

	int *buffer_a = new int[alph_size]; //count symbols into string a
	int *buffer_b = new int[alph_size]; //count symbols into string b

	for (int i = 0; i < alph_size; i++) {
		buffer_a[i] = 0;
		buffer_b[i] = 0;
	}

	for (size_t i = 0; i < a.size(); i++)
		buffer_a[a[i] - 'a']++;

	for (size_t i = 0; i < b.size(); i++)
		buffer_b[b[i] - 'a']++;
	
	int counter = 0;

	for (int i = 0; i < alph_size; i++) {
		
		int size_a = buffer_a[i];
		int size_b = buffer_b[i];

		if (!(size_a && size_b))
			continue;

		int temp = 0;

		while (size_a && size_b) {
			temp++;
			size_a--;
			size_b--;
		}

		counter += temp;
	}

	return a.size() + b.size() - 2 * counter;
}


void test() {
	
	cout << makeAnagram("cde", "abc") << endl; //4
	cout << makeAnagram("fcrxzwscanmligyxyvym", "jxwtrhvujlmrpdoqbisbwhmgpmeoke") << endl; //30

}


int main()
{
	test();

	system("pause");

	return 0;
}