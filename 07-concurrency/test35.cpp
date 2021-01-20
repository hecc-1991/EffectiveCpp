#include <iostream>
#include <thread>
#include <future>

using std::cout;
using std::endl;

int doAsyncWork() {
	cout << "doAsyncWork" << endl;
	return 0;
}

void test1() {
	// 基于线程
	std::thread t(doAsyncWork);
	t.join();

	// 基于任务
	auto fut = std::async(doAsyncWork);
	return;
}

int main(int argc, char* args[]) {

	test1();

	return 0;
}