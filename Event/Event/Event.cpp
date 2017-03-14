#include <iostream>
#include "Event.h"

class  EventTest
{
	public:
		EventTest(){};
		~EventTest(){};
		void bindTest();
		void test1(std::chrono::system_clock::time_point);
		void test2(std::chrono::system_clock::time_point);
		void test3(std::chrono::system_clock::time_point);
		void test4(std::chrono::system_clock::time_point);
		void trigger();

	private:
		core::Event<void(std::chrono::system_clock::time_point)> m_distanceChanged;
};

void EventTest::bindTest()
{
	std::function<void(std::chrono::system_clock::time_point)>testfunc1 = std::bind(&EventTest::test1, this, std::placeholders::_1);
	std::function<void(std::chrono::system_clock::time_point)>testfunc2 = std::bind(&EventTest::test2, this, std::placeholders::_1);
	std::function<void(std::chrono::system_clock::time_point)>testfunc3 = std::bind(&EventTest::test3, this, std::placeholders::_1);
	std::function<void(std::chrono::system_clock::time_point)>testfunc4 = std::bind(&EventTest::test4, this, std::placeholders::_1);
	core::InstanceFunction<void(std::chrono::system_clock::time_point)> insfunc1(testfunc1, this, "test1");
	core::InstanceFunction<void(std::chrono::system_clock::time_point)> insfunc2(testfunc2, this, "test2");
	core::InstanceFunction<void(std::chrono::system_clock::time_point)> insfunc3(testfunc3, this, "test3");
	core::InstanceFunction<void(std::chrono::system_clock::time_point)> insfunc4(testfunc4, this, "test4");
	m_distanceChanged += insfunc1;
	m_distanceChanged += insfunc2;
	m_distanceChanged += insfunc3;
	m_distanceChanged += insfunc4;
}

void EventTest::test1(std::chrono::system_clock::time_point)
{
	std::cout << "Hello C++ EventHandle£¡" << std::endl;
}

void EventTest::test2(std::chrono::system_clock::time_point)
{
	std::cout << "Hello C++ EventHandle£¡" << std::endl;
}

void EventTest::test3(std::chrono::system_clock::time_point)
{
	std::cout << "Hello C++ EventHandle£¡" << std::endl;
}

void EventTest::test4(std::chrono::system_clock::time_point)
{
	int i;
	std::cin >> i;
}

void EventTest::trigger()
{
	core_Event_Trigger(m_distanceChanged, std::chrono::system_clock::now());
}

int main()
{
	core::Event<void()> m_distanceChanged;
	EventTest test;
	test.bindTest();
	test.trigger();
	//std::function<void()> fa = Test1;
	//core::InstanceFunction<void(std::chrono::system_clock::time_point)>func(fa,);
	return 0;
}