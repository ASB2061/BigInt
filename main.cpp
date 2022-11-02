//
// Created by davew on 10/12/21.
//


#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "SafeInt.h"
#include "String.h"
#include "DoubleInt.h"
#include <logic.h>

int main() {
    std::cout << "Hello, world" << std::endl;
    // need to add calls to test suite and/or user interface to work with the code here
    // String_Demo();
    // SafeInt_Demo();
    DoubleIntTestSuite();
    unsigned int pie;
    pie = UINT32_MAX + 1;
    std::cout << UINT32_MAX << "\n" << pie << std::endl;
//    DoubleInt fiboCount = DoubleInt(15);
//    hccs_assert(DoubleIntTestFibonacci(fiboCount) == 610);
    std::cout << "all done" << std::endl;
}
