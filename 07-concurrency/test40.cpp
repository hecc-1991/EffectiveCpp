#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <stdio.h>

using namespace std::literals;

using std::cout;
using std::endl;


// volatile 用于特种内存，告诉编译器不要优化变量
void test1()
{
	/*
	volatile int i = 10;
	int a = i;

	printf("i = %d", a);

	// 下面汇编语句的作用就是改变内存中 i 的值
	// 但是又不让编译器知道
	__asm {
		mov dword ptr[ebp - 4], 20h
	}

	int b = i;
	printf("i = %d", b);
	*/
}

// atomic 保证变量原子性
void test2()
{
	std::atomic_int x = 10;
	std::atomic<int> y(x.load());
	y.store(x.load());

	return;
}

void test3()
{
	std::atomic_int x = 10;

	register auto i = x.load();

	std::atomic<int> y(i);
	y.store(i);

	return;
}


int main(int argc, char* args[]) {

	test2();

	test3();

	return 0;
}