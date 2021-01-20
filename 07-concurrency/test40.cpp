#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <stdio.h>

using namespace std::literals;

using std::cout;
using std::endl;


// volatile ���������ڴ棬���߱�������Ҫ�Ż�����
void test1()
{
	/*
	volatile int i = 10;
	int a = i;

	printf("i = %d", a);

	// �������������þ��Ǹı��ڴ��� i ��ֵ
	// �����ֲ��ñ�����֪��
	__asm {
		mov dword ptr[ebp - 4], 20h
	}

	int b = i;
	printf("i = %d", b);
	*/
}

// atomic ��֤����ԭ����
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