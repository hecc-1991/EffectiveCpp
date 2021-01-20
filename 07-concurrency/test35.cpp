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
	// �����߳�
	std::thread t(doAsyncWork);
	t.join();

	// ��������
	auto fut = std::async(doAsyncWork);
	return;
}

int main(int argc, char* args[]) {

	test1();

	return 0;
}