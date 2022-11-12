//
// Created by abenisty on 11/12/22.
//

#ifndef BIGINT_BIG_INT_H
#define BIGINT_BIG_INT_H

/**
 * This is the header file that contains the base type, function names with parameters, and the struct.
 * */

#if defined __cplusplus // read this "etern C" line _only_ when we're using C++
extern "C" {
#endif

struct big_int {
    unsigned int *int_group_pointer;
    int size;

};

struct big_int make_big_int();

void print_big_int();

void big_int_Fibo(unsigned int input);


#if defined __cplusplus // read this "extern C" only in C++
}
#endif

#endif //BIGINT_BIG_INT_H
