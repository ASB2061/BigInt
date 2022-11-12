//
// Created by abenisty on 11/12/22.
//

#include <bits/types/FILE.h>
#include "big_int.h"

/**
 * This is the .c file for the big_int class/struct. In order to construct big_int, we utilize malloc
 * to allocate space on the free store heap and construct unsigned int arrays that will store numbers
 * larger than unsigned int (2^32 -1).
 */

big_int make_big_int() {
    big_int newBigInt;
    newBigInt.size = 0;
    newBigInt.int_group_pointer = 0;
    return newBigInt;
}

big_int make_big_int_from_int(unsigned int i) {
    big_int newBigInt;
    newBigInt.int_group_pointer = (unsigned int *) malloc(1 * sizeof(unsigned int));
    newBigInt.size = 1;
    newBigInt.int_group_pointer[0] = i;
    return newBigInt;
}

big_int big_int_extend(unsigned int *first, unsigned int first_size, unsigned int *second, unsigned int second_size) {

    unsigned int *returned_big_int_array;
    returned_big_int_array = (unsigned int *) malloc((first_size + second_size)*sizeof(unsigned int));
    for (int i = 0; i < first_size; i++) {
        returned_big_int_array[i] = first[i];
    }
    free(first);
    for (int j = 0; j < second_size; j++) {
        returned_big_int_array[j + first_size] = second[j];
    }
    free(second);

}

unsigned int print_big_int_to(FILE *destination, big_int i) {
    for (int j = 0; j < i.size; j++) {
        fprintf(destination, "%i", i.int_group_pointer[j]);
    }
    fprintf(destination, "%s", "\n");
    return 0;
}

unsigned int print_big_int(big_int i) {
    return print_big_int_to(stdout, i);
}

void big_int_Fibo(unsigned int input) {


}

