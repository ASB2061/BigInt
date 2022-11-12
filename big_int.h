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

#include <stdlib.h>

typedef unsigned int big_int_base_type;

typedef struct {
    big_int_base_type size;
    unsigned int *int_group_pointer;
} big_int;

big_int make_big_int();

big_int make_big_int_from_int(unsigned int i);

#include <stdio.h>

unsigned int print_big_int_to(FILE *destination, big_int i);

unsigned int print_big_int(big_int i);

void big_int_Fibo(unsigned int input);

#if defined __cplusplus // read this "extern C" only in C++
}
#endif

#endif //BIGINT_BIG_INT_H
