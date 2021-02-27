#include <iostream>
#include <thread>
#include <functional>
using namespace std;

void hello()
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cout << "hello concurrency world!\n";
}

void hello_bind(int a)
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cout << "hello_bind: a = " << a << endl;
}

class A
{
public:
	void operator()() const
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cout << "A()" << endl;
	}
};

auto f = std::bind(hello_bind, 4);

int main()
{
	//std::thread th(hello);
	//std::thread th(f);
	A a;
	std::thread th(a);
	th.join();
	system("pause");
	return 0;
}
