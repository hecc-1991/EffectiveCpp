#include<iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;

using FilterContainer = std::vector<std::function<bool(int)>>;

FilterContainer filters;


void addDivisorFilter() {
	int div = 10;
	filters.emplace_back([&](int value) {// "=" is true but not safe absolutely
		cout << "div = " << div << endl;
		return value % div == 0;
	});
}

template<typename C>
void workWithContainer(const C& constainer)
{
	int div = 5;

	// C++11 use this 
	//using ConElemT = typename C::value_type;

	using std::begin;
	using std::end;
	if (std::all_of(
		begin(constainer), end(constainer),
		[&](const auto& value) {
		return value % div == 0;
	})
		)
	{
		cout << "all elem div by " << div << endl;
	}
	else {
		cout << "not all elem div by " << div << endl;

	}

}


class Widget
{
public:

	~Widget() {
		cout << " ~Widget() " << endl;
	}

	void addFilter() const;

private:
	int div{ 10 };

};

void Widget::addFilter() const {

	auto divCopy = div;

	filters.emplace_back([divCopy, div = div](int value) {
		cout << "div = " << div << ",divCopy = " << divCopy << endl;
		return value % div == 0;
	});
}

void doSomething() {
	auto w = std::make_unique<Widget>();
	//auto w = std::make_shared<Widget>();

	w->addFilter();
}


void addDivisorFilter2() {
	static int div2 = 10;
	filters.emplace_back([=](int value) {
		cout << "div = " << div2 << endl;
		return value % div2 == 0;
	});

	div2++;
}

// �����õ�Ĭ�ϲ�׽�ᵼ������
void test1() {
	addDivisorFilter();
	filters[0](5);
}

// ��������
void test2() {
	std::vector<int> cont{ 5,10,20,40 };
	workWithContainer(cont);
}

// lambda������ĳ�Ա������ʵ�ʲ������thisָ�룬���ʹ�á�=��ʱ������ʵ���ͷţ�lambda�еı���Ҳ������
void test3() {
	doSomething();
	filters[1](20);
}

// lambda��������static�����������ò���
void test4() {
	addDivisorFilter2();
	filters[2](30);
}


int main(int argc, char* args[]) {

	test1();
	test2();
	test3();
	test4();



	return 0;
}