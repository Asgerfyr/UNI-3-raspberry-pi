#include <thread>
#include <vector>
#include <iostream>
#include "scoped_lock.h"
#include <mutex>

#define N_THREADS 2

int main() {
    
    std::vector<std::thread> thread;

    std::mutex mut;

    auto task1_print = [&](int id){
    
        for(int i = 0; i < 10; i++){
            scoped_lock lock(mut);
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

// From Wikipedia: "idiom is a code fragment having a semantic role[1] which recurs frequently across software projects."
// The Scoped Locking Idiom has the semantic role of: "From here until the end of this block (scope), this lock is held."
// Using the idiom works like this:
// { /* Scope begin */
//     /* -- Non-critical Section -- */
//     scoped_lock(mutex);
//     /* -- Critical Section -- */
// } /* Scope end: automatically unlocks mutex */
// Idioms allows C++ programmers to talk to JavaScript programmers about using ex. a Scoped Lock, even though the inner implementation may differ between languages. You'll see many more idioms in you upcoming career :-)
// So, let's fix the printing problem using a Scoped Lock, this means that you must first implement a C++ version of a such. Visit the Scoped Locking Idiom to find more details. Hint! Use std::mutex instead of Thread_Mutex.