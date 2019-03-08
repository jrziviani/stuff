#include "priority_queue.h"
#include <iostream>

using namespace std;

int main()
{
    stuff::priority_queue<int> pq(stuff::priority_queue<int>::type::MIN_PRIORITY);
    pq.enqueue(10);
    pq.enqueue(5);
    pq.enqueue(3);
    pq.enqueue(8);
    pq.enqueue(2);

    while (!pq.is_empty()) {
        cout << pq.dequeue() << endl;
    }
}
