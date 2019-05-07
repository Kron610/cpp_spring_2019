#include <iostream>
#include <mutex>
#include <thread>
constexpr size_t COUNT = 500000;
std::mutex mutex;
std::mutex mutex2;
void Ping()
{
	for (size_t i = 0; i < COUNT; i++)
	{
		mutex.lock();
		std::cout << "ping\n";
		mutex2.unlock();
	}
}

void Pong()
{
	for (size_t i = 0; i < COUNT; i++)
	{
		mutex2.lock();
		std::cout << "pong\n";
		mutex.unlock();
	}
}

int main()
{
	std::thread thread1(Ping);
	mutex2.lock();
	std::thread thread2(Pong);
	thread1.join();
	thread2.join();
	return 0;
}
