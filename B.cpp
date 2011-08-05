#include "B.hpp"
#include <iostream>

using namespace std;


//extern "C" void doo(); 

void
B::foo(int a, const char *b) {
     int i;
     cout << "B::foo() called." << endl;
}

int
B::goo(int a, const char *b) {
    cout << "B::goo() called." << endl;
    return 1234;
}
