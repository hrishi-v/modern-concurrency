#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

static int shared_value = 0;
std::mutex mylock;

void shared_value_increment(){
	mylock.lock();
		shared_value++; // The code between the lock and unlock is known as the critical section.
	mylock.unlock();
}

int main()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < 100; i++)
	{
		threads.push_back(std::thread(shared_value_increment));
	}

	for (auto &thread : threads)
	{
		thread.join();
	}

	std::cout << "Shared Value: " << shared_value << std::endl;
	return 0;
}

/*
	The code will run, and output the value expected (100) most of the time.
	However, as we do not use any mutual exclusions (mutex) the thread enter a "data race".
	This "data race" results in threads not having the latest value of the shared_value when they carry out the increment function.
	This can result in the shared_value output at the end of all the threads executing not being a deterministic result.
*/