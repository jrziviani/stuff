#include "mergesort.h"
#include <iostream>

using namespace std;

int main()
{
    stuff::vector<int> v;
    v.append(3);
    v.append(10);
    v.append(2);
    v.append(1);
    v.append(4);
    v.append(3);
    v.append(6);
    v.append(9);
    v.append(15);
    v.append(2);
    v.append(12);
    v.append(11);
    v.append(5);
    v.append(9);
    v.append(3);
    v.append(5);
    stuff::mergesort<int>(v,
            [](const int &a, const int &b) {
                return a < b;
            });

    v.iterate([](int &d) { cout << d << endl; });
    cout << "--------\n";

    /*
    stuff::list<int> l;
    l.append(3);
    l.append(10);
    l.append(2);
    l.append(1);
    l.append(4);
    l.append(3);
    l.append(6);
    l.append(9);
    l.append(0);
    stuff::mergesort<int>(l,
            [](const int &a, const int &b) {
                return a < b;
            });

    l.iterate([](int &d) { cout << d << endl; });
    */
}
