#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
void print(T *ptr, int size, bool endline = true) {

	cout << "{ ";

	for (size_t i = 0; i < size; i++)
	{
		cout << ptr[i] << " ";
	}

	cout << "}\t" ;

	if (endline)
		cout << endl;

}

//{start_ ... end_} must be sorted. end pointer used as a border
int get_pivot(int *start, int *end) {
	
	int max_val = INT32_MIN;
	int max_val_count = INT32_MIN;

	int curr_val = INT32_MIN;
	int curr_val_count = INT32_MIN;

	auto ptr = start;

	while (ptr != end) {

		if (curr_val == INT32_MIN) {

			max_val = *ptr;
			max_val_count = 1;
			
			curr_val = *ptr;
			curr_val_count = 1;
			
			ptr++;
			continue;
		}

		if (*ptr == curr_val)
			curr_val_count++;

		if (max_val_count <= curr_val_count) {

			max_val_count = curr_val_count;
			max_val = curr_val;

			curr_val = *ptr;
			curr_val_count = 1;
		}

		ptr++;
	}

	return max_val;
}

string isValid(string s) {

	int alph_size = 'z' - 'a' + 1;

	int *buffer = new int[alph_size + 1]; //to count number of symbols into string a
	int *start	= buffer;
	int *end	= buffer + alph_size;
	*end = INT32_MAX;

	for (int i = 0; i < alph_size; i++) 
		buffer[i] = 0;

	for (size_t i = 0; i < s.size(); i++)
		buffer[s[i] - 'a']++;
	
	//print(buffer, alph_size, false);

	sort(start, end);

	while (start != end) {
		if (*start != 0)
			break;
		start++;
	}

	int sum = 0;
	int items_count = end - start;
	bool is_alone = (*start == 1) ? true : false; //has the string an alone charester

	for (int *ptr = start; ptr < end; ptr++) 
		sum += *ptr;

	int pivot = get_pivot(start, end);

	if (pivot *items_count == sum) {

		if (*start == *(end -1))
			return "YES";
		else return "NO";
	}
	else if (pivot * items_count == sum - 1)
		return "YES";
	else if (is_alone && (pivot * (items_count - 1) == sum - 1))
		return "YES";
	else
		return "NO";
}

void test() {

	cout << isValid("xxxaabbccrry") << " / NO" << endl;
	cout << isValid("aaaabbcc") << " / NO" << endl;
	cout << isValid("aabbc") << " / YES" << endl; 
	cout << isValid("a") << " / YES" << endl; 
	cout << isValid("abcdefghhgfedecba") << " / YES" << endl; 
	cout << isValid("aabbcd") << " / NO" << endl; 
	cout << isValid("aabbccddeefghi") << " / NO" << endl; 
	cout << isValid("abcdefghhgfedecba") << " / YES" << endl; 
}

int main()
{
	test();

	system("pause");

	return 0;
}