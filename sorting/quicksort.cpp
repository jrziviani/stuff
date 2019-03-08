#include "quicksort.h"

#include <iostream>

using namespace std;

bool check(stuff::vector<int> &v)
{
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1])
            return false;
    }
    return true;
}

int main()
{
    stuff::vector<int> v;
    v.append(1);
    v.append(5);
    v.append(6);
    v.append(3);
    v.append(2);
    v.append(1);
    v.append(4);
    v.append(7);

    stuff::quicksort<int>(v,
            [](const int &a, const int &b) {
                return a < b;
            });

    v.iterate([](int &a) { cout << a << endl; });
    return 0;
    for (size_t i = 0; i < 200; i++) {
        stuff::quicksort<int>(v,
                [](const int &a, const int &b) {
                    return a > b;
                });
        if (!check(v)) {
            cerr << "ouch!" << endl;
            break;
        }
    }

    v.iterate([](int &a) { cout << a << endl; });

    /*
    stuff::list<int> l;
    l.append(5);
    l.append(7);
    l.append(1);
    l.append(9);
    l.append(8);
    l.append(2);
    l.append(0);
    l.append(10);
    l.append(6);

    stuff::quicksort<int>(l,
            [](const int &a, const int &b) {
                return a < b;
            });

    //l.iterate([](int &a) { cout << a << endl; });
*/
    return 0;
}
