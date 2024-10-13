#include <thread>
#include <iostream>
#include <vector>

int main(){
	auto lambda = [](int x){
		std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
		std::cout << "Argument passed in: " << x << std::endl;
	};

	std::vector<std::thread> threads;
	for (int i = 0; i < 10; i++){
		threads.push_back(std::thread(lambda, i));
	}

	for (auto &thread : threads){
		thread.join();
	}

	std::cout << "Hello from main thread!" << std::endl;
	return 0;
}

/* 
	We can see that in this example, 10 threads are launched, executing the code in parallel.
	However, in this example, there is some interleaving between the output messages.
	This is because there are no conditions applied to the parallelisation of the code.
*/