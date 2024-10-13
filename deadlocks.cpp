#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

static int shared_value = 0;
std::mutex mylock;

void shared_value_increment()
{
	//mylock.lock();
	std::lock_guard<std::mutex> lockGuard(mylock); // lock_guard: Lock that unlocks when out of scope!
	shared_value++; // The code between the lock and unlock is known as the critical section.
	//mylock.unlock();
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
	What are deadlocks?
	Deadlocks occur when critical sections do not end - a lock that is never unlocked by a thread that proceeds to go out of scope.
*/