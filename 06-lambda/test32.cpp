#include<iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;

class Widget
{
public:
	bool isValidated() const {
		cout << "isValidated" << endl;
		return true;
	};

	bool isProcessed() const {
		cout << "isProcessed" << endl;

		return true;
	};

	bool isArchived() const {
		cout << "isArchived" << endl;

		return true;
	};

private:

};

// 初始化捕捉（广义捕捉）
void test1() {
	auto pw = std::make_unique<Widget>();

	auto func = [pw = std::move(pw)]{
		return pw->isValidated() && pw->isArchived();
	};

}

// 在c++11模拟初始化捕获
void test2() {

	// c++14 support
	std::vector<double> data{ 0.1f,2.2f,5.0f };
	auto func = [data = std::move(data)]{
		if (std::any_of(data.begin(),data.end(),[&](const auto& value) {
			return value == 2.1f;
		})) {
			cout << "size = "<< data.size() << endl;
		}
		else
		{
			cout << "has not 2.1f " << endl;
		}
	};

	func();

	// c++11 support
	std::vector<int> data2{ 1,10,101,1110 };

	auto func2 = std::bind([](const std::vector<int>& data) {

		//data.push_back(55);
		cout << "size = " << data.size() << endl;
	}, std::move(data2));
	func2();
	return;
}



int main(int argc, char* args[]) {

	test1();

	test2();

	return 0;
}