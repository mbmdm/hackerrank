#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//#define mdebug

uint64_t stepsumGame(uint64_t a) {

	int idx = -1;
	uint64_t temp = a;

	for (int i = 0; i < sizeof(uint64_t)*8; i++) {
		if (temp & 1)
			idx = i;
		temp = temp >> 1;
	}

	temp = pow(2, idx);

	if (temp == a)
		return temp >> 1;
	else return temp;
}

// Complete the counterGame function below.
string counterGame(uint64_t n) {

	int counter = 0;
	uint64_t temp;

	while (n != 1) {
		temp = stepsumGame(n);

#ifdef mdebug
		cout << "step " << counter << "\t";
		cout << "heap = " << n << ": ";
		if (counter % 2 == 0)
			cout << "Louise takes ";
		else
			cout << "Richard takes ";
		cout << temp << endl;
#endif // mdebug

		n -= temp;
		counter++;
	}

	if (counter % 2 == 0)
		return "Richard";
	else
		return "Louise";
}



int main()
{ 
	//test case 1
	cout << counterGame(1560834904) << endl;
	cout << counterGame(1768820483) << endl;
	cout << counterGame(1533726144) << endl;
	cout << counterGame(1620434450) << endl;
	cout << counterGame(1463674015) << endl;

	return 0;
}