#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#define mdebug

using namespace std;

struct prod {
	uint64_t m, w;

	prod() { m = w = 0; }

	prod(uint64_t m_, uint64_t w_) :m{ m_ }, w{ w_ } { 
		
		if (m > w)
			swap(m, w);
	}

	prod(uint64_t n) {
		
		m = sqrt(n);
		w = n / m;

		if (m*w < n)
			m++;
	}

	void operator++(int) {
		this->m++;
		if (m > w) swap(m, w);
	}

	bool operator<(prod &p) {
		if (this->m + this->w < p.m + p.w)
			return true;
		else return false;
	}

	uint64_t productivity() const {
		return m*w;
	}

	bool can_impove(uint64_t price, uint64_t candies) const{
		return candies / price;
	}

	//change candies if prod object is impoved
	void try_improve(uint64_t price, uint64_t &candies) {

		auto temp = candies / price;
		
		if (temp == 0) return;

		candies = candies - temp *price;

		auto delta = w - m;

		if (temp < delta)
			m += temp;
		else {
			temp -= delta;
			m += delta;

			auto a = temp / 2;
			m += a;
			w += temp - a;
		}
	}

	//improve prod on 1 element. 
	//if it can't be improved, improve prod anyway and return number of days to achive this aim 
	//change candies if prod object is impoved
	uint64_t force_improve(uint64_t price, uint64_t &candies) {
		
		if (candies / price ) {

			this->operator++(1);
			candies -= price;
			return 0;			
		}
		
		auto productivity = this->productivity();
		auto days = price / productivity;
		if (days * productivity < price)
			days++;

		candies += days * productivity;
		candies -= price;

		while (candies >= productivity) {
			days--;
			candies -= productivity;
		}

		this->operator++(999);

		return days;
	}
};

struct mframe
{
	prod plant;
	uint64_t candy = 0;
	uint64_t days = ULLONG_MAX;
};

// Complete the minimumPasses function below.
uint64_t minimumPasses(uint64_t m, uint64_t w, uint64_t p, uint64_t n) {

	prod current_plant{ m,w };
	prod max_plant{ n };
	uint64_t candies = 0;
	uint64_t day = 0;
	uint64_t min_days = ULLONG_MAX;
	mframe min_frame;

	while (current_plant < max_plant) {
	
		day++;

		auto productivity = current_plant.productivity();
		candies += productivity;
		auto target_candies = n - candies;

		auto days_left = target_candies / productivity;
		if (days_left * productivity < target_candies) days_left++;

		if (days_left + day < min_days) {
			
			min_days = days_left + day;

			if (min_days < 7000)
				cout << "";

			min_frame.candy = candies - productivity;
			min_frame.plant = current_plant;
			min_frame.days = day - 1;
		}

		if (current_plant.can_impove(p, candies))
			current_plant.try_improve(p, candies);
		else
			day += current_plant.force_improve(p, candies);
	}

	if (day == 0)
		return 1;

	//get back to chech better decision using prod::operator++() for plant
	//restore candies and current_plant that was obtained when assign min_days
	candies = min_frame.candy; //candies that we had after the frame.days
	current_plant = min_frame.plant; //plant corresponding frame.days 

	while (current_plant < max_plant) {

		auto productivity = current_plant.productivity();
		candies += productivity;
		auto target_candies = n - candies;

		auto days_left = target_candies / productivity;
		if (days_left * productivity < target_candies) days_left++;

		if (days_left + day < min_days) {
			min_days = days_left + day;
			cout << "";
		}

		candies = min_frame.candy;
		current_plant++;
	}

	return min_days;
}

void test() {

#ifdef mdebug

	uint64_t m, w, p, n, result, output;
	string test_case;

	//################################################################
	test_case = "12";
	m = 3; w = 13; p = 13; n = 1000000000000; result = 10;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
			cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "17";
	m = 4294967296; w = 4294967296; p = 1000000000; n = 10000000000; result = 1;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "1";
	m = 1; w = 1; p = 6; n = 45; result = 16;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "2";
	m = 5184889632; w = 5184889632; p = 20; n = 10000; result = 1;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "21";
	m = 5361; w = 3918; p = 8447708; n = 989936375520; result = 3577;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "44";
	m = 5; w = 2; p = 10302; n = 9133131738; result = 6583;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "10";
	m = 4294967296; w = 4294967296; p = 10; n = 10000; result = 1;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

	//################################################################
	test_case = "7";
	m = 1; w = 100; p = 10000000000; n = 1000000000000; result = 617737754;
	output = minimumPasses(m, w, p, n);
	if (output != result)
		cout << "test case " << test_case << " failed" << endl << "wrong value: " << output << endl << "right value: " << result << endl;
	else {
		cout << "test case " << test_case << " done" << endl;
	}
	cout << endl;

#endif

}

int main()
{
	test();

	system("pause");

	return 0;
}