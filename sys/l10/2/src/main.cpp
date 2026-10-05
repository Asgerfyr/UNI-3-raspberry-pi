#include <thread>
#include <vector>
#include <iostream>
#include <mutex>

#define N_THREADS 2

int main() {
    
    std::vector<std::thread> thread;

    std::mutex mut;

    auto task1_print = [&](int id){
    
        for(int i = 0; i < 10; i++){
            mut.lock();
            std::cout << "id: " <<  id << "   i have printed: " << i+1 <<" times\n";
            mut.unlock();
        }

    };

    thread.emplace_back(task1_print, 0);
    thread.emplace_back(task1_print, 1);

    for(auto& t: thread){
        t.join();
    }

    return 0;
}

// Let's fix the printouts that were sometimes done on top of each other. Solve it first using a mutex and secondly using a semaphore.
// Questions

// Does it matter which of the two you use in this scenario? Why?
// Consider the three design options for placing the mutex/semaphore shown below. What are the consequences of the different design options? (Note that the answer to the below questions actullay do require some thought!)

// Inside the class - as a member variable?
// Outside the class - as a global variable, but solely used within the class?