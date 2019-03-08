#include "list.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    stuff::list<int> l;
    l.append(3);
    l.prepend(5);
    l.prepend(6);
    l.prepend(0);
    l.prepend(2);
    l.append(7);
    l.append(1);
    l.iterate([](int &d) { cout << d << endl; });

    cout << "at 5: " << l[5] << endl;

    cout << "----\n";

    l.pop();
    l.pop();
    l.iterate([](int &d) { cout << d << endl; });

    cout << "----\n";

    l.dequeue();
    l.pop();
    l.dequeue();
    l.iterate([](int &d) { cout << d << endl; });

    cout << "----\n";

    l.pop();
    l.pop();
    l.pop();
    l.iterate([](int &d) { cout << d << endl; });


    return 0;
}
