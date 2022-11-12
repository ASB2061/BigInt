//
// Created by davew on 10/12/21.
//


#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "SafeInt.h"
#include "String.h"
#include "DoubleInt.h"
#include <logic.h>
#include "big_int.h"

int main() {
    std::cout << "Hello, world" << std::endl;
    // need to add calls to test suite and/or user interface to work with the code here
    // String_Demo();
    // SafeInt_Demo();

//    unsigned int pie;
//    pie = 10000 - 10001;
//    std::cout << pie << std::endl;

    // DoubleIntTestSuite();
    // unsigned int inputFibo = 93; // note that 93 is the highest fibonacci value that can be calculated with DoubleInt
    // std::cout << "Testing Fibonacci DoubleInt test function with input " << inputFibo << std::endl;

    // DoubleIntTestFibonacci(inputFibo);
//    DoubleInt fiboCount = DoubleInt(15);
//    hccs_assert(DoubleIntTestFibonacci(fiboCount) == 610);
    big_int test_big_int = make_big_int_from_int(100000);
    print_big_int(test_big_int);
    std::cout << "all done" << std::endl;
}
