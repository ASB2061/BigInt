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

    // DoubleIntTestSuite();
    // unsigned int inputFibo = 93; // note that 93 is the highest fibonacci value that can be calculated with DoubleInt
    // std::cout << "Testing Fibonacci DoubleInt test function with input " << inputFibo << std::endl;
    // DoubleIntTestFibonacci(inputFibo);
    //    output_Big_Int.int_group_pointer = (unsigned int *) malloc(sizeof(unsigned int) * 3);
//    output_Big_Int.size = 3;
//    destroyBigInt(output_Big_Int);
//    free(output_for_Fibo.int_group_pointer);
//    big_int output_Big_Int = make_big_int();

    big_int_test_suite();
    fprintf(stdout, "%s", "_____________________________________________________________\n");
    unsigned int fiboInput = 1000;
    std::cout << "Testing the " << fiboInput << " fibonacci value" << std::endl;
    big_int output_for_Fibo = big_int_Fibo(fiboInput);
    print_big_int(output_for_Fibo);
    destroyBigInt(output_for_Fibo);


    std::cout << "\n";
    std::cout << "all done" << std::endl;
}
