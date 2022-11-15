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
//    auto doubleIntTest = DoubleInt(64);
//    std::cout << doubleIntTest << "\n" << std::endl;
    // DoubleIntTestFibonacci(inputFibo);
//    DoubleInt fiboCount = DoubleInt(15);
//    hccs_assert(DoubleIntTestFibonacci(fiboCount) == 610);
/**
 * Testing out big_int_extend here
 */
 /*
    big_int test_big_int = make_big_int_from_int(100000);
    print_big_int(test_big_int);
    unsigned int *Xtest = (unsigned int*) malloc(10 * sizeof(unsigned int));
    for (int z = 0; z < 10; z++) {
        Xtest[z] = 50 + z;
    }
    for (int y = 0; y < 10; y++) {
        fprintf(stdout, "%i", Xtest[y]);
    }
    fprintf(stdout, "%s", "\n");
    test_big_int = big_int_extend( Xtest, 10,test_big_int.int_group_pointer, test_big_int.size);
    print_big_int_to(stdout, test_big_int);
*/

    /**
     * Testing with big_int_add here
     */

//    big_int big_int_TestAdd = make_big_int_empty_large(2);
//    for (int c = 0; c < 6; c++) {
//        big_int_TestAdd.int_group_pointer[c] = 4294967295;
//    }
//    big_int one_big_int = make_big_int_from_int(1);
//
//    std::cout << "Adding... " << std::endl;
//    std::cout << "        ";
//    print_big_int_to(stdout, big_int_TestAdd);
//    std::cout << "and" << std::endl;
//    std::cout << "        ";
//    print_big_int_to(stdout, one_big_int);
//    std::cout << "Result: ";
//    big_int bigIntAddition = big_int_add(big_int_TestAdd, one_big_int);
//    print_big_int_to(stdout, bigIntAddition);
//    std::cout << "\n";
//
//    big_int big_int_TestAddTwo = make_big_int_empty_large(2);
//    for (int c = 0; c < 6; c++) {
//        big_int_TestAddTwo.int_group_pointer[c] = 4294967295;
//    }
//    big_int big_int_addition = big_int_add(big_int_TestAddTwo, big_int_TestAddTwo);
//
//    print_big_int_to(stdout, big_int_TestAddTwo);
//    print_big_int_to(stdout, big_int_TestAddTwo);
//
//    print_big_int_to(stdout, big_int_addition);

    big_int_test_suite();
    fprintf(stdout, "%s","\n\n\n\n");
    unsigned int fiboInput = 1000000;
    std::cout << "Testing the " << fiboInput <<" fibonacci value" << std::endl;
    big_int_Fibo(fiboInput);
    std::cout << "\n";
    std::cout << "all done" << std::endl;
}
