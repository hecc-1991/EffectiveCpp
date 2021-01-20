#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <deque>

using namespace std::literals;

using std::cout;
using std::endl;


std::condition_variable cv;
std::mutex m;

bool flag(false);

std::deque<int> queue_;

void request(const char *thread_name) {

	while (true) {

		// detect event
		std::this_thread::sleep_for(1ms);
		static int i = 0;

		auto id = std::this_thread::get_id();
		//cout << "thread name : " << thread_name << ", id : " << id << " func : " << "request" << endl;

		{
			std::unique_lock<std::mutex> g(m);
			
			//cout << "thread name : " << thread_name << ", id : " << id << " lock " << endl;
			queue_.push_back(i);
			cout << "thread name : " << thread_name << ", id : " << id << " input i = "<< i << endl;
			i++;
			flag = true;
		}
		cv.notify_one();
		//cout << "thread name : " << thread_name << ", id : " << id << " unlock" << endl;
	} 
}

void reply(const char* thread_name) {

	while (true) {

		// prepare
		std::this_thread::sleep_for(1ms);

		auto id = std::this_thread::get_id();
		//cout << "thread name : " << thread_name << ", id : " << id << " func : " << "reply" << endl;

		{
			std::unique_lock<std::mutex> lk(m);

			//cout << "thread name : " << thread_name << ", id : " << id << " lock " << endl;
			/*
			wait函数都在会阻塞时，自动释放锁权限，
			即调用unique_lock的成员函数unlock（），
			以便其他线程能有机会获得锁。
			这就是条件变量只能和unique_lock一起使用的原因，
			否则当前线程一直占有锁，线程被阻塞。
			*/
			cv.wait(lk, [] {
				return flag;
			});
			if (!queue_.empty())
			{
				auto i = queue_.front();
				cout << "thread name : " << thread_name << ", id : " << id << " output i =  " << i << endl;
				queue_.pop_front();
			}

			flag = false;
		}
		//cout << "thread name : " << thread_name << ", id : " << id << " unlock " << endl;
	}
}

void test1() {
	std::thread t1(request, "t1");
	std::thread t2(reply, "t2");

	std::thread t3(request, "t3");
	std::thread t4(reply, "t4");

	t1.join();
	t2.join();

	t3.join();
	t4.join();
}

//#################### 一次性通信事件
std::promise<void> p;

void react()
{
	cout << "id : " << std::this_thread::get_id() <<" react" << endl;
}

void detect()
{
	auto sf = p.get_future().share();
	constexpr auto threadsToRun = 10;
	std::vector<std::thread> ths;
	for (size_t i = 0; i < threadsToRun; i++)
	{
		ths.emplace_back([sf] {
			sf.wait();
			react();
		});
	}

	// 此处若跑出异常，则detect会失去响应
	std::this_thread::sleep_for(100ms);

	// 让所有线程取消暂停
	p.set_value();

	// todo
	// ...

	for (auto& t : ths)
	{
		t.join();
	}

}

void test2() {
	detect();
}

int main(int argc, char* args[]) {

	//test1();

	test2();

	return 0;
}