//
// Created by abenisty on 11/12/22.
//

#include <bits/types/FILE.h>
#include "big_int.h"
#include <stdlib.h>

/**
 * This is the .c file for the big_int class/struct. In order to construct big_int, we utilize malloc
 * to allocate space on the free store heap and construct unsigned int arrays that will store numbers
 * larger than unsigned int (2^32 -1).
 */


/**
 * This makes an empty big_int struct with a size of 0 and a u_int pinter that is 0, since it points to nothing.
 * @return big_int
 */
big_int make_big_int() {
    big_int newBigInt; // create an empty big_int struct
    newBigInt.size = 0; // set size to zero
    newBigInt.int_group_pointer = 0; // set the pointer to zero since we want it to be empty
    return newBigInt;
}

/**
 * As the name suggests,
 * @param i
 * @return
 */

big_int make_big_int_from_int(unsigned int i) {
    big_int newBigInt; // create an empty big_int struct
    newBigInt.int_group_pointer = (unsigned int *) malloc(1 * sizeof(unsigned int)); // allocate one spot of memory
    // for an unsigned int in the free-store heap
    newBigInt.size = 1; // set size to one
    newBigInt.int_group_pointer[0] = i; // set the first term in the int_group to i
    return newBigInt;
}

big_int make_big_int_empty_large(unsigned int i) {
    big_int newBigInt; // creates an empty big_int struct
    newBigInt.int_group_pointer = (unsigned int *) malloc(i * sizeof(unsigned int)); // allocates "i" spots of
    // memory on the free-store heap.
    newBigInt.size = i; // makes newBigInt of size i since we want "i" empty spots
    return newBigInt;
}

big_int big_int_extend(unsigned int *first, unsigned int first_size, unsigned int *second, unsigned int second_size) {
    big_int big_int_extension;
    big_int_extension.int_group_pointer = (unsigned int *) malloc((first_size + second_size) * sizeof(unsigned int));
    for (int i = 0; i < first_size; i++) {
        big_int_extension.int_group_pointer[i] = first[i];
    }
    free(first);
    for (int j = 0; j < second_size; j++) {
        big_int_extension.int_group_pointer[j + first_size] = second[j];
    }
    free(second);
    big_int_extension.size = first_size + second_size;
    return big_int_extension;
}

big_int big_int_add(big_int i, big_int j) {
    short regulator = 0;
    if (i.size > j.size) {
        big_int returned_big_int = make_big_int_empty_large(i.size);
        for (int z = 0; z < j.size; z++) {
            if (regulator == 0) {
                regulator = check_overflow(i.int_group_pointer[z], j.int_group_pointer[z]);
                returned_big_int.int_group_pointer[z] = i.int_group_pointer[z] + j.int_group_pointer[z];
            } else if (regulator == 1) {
                regulator = check_overflow(i.int_group_pointer[z], j.int_group_pointer[z] + 1);
                returned_big_int.int_group_pointer[z] = i.int_group_pointer[z] + j.int_group_pointer[z] + 1;
            }
        }
        for (int x = 0; x < (i.size - j.size); x++) {
            if (regulator == 0) {
                returned_big_int.int_group_pointer[x + j.size] = i.int_group_pointer[x + j.size];
            } else if (regulator == 1) {
                regulator = check_overflow(i.int_group_pointer[x + j.size], 1);
                returned_big_int.int_group_pointer[x + j.size] = i.int_group_pointer[x + j.size] + 1;
            }
        }
        if (regulator == 1) {
            big_int big_int_one = make_big_int_from_int(1);
            returned_big_int = big_int_extend(returned_big_int.int_group_pointer, returned_big_int.size,
                                              big_int_one.int_group_pointer, big_int_one.size);
            //free(big_int_one.int_group_pointer);
        }
        return returned_big_int;

    } else if (i.size < j.size) {
        big_int returned_big_int = make_big_int_empty_large(j.size);
        for (int a = 0; a < i.size; a++) {
            if (regulator == 0) {
                regulator = check_overflow(i.int_group_pointer[a], j.int_group_pointer[a]);
                returned_big_int.int_group_pointer[a] = i.int_group_pointer[a] + j.int_group_pointer[a];
            } else if (regulator == 1) {
                regulator = check_overflow(i.int_group_pointer[a], j.int_group_pointer[a] + 1);
                returned_big_int.int_group_pointer[a] = i.int_group_pointer[a] + j.int_group_pointer[a] + 1;
            }
        }
        for (int b = 0; b < (j.size - i.size); b++) {
            if (regulator == 0) {
                returned_big_int.int_group_pointer[b + i.size] = j.int_group_pointer[b + i.size];
            } else if (regulator == 1) {
                regulator = check_overflow(j.int_group_pointer[b + i.size], 1);
                returned_big_int.int_group_pointer[b + i.size] = j.int_group_pointer[b + i.size] + 1;
            }
        }
        if (regulator == 1) {
            big_int big_int_one = make_big_int_from_int(1);
            returned_big_int = big_int_extend(returned_big_int.int_group_pointer, returned_big_int.size,
                                              big_int_one.int_group_pointer, big_int_one.size);
        }
        return returned_big_int;
    } else { /**
             * If the length of the big_ints are equivalent. We follow this set of for loops.
             */
        big_int returned_big_int = make_big_int_empty_large(i.size); // create a returnable for loop that is empty with
        // i.size spaces allocated in the free-store heap
        for (int c = 0; c < i.size; c++) {
            if (regulator == 0) { // if there is no carry from the previous addition.
                regulator = check_overflow(i.int_group_pointer[c], j.int_group_pointer[c]); // check for overflow
                returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c];
            } else if (regulator == 1) {
                if ((check_overflow(1, i.int_group_pointer[c]) == 1 ||
                     check_overflow(1, j.int_group_pointer[c] == 1)) &&
                    check_overflow(i.int_group_pointer[c], j.int_group_pointer[c])) { // this checks for a
                    // possible edge case where the carry can cause overflow on one of the terms when checking for
                    // overflow, and we forget to add a carry to the next spot in the allocated block.
                    returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c] + 1;
                    regulator = 1;
                }
//                regulator = check_overflow(i.int_group_pointer[c], j.int_group_pointer[c] + 1);
//                returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c] + 1;
            }
        }
        if (regulator == 1) {
            big_int big_int_one = make_big_int_from_int(1);
            returned_big_int = big_int_extend(returned_big_int.int_group_pointer, returned_big_int.size,
                                              big_int_one.int_group_pointer, big_int_one.size);
        }
        return returned_big_int;
    }
}

short check_overflow(unsigned int x, unsigned int y) {
    if (x > BIG_INT_MAX - y) {
        return 1;
    }
    return 0;
}

void print_big_int_to(FILE *destination, big_int i) {
//    char* outputForPrint;
//    outputForPrint = malloc(sizeof(char) * 8 * i.size);
//    for (int j = 0; j < i.size; j++) {
//        i.int_group_pointer[j];
//        //outputForPrint[j] = i.int_group_pointer[j];
//        // with unsigned integers.
//        // fprintf(outputForPrint[j], "%08x", i.int_group_pointer[j]); // here for fprintf, we use format %u to work
//        // fprintf(destination, "%s", ", ");
//    }
    for (int k = 0; k < i.size; k++) {
        fprintf(destination, "%08x", i.int_group_pointer[i.size - k]);
    }

//    fprintf(destination, "%08x", i.int_group_pointer[j]); // here for fprintf, we use format %u to work
//    fprintf(destination, "%s", ", ");
    fprintf(destination, "%s", "\n");
}

void print_big_int(big_int i) {
    return print_big_int_to(stdout, i);
}

void big_int_Fibo(unsigned int input) {


}

void big_int_test_suite() {

}

//        if (regulator == 1) { // if the regulator is still 1 at the last place, then we have a special case
//            regulator = check_overflow(i.int_group_pointer[j.size], 1); // here we check if there is overflow if we add into i's next place
//            if (regulator == 0) { // if there will be no overflow from the one
//                returned_big_int.int_group_pointer[j.size] = i.int_group_pointer[j.size] + 1;
//                for (int a = 1; a < (i.size - j.size); a++) {
//                    returned_big_int.int_group_pointer[j.size + a] = i.int_group_pointer[j.size + a];
//                }
//                return returned_big_int;
//            } else if (regulator == 1) { // if there is overflow from the one.
//                    for (int b = 0; b < (i.size - j.size); b++) {
//                        returned_big_int.int_group_pointer[j.size + b] = i.int_group_pointer[j.size + b] + 1;
//                    }
////                if (i.size - j.size == 1) {
////
////                } else if (i.size - j.size > 1) {
////                    returned_big_int.int_group_pointer[j.size] = i.int_group_pointer[j.size] + 1;
////                    for (int a = 1; a < (i.size - j.size); a++) {
////                        returned_big_int.int_group_pointer[j.size + a] = i.int_group_pointer[j.size + a];
////                    }
//                }
//            }
//        }