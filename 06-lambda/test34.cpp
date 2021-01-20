#include <iostream>
#include <chrono>
#include <functional>
#include <typeinfo>

using std::cout;
using std::endl;

using namespace std::chrono;
using namespace std::literals;

using namespace std::placeholders;

using Time = steady_clock::time_point;
using Duration = steady_clock::duration;


enum class Sound :uint32_t
{
	Beep = 0,
	Siren,
	Whistle
};

enum class Volume
{
	Normal,
	Loud,
	LoudPlus
};





void setAlarm(Time t, Sound s, Duration d) {

	cout << "at "<< time_point_cast<seconds>(t).time_since_epoch().count()
		<< " , during "<<  duration_cast<seconds>(d).count() << endl;
}


// ������������ʱ��std::bind���޷�ʶ���������뱨��
void setAlarm(Time t, Sound s, Duration d,Volume v) {

	cout << "at " << time_point_cast<seconds>(t).time_since_epoch().count()
		<< " , during " << duration_cast<seconds>(d).count() 
		<< " , Volume " << endl;
}


// lambda �� std::bind ����ʵ�ַ�ʽ���Ƽ�ǰ��
void test1() {

	auto setSoundL =
		[](Sound s) {
		
		setAlarm(steady_clock::now()+1h, s, 30s);
	};

	using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);

	// std::bind��ʵ������ִ��
	auto setSoundB = std::bind(static_cast<SetAlarm3ParamType>(setAlarm), steady_clock::now() + 1h,_1,30s);

	// std::bind��ʵ������ִ�У����鱾��һ��
	auto setSoundB2 = std::bind(static_cast<SetAlarm3ParamType>(setAlarm),
		std::bind(std::plus<>(), steady_clock::now(), hours(1)),
		_1,seconds(30));

	char name[50];
	std::cin >> name;

	setSoundL(Sound::Siren);

	setSoundB(Sound::Whistle);

	setSoundB2(Sound::Beep);

	return;

}


// lambda �� std::bind ����ʵ�ַ�ʽ���Ƽ�ǰ��
void test2() {
	auto lowVal = 10;
	auto highVal = 100;
	// c++14 lambda֧��auto
	auto betweenL = [lowVal, highVal](const auto& val) {
		return val >= lowVal&& val <= highVal;
	};

	auto betweenB = std::bind(std::logical_and<>(),
		std::bind(std::less_equal<>(),lowVal,_1),
		std::bind(std::less_equal<>(),_1,highVal)
	);


	auto retL = betweenL(5);

	auto retB = betweenB(56);

	return;
}

enum class Compress : int
{
	Low = 0,
	Normal,
	High

};
class Widget
{
public:
	Compress c{Compress::Normal};
private:

};



Widget compress(const Widget& w, Compress lev) {
	auto arr = {"Low","Normal","High"};
	
	cout << "lev : " << *(arr.begin() + static_cast<int>(lev)) << endl;
	Widget w2;
	w2.c = lev;
	return w2;
}

void test3() {
	Widget w;
	// lambda w��ֵ����lev��ֵ����
	auto compressL = [w](Compress lev) {
		compress(w, lev);
	};

	// std::bind���Ǹ�����ʵ�Σ�������ÿ���ʹ��std::ref
	auto compressB = std::bind(compress,w,_1);

	// lambda��������ֵ��ʵ�Σ���ֵ����
	compressL(Compress::Low);

	// �󶨶����ʵ�Σ������ô���
	compressB(Compress::High);
	
}

class PolyWidget
{
public:

	template<typename T>
	void operator ()(const T& param) {
		cout << typeid(param).name() << endl;
	}

private:

};



void test4() {
	PolyWidget pw;
	auto boundPWB = std::bind(pw, _1);

	boundPWB(12306);
	boundPWB(nullptr);
	boundPWB("hecc");

	PolyWidget pw2;
	auto boundPWL = [&pw2](const auto& param) {
		pw2(param);
	};

	boundPWL(9999.9);
	boundPWL('x');
	boundPWL(pw2);

	return;
}


int main(int argc, char* args[]) {

	//test1();

	//test2();

	//test3();

	test4();

	return 0;
}