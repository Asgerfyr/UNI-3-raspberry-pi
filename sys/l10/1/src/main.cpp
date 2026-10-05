#include <thread>
#include <vector>
#include <iostream>

#define N_THREADS 2

int main() {
    
    std::vector<std::thread> thread;

    auto task1_print = [](int id){
    
        for(int i = 0; i < 10; i++){
            std::cout << "id: " <<  id << "   i have printed: " << i+1 <<" times\n";
        }

    };

    thread.emplace_back(task1_print, 0);
    thread.emplace_back(task1_print, 1);

    for(auto& t: thread){
        t.join();
    }

    return 0;
}

// Write a program that creates two threads.
// When creating the threads, they must be passed an ID, which they will print to stdout every second along with the number of times the thread has printed to stdout.
// When the threads have written to stdout 10 times each, they shall terminate.
// The main() function must wait for the two threads to terminate before continuing (hint: Look up std::join()).