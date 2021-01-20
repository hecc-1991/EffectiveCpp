#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std::literals;

using std::cout;
using std::endl;

class ThreadRAII
{
public:
	enum class DtorAction
	{
		join,
		detach
	};

	ThreadRAII(std::thread&& t,DtorAction a):action(a),t(std::move(t)){};

	~ThreadRAII() {
		if (t.joinable())
		{
			if (action == DtorAction::join)
			{
				t.join();
			}
			else
			{
				t.detach();
			}
		}
	};

	std::thread& get() {
		return t;
	}

	ThreadRAII(ThreadRAII&&) = default;
	ThreadRAII& operator=(ThreadRAII&&) = default;

private:
	DtorAction action;
	std::thread t;
};

constexpr auto tenMillion = 10'000'000;

bool conditionAreSatisfied() {
	return false;
}

void performComputatoin(std::vector<int> v) {
	cout << v.size() << endl;
}

bool doWork(std::function<bool(int)> filter, int maxVal = tenMillion)
{
	std::vector<int> goodVals;
	ThreadRAII t(
		std::thread([&filter, maxVal, &goodVals]() {
		auto _maxVal = maxVal;
		for (int i = 0; i <= _maxVal; ++i)
		{
			if (filter(i))
				goodVals.push_back(i);
		}


	})
		,
		ThreadRAII::DtorAction::join
		);

	auto nh = t.get().native_handle();

	if (conditionAreSatisfied())
	{
		t.get().join();
		performComputatoin(goodVals);
		return true;
	}
	return false;
}

void test1() {

	doWork([&](int i) {
		cout << i << endl;
		return i % 100 == 0 ? true : false;
	},1000);
	
	return;
}



int main(int argc, char* args[]) {

	test1();


	return 0;
}