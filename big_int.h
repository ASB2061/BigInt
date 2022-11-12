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
#define BIG_INT_MAX 4294967295
#define BIG_INT_MIN 0

typedef struct {
    big_int_base_type size;
    unsigned int *int_group_pointer;
} big_int;

big_int make_big_int();

big_int make_big_int_from_int(unsigned int i);

big_int make_big_int_empty_large(unsigned int i);

big_int big_int_extend(unsigned int *first, unsigned int first_size, unsigned int *second, unsigned int second_size);

big_int big_int_add(big_int i, big_int j);

#include <stdio.h>

short check_overflow(unsigned int x, unsigned int y);

void print_big_int_to(FILE *destination, big_int i);

void print_big_int(big_int i);

void big_int_Fibo(unsigned int input);

void big_int_test_suite();

#if defined __cplusplus // read this "extern C" only in C++
}
#endif

#endif //BIGINT_BIG_INT_H
