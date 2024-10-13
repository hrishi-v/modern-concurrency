#include <thread>
#include <iostream>
#include <vector>

int main(){
	auto lambda = [](int x){
		std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
		std::cout << "Argument passed in: " << x << std::endl;
	};

	std::vector<std::jthread> jthreads;
	for (int i = 0; i < 10; i++){
		jthreads.push_back(std::jthread(lambda, i));
	}

	std::cout << "Hello from main thread!" << std::endl;
	return 0;
}

/* 
	In this example, we use 'jthread', a construct present in C++20 - this uses the principle of RAII, enabling auto-joining and cancellation.
	I see this like the smart pointer of the thread world!
	jthreads simply carry out the joining operation automatically when the thread leaves the scope it is initialised in.
*/