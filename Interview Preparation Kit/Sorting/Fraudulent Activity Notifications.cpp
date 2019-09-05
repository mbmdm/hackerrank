#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Complete the activityNotifications function below.
int activityNotifications_plain(vector<int> expenditure, int d) {

	vector<int> buffer;
	buffer.resize(d);

	int counter = 0;
	double mediane = 0;
	vector<int>::iterator start;
	vector<int>::iterator end;

	for (int i = d; i < expenditure.size(); i++) {
		
		start = expenditure.begin() + i - d;
		end = start + d;
		copy(start, end, buffer.begin());
		
		if (d % 2 != 0) {
			nth_element(buffer.begin(), buffer.begin() + d/2, buffer.end());
			mediane = *(buffer.begin() + d / 2);
		}
		else {
			nth_element(buffer.begin(), buffer.begin() + (int)floor(d / 2), buffer.end());
			nth_element(buffer.begin(), buffer.begin() + (int)ceil(d / 2), buffer.end());
			mediane = *(buffer.begin() + (int)floor(d / 2));
			mediane += *(buffer.begin() + (int)ceil(d / 2));
			mediane /= 2;
		}

		if (expenditure[i] >= mediane * 2)
			counter++;
	
	}
	
	return counter;
}

double get_mediane(vector<int> &v) {
	
	int n = v.size();

	if (n % 2 != 0)
		return *(v.begin() + floor(n / 2));
	else
	{
		int i = n / 2;
		double mediane = v[i];
		mediane += v[i - 1];
		mediane /= 2;
		
		return mediane;
	}
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {

	vector<int> buffer;
	buffer.resize(d);

	copy(expenditure.begin(), expenditure.begin() + d, buffer.begin());
	sort(buffer.begin(), buffer.end());

	int counter = 0; //number of notifivation
	int start = 0; //start index of prior transaction data
	int end = d - 1; //last index of prior transaction data

	for (int i = d; i < expenditure.size(); i++) {

		start = i - d;

		auto mediane = get_mediane(buffer);

		if (expenditure[i] >= mediane * 2)
			counter++;

		//prepare buffer to the next step
		int remove_val = expenditure[start];
		int new_val = expenditure[i];

		auto remove_itr = std::lower_bound(buffer.begin(), buffer.end(), remove_val);

		buffer.erase(remove_itr);

		auto past_itr = std::lower_bound(buffer.begin(), buffer.end(), new_val);

		buffer.insert(past_itr, new_val);
	}

	return counter;
}

void test() {

	vector<int> v1 = {10,20,30,40,50}; //1
	cout << activityNotifications(v1, 3) << endl << endl;

	vector<int> v2 = { 2, 3, 4, 2, 3, 6, 8, 4, 5 }; //2
	cout << activityNotifications(v2, 5) << endl << endl;

	vector<int> v3 = { 1,2,3,4,4 }; //0
	cout << activityNotifications(v3, 4) << endl << endl;
}

int main() {

	test();

	system("pause");

	return 0;
}