#include "heap.h"
#include <iostream>

using namespace std;

int main()
{
    stuff::heap<int> h(stuff::compare_max<int>);
    h.insert(1);
    h.insert(6);
    h.insert(3);
    h.insert(8);
    h.insert(4);
    h.insert(2);

    while (!h.is_empty()) {
        cout << h.remove() << endl;
    }

    return 0;
}
