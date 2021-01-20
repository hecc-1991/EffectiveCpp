#include <memory>
#include <iostream>

using std::cout;
using std::endl;

template<typename T>
float normalize(T&& v) {
	auto ret = v / 100.0;
	return ret;
}

// lambda����������Ϊauto&&���βΣ�ʹ��decltype����std::forward֮��
void test1() {

	auto f = [](auto&&... params) {
		return normalize(std::forward<decltype(params)>(params)...);
	};

	auto ret = f(20);

	cout << ret << endl;

}

int main(int argc, char* args[]) {

	test1();


	return 0;
}