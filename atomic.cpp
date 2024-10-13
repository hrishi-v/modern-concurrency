#include <thread>
#include <iostream>
#include <vector>

static std::atomic<int> shared_value = 0;

void shared_value_increment()
{
	shared_value+=1; // must use ++ to avoid data race
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