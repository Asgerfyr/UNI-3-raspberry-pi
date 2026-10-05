#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <random>

// ==============================
// Linked List Node
// ==============================
struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

static std::atomic<int> stop = 0;

// ==============================
// Build Linked List
// ==============================
Node* build_linked_list(size_t n_nodes) {
    if (n_nodes == 0) return nullptr;

    // Random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 5000000);

    Node* head = new Node(dist(rng));
    Node* current = head;

    for (size_t i = 1; i < n_nodes; i++) {
        current->next = new Node(dist(rng));
        current = current->next;
    }
    return head;
}



// ==============================
// Sequential Search
// ==============================

Node* sequential_search(Node* begin, Node* end, int key)
{
    while (begin != end) {
        if (begin->value == key){
            return begin;
        }
        begin = begin->next;
    }
    return nullptr;
}


/* ==============================
   build_segments
   head: Head pointer of linked list
   n_nodes: Number of nodes in the linked list
   n_threads: Number threads we want to run in parallel
   returns: Vector with pointers to the beginning of each segment
   ============================== */
std::vector<Node*> build_segments(Node* head, size_t n_nodes, size_t n_threads) {
    std::vector<Node*> segments;
    if (!head || n_threads == 0) return segments;

    size_t chunk_size = n_nodes / n_threads;
    Node* current = head;
    size_t count = 0;

    while (current) {
        if (count % chunk_size == 0 && segments.size() < n_threads) {
            segments.push_back(current);
        }
        current = current->next;
        count++;
    }
    return segments;
}


void segment_search_thread(Node* begin, Node* end, const int key, Node** result){
    while (begin != end) {
        if(stop == 1) return;
        if (begin->value == key){
            stop = 1;
            *result = begin;
            return;
        }
        begin = begin->next;
    }
}
