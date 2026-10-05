#include "linklist.h"

#define N_NODES 10000000

#define N_THREADS 16

int main() {
    Node* head = build_linked_list(N_NODES);

    Node* current = head;

    for(int i = 0; i < 100;i++){
        std::cout << "i=" << i << " value=" << current->value << std::endl;
        current = current->next;
    }


    
    //test tid for process
    auto time_start = std::chrono::high_resolution_clock::now(); 
    
    Node* res = sequential_search(head, nullptr, 212);

    auto time_end = std::chrono::high_resolution_clock::now();
    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    std::cout << "duration: " << time_diff << " ms" << std::endl;


    if(res != nullptr) 
    {
        std::cout << 212 << "was found: " << res->value << std::endl;
    }
    



    std::vector<Node*> results(N_THREADS, nullptr);

    std::vector<Node*> segments = build_segments(head, N_NODES, N_THREADS);
    segments.push_back(nullptr);

    std::vector<std::thread> threads(N_THREADS);


    //test thread 
    time_start = std::chrono::high_resolution_clock::now(); 

    for(int i = 0; i < N_THREADS; i++){
        threads[i] = std::thread(segment_search_thread, segments[i], segments[i+1], 212, &results[i]);
    }
    
    for(int i = 0; i < N_THREADS; i++){
        threads[i].join();
    }

    time_end = std::chrono::high_resolution_clock::now();
    time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
    std::cout << "duration: " << time_diff << " ms" << std::endl;


    for(int i = 0; i < N_THREADS; i++){
        if(results[i]){
            std::cout << "result of thread: " << i << " : " << results[i] << " : " << results[i]->value << std::endl;
            break;
        }
    }

    return 0;
}