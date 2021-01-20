#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std::literals;

using std::cout;
using std::endl;

int doAsyncWork() {
	cout << "doAsyncWork" << endl;
	return 0;
}

void test1() {

	//不指定策略即默认启动策略，就是按照下面方式运行
//std::async(std::launch::async | std::launch::deferred,doAsyncWork);

	// std::launch::deferred 延迟运行，知道期值调用 get 或者 wait
	auto fut = std::async( std::launch::deferred,doAsyncWork);
	//auto ret = fut.get();
	//fut.wait();
	auto ret = fut.wait_for(100ms);

	return;
}

int doAsyncWork2() {
	cout << "doAsyncWork2" << endl;
	return 0;
}

void test2() {

	auto fut = std::async(doAsyncWork2);

	if (fut.wait_for(0ms) == std::future_status::deferred)
	{
		// 任务被延迟了
		fut.get();
	}
	else
	{
		while (fut.wait_for(300ms) != std::future_status::ready)
		{
			// 任务未被延迟，也未就绪
			cout <<"wait...\n" <<endl;
		}
	}

	return;
}

template<typename F,typename ...Ts>
inline auto reallyAsync(F&& f, Ts&& ... params) {
	return std::async(std::launch::async, 
		std::forward<F>(f),
		std::forward<Ts>(params)...
		);
}

int doAsyncWork3(std::string str) {

	std::this_thread::sleep_for(500ms);

	cout << "doAsyncWork3 : " << str << endl;
	return 0;
}

void test3() {

	reallyAsync(doAsyncWork3, std::string("hecc"));

	return;
}

int main(int argc, char* args[]) {

	test1();

	test2();

	test3();

	return 0;
}