/*
https://www.hackerrank.com/challenges/poisonous-plants/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <list>
#include <stack>
#include <memory>
//#include "testclass.h"

using namespace std;

//brutal
int poisonousPlants_brutal(vector<int> p) {

	bool pass_flag = false;
	uint32_t days = 0;

	do {
		
		//mprint(p.begin(), p.end());

		auto deleted = std::numeric_limits<int>::max();
		auto ptr = p.begin() + 1;
		pass_flag = false;
		
		while (ptr != p.end()) {
			
			if (deleted != std::numeric_limits<int>::max()) {
				
				if (*ptr > deleted) {
					deleted = *ptr;
					ptr = p.erase(ptr);
					pass_flag = true;
				}
				else {
					deleted = std::numeric_limits<int>::max();
					ptr++;
				}
			}
			else {

				if (*ptr > * (ptr - 1)) {
					deleted = *ptr;
					ptr = p.erase(ptr);
					pass_flag = true;
				}
				else
					ptr++;
			}
		}

		if (pass_flag) days++;

	} while (p.size() != 0 && pass_flag);

	return days;
}

template <class T>
struct miter {

	miter() :
		next{ nullptr },
		prev{ nullptr }
	{
		res = shared_ptr<T>(nullptr);
	}
	miter(const T& obj) :
		next{ nullptr }, 
		prev{nullptr} 
	{	
		res = make_shared<T>(obj);
	}
	miter(T&& obj) :
		next{ nullptr }, 
		prev{ nullptr } 
	{	
		res = make_shared<T>();
		*res = std::move(obj);
	}

	shared_ptr<T> res;
	miter *next;
	miter* prev;

	miter<T>& operator=(const miter<T>& right) {

		if (this == &right)
			return *this;

		next = right.next;
		prev = right.prev;
		res = right.res;
	}

	bool operator!=(const miter<T>& right) {

		shared_ptr<T> a = this->res;
		shared_ptr<T> b = right.res;

		if (a && b) {
			return !(a == b);
		}
		else if (a || b)
			return true;
		else
			return false;
	}

	bool operator==(const miter<T>& right) {

		return !this->operator!=(right);
	}

	miter<T>& operator++(int) {
		auto temp = *this;
		*this = *(this->next);
		return temp;
	}

	T& operator*() {
		return *res;
	}
};

template <class T>
struct mlist {

	miter<T>* begin_;
	miter<T>* end_;
	size_t size_;

	mlist()
	{
		begin_ = new miter<T>{};
		end_ = begin_;
		size_ = 0;
	}

	mlist(const mlist<T>& m) {

		this->operator=(m);
	}

	mlist& operator=(const mlist<T> &m) {

		this->begin_ = new miter<T>{};
		this->end_ = begin_;
		this->size_ = 0;

		miter<T>* ptr = m.begin_;
		while (ptr != m.end_) {

			const T& temp = *((*ptr).res);
			this->push(temp);
			ptr = ptr->next;
		}

		return *this;
	}

	~mlist() {
		this->clear();
		delete end_;
	}

	void push(const T& val) {
		
		miter<T> *temp = new miter<T>{ val };
		miter<T>* prev = end_->prev;
		temp->next = end_;
		temp->prev = prev;
		end_->prev = temp;

		if (size_ == 0) 
			begin_ = temp;

		else {
			prev->next = temp;
		}

		size_++;
	}

	miter<T> previous(const miter<T>& itr) {
		
		if (itr.prev != nullptr)
			return *(itr.prev);
		else return *end_;
	}

	T& top() {
	
		miter<T>* prev = end_->prev;
		return *(prev->res);
	}

	T& bottom() {

		return *(begin_->res);
	}

	void pop_bottom() {
		
		miter<T>* temp = begin_;
		begin_ = begin_->next;
		begin_->prev = nullptr;
		delete temp;
		size_--;
	}

	miter<T> begin() {
		return *begin_;
	}

	miter<T> end() {
		return *end_;
	}

	size_t size() {
		return size_;
	}

	void clear() {
		
		auto ptr = begin_;
		while (ptr != end_) {
			
			auto temp = ptr->next;
			delete ptr;
			ptr = temp;
		}

		size_ = 0;
		begin_ = end_;
	}

	void merge(mlist<T>& l) {
	
		if (l.size_ == 0)
			return;

		miter<T>* prev = end_->prev;
		prev->next = l.begin_;
		l.begin_ = prev;

		prev = l.end_->prev;
		prev->next = end_;
		end_->prev = prev;

		this->size_ += l.size_;

		l.begin_ = l.end_;
		l.size_ = 0;
	}


	bool empty() {
		if (size_ == 0)
			return true;
		else
			return false;
	}

	miter<T> erase(miter<T> itr) {
		
		if (itr == *end_)
			return *end_;

		miter<T>* prev = itr.prev;
		miter<T>* next = itr.next;
		miter<T>* curr = next->prev;

		next->prev = prev;

		if (prev != nullptr)
			prev->next = next;

		delete curr;

		size_--;

		return *next;
	}
};

mlist<mlist<int>> make_listlist(vector<int>& p) {

	mlist<mlist<int>> l;
	mlist<int> temp;

	temp.push(p[0]);

	for (size_t i = 1; i < p.size(); i++) {

		if (p[i] > p[i - 1]) {
			l.push(temp);
			temp = mlist<int>{};
			temp.push(p[i]);
		}
		else {
			temp.push(p[i]);
		}
	}

	if (!temp.empty())
		l.push(temp);

	return l;
}

void pass(mlist<mlist<int>>& l) {

	if (l.size() == 1) return;

	auto ptr = l.begin();
	ptr++;

	while (ptr != l.end()) {
		
		mlist<int>& list = (*ptr);
		
		list.pop_bottom();

		if (list.empty())
			ptr = l.erase(ptr);
		else
			ptr++;
	}
}

void try_chain(mlist<mlist<int>>& l) {

	if (l.size() == 1)
		return;

	auto curr = l.begin();
	auto next = l.begin(); next++;


	while (next != l.end()) {
	
		if (!(*next).empty()) {

			auto a = (*curr).top();
			auto b = (*next).bottom();

			if (a >= b) {

				(*curr).merge(*next);
				next = l.erase(next);
				curr = l.previous(next);
			}
			else {
				curr++;
				next++;
			}
		}
		else
			next = l.erase(next);

	}
}

int poisonousPlants(vector<int> p) {

	//crutial idea from discussion branch
	auto l = make_listlist(p);

	auto counter = 0;

	while (l.size() != 1) {

		pass(l);
		try_chain(l);
		counter++;
	}

	return counter;
}

template <class func>
void run_test(string case_name, func f, vector<int> input, int output, bool debug = true, string endstr= "\n") {
	
	auto start = std::chrono::system_clock::now();
	auto res = f(input);
	auto end = std::chrono::system_clock::now();

	cout << case_name << ":\t";

	if (debug) {
		if (res == output) cout << "OK" << endl;
		else cout << "FAILED" << endl;

		cout << "output: " << res << ", expected: " << output;
		cout << ", time(milli sec): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		cout << ", time(micro sec): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		cout << endl;
	}
	else if (res != output)
		cout << "FAILED\n" << "output: " << res << ", expected: " << output << endl;

	else
		cout << "OK" << endl;
	
	cout << endstr;
}

template <class T1, class T2>
struct result_data {
	T1 input;
	T2 output;
};

template <class T1, class T2>
result_data<T1,T2> read_file(string filename_in, string filename_out) {

	ifstream fs_in, fs_out;
	fs_in.open(filename_in.c_str());
	fs_out.open(filename_out.c_str());

	if (!fs_in.is_open()) {
		cout << "problem with openning file: " << filename_in.c_str() << endl;
		return {};
	}

	if (!fs_out.is_open()) {
		cout << "problem with openning file: " << filename_out.c_str() << endl;
		return {};
	}

	int64_t n, temp;
	T1 input;
	T2 output;

	fs_in >> n;

	while (fs_in >> temp)
		input.push_back(temp);

	fs_out >> output;

	fs_in.close();
	fs_out.close();

	return { input, output };
}

void run_tests(bool debug = true) {

	string endstr = (debug) ? "\n" : "";

	cout << "Sample tests" << endl << endl;

	run_test("Test case 8",			poisonousPlants, { 20, 5, 6, 15, 2, 2, 17, 2, 11, 5, 14, 5, 10, 9, 19, 12, 5 }, 4, debug, endstr);
	run_test("from discussion",		poisonousPlants, { 6, 5, 8, 7, 4, 7, 3, 1, 1, 10 }, 2, debug, endstr);
	run_test("my 3",				poisonousPlants, { 1, 10, 4, 9, 3, 8 }, 3,  debug, endstr);
	run_test("my 2",				poisonousPlants, { 3, 10, 9, 8, 7, 2 }, 4,  debug, endstr);
	run_test("my 1",				poisonousPlants, { 1, 10, 9, 8, 7 }, 4, debug, endstr);
	run_test("Example",				poisonousPlants, { 3, 6, 2, 7, 5 }, 2,  debug, endstr);
	run_test("Sample Test case 0",	poisonousPlants, { 6, 5, 8, 4, 7, 10, 9 }, 2,  debug, endstr);
	run_test("Sample Test case 1",	poisonousPlants, { 3, 2, 5, 4 }, 2,  debug, endstr);
	run_test("Sample Test case 2",	poisonousPlants, { 4, 3, 7, 5, 6, 4, 2 }, 3,  debug, endstr);

	//Test from files
	auto test19 = read_file<vector<int>, int>("..\\tests\\test19_in.txt", "..\\tests\\test19_out.txt");
	run_test("Test case 19", poisonousPlants, test19.input, test19.output, debug, endstr);
}

int main() {

	run_tests(true);

	cout << "done." << endl;

	int temp;
	cin >> temp;

	return 0;
}