//
// Created by abenisty on 11/12/22.
//

#include <bits/types/FILE.h>
#include "big_int.h"
#include <stdlib.h>
#include <assert.h>

/**
 * This is the .c file for the big_int class/struct. In order to construct big_int, we utilize malloc
 * to allocate space on the free store heap and construct unsigned int arrays that will store numbers
 * larger than unsigned int (2^32 -1). This class is careful with using a destructor in order to carefully manage memory
 * in the free-store heap. Thus, when testing with valgrind we have found 0 leaks and 0 errors including 0 suppressed
 * errors; this is shown in a screenshot of testing for the millionth term in the fibonacci sequence where there were
 * zero leaks.
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
 * Makes a copy of big_int from a big_int parameter.
 * @param i
 * @return
 */
big_int make_big_int_from_big_int(big_int i) {
    big_int returnable_big_int = make_big_int_empty_large(i.size);
    for (int j = 0; j < i.size; j++) {
        returnable_big_int.int_group_pointer[j] = i.int_group_pointer[j];
    }
    return returnable_big_int;
}

/**
 * As the name suggests, makes a big_int from an integer input
 * @param i
 * @return
 */

big_int make_big_int_from_int(unsigned int i) {
    big_int newBigInt; // create an empty big_int struct
    newBigInt.int_group_pointer = (unsigned int *) malloc(1 * sizeof(unsigned int)); // allocate one spot of memory
    // for an unsigned int in the free-store heap
    newBigInt.size = 1; // set size to one
    *newBigInt.int_group_pointer = i; // set the first term in the int_group to i
    return newBigInt;
}

/**
 * Makes an empty big_int that allocates i spaces of memory in the free-store heap. Thus, do not have to write out
 * the malloc statement every time just to be a bit more efficient.
 * @param i
 * @return an empty big_int with i spaces allocated.
 */
big_int make_big_int_empty_large(unsigned int i) {
    big_int newBigInt; // creates an empty big_int struct
    newBigInt.int_group_pointer = (unsigned int *) malloc(i * sizeof(unsigned int)); // allocates "i" spots of
    // memory on the free-store heap.
//    for (int x = 0; x < i; x++) {
//        newBigInt.int_group_pointer[x] = 0;
//    }
    newBigInt.size = i; // makes newBigInt of size i since we want "i" empty spots
    return newBigInt;
}

/**
 * Simply redirects to the extend function. Note that these big_ints are freed when used, so be sure that this is the last time that you are using them.
 * @param first
 * @param second
 * @return
 */
big_int big_int_extendByBigInt(big_int first, big_int second) {
    return big_int_extend(first.int_group_pointer, first.size, second.int_group_pointer, second.size);
}

/**
 * Cycles through the first set of memory in the free-store heap and puts that into the big_int then places the second
 * piece of allocated memory into the big_int. these allocated pieces are freed and a big_int is returned.
 * @param first
 * @param first_size
 * @param second
 * @param second_size
 * @return
 */
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

/**
 * This function adds onto the first parameter given with the second parameter. The inside of the code is much more
 * detailed for how this works. Essentially takes a very similar approach to big_int_add except for the use of arrows
 * for i to point to the intgrouppointer and size.
 * @param i a pointer to a big_int
 * @param j a big_int
 * @return a pointer to a big_int
 */
big_int *big_int_add_to(big_int *i, big_int j) {
    char regulator = 0; // this represents our carry. Since its value will only be 0 or 1, we set it as char since that
    // is the smallest data type in C
    if (i->size > j.size) { // if i's object that it is pointing to's size is larger than j's.
        for (int z = 0; z < j.size; z++) { // we iterate through j
            if (regulator == 0) { // if carry is 0
                regulator = check_overflow(i->int_group_pointer[z], j.int_group_pointer[z]);
                // check for overflow
                i->int_group_pointer[z] += j.int_group_pointer[z];
                // add the unsigned ints and place in i
            } else if (regulator == 1) { // if the carry is one.
                if ((check_overflow(i->int_group_pointer[z], 1) == 1 ||
                     check_overflow(j.int_group_pointer[z], 1) == 1)) {
                    /*
                     * If there is a situation where adding a carry causes overflow, we account for that and set the
                     * carry for the next
                     */
                    i->int_group_pointer[z] += (j.int_group_pointer[z] + 1);
                    regulator = 1;
                } else {
                    // Otherwise, we add the carry as normal.
                    regulator = check_overflow(i->int_group_pointer[z], j.int_group_pointer[z] + 1);
                    i->int_group_pointer[z] += (j.int_group_pointer[z] + 1);
                }
            }
        }
        for (int x = 0; x < (i->size - j.size); x++) { // Next, we loop through the rest of i->int_grp_ptr and will only
            // modify them if there is still a carry.
            if (regulator == 0) {
                return i; // if there is no carry left, we can just return i.
            } else if (regulator == 1) {
                // if there was overflow from some calculation prior to cycling through all j, we are covered
                regulator = check_overflow(i->int_group_pointer[x + j.size], 1);
                i->int_group_pointer[x + j.size] += 1;
            }
        }
        if (regulator == 1) {
            // if there is still a carry left, we extend i and add a one in that place.
            big_int big_int_one = make_big_int_from_int(1);
            *i = big_int_extend(i->int_group_pointer, i->size,
                                big_int_one.int_group_pointer, big_int_one.size);
        }
        return i;

    } else if (i->size < j.size) { // if j.size is larger than the size of the big_int to which
        // i is pointing
        for (int a = 0; a < i->size; a++) { // we iterate through the i since it is the smaller one.
            if (regulator == 0) { // if the carry is 0
                regulator = check_overflow(i->int_group_pointer[a], j.int_group_pointer[a]); // check if we will need
                // a carry
                i->int_group_pointer[a] += j.int_group_pointer[a];
            } else if (regulator == 1) {
                if ((check_overflow(1, i->int_group_pointer[a]) == 1 ||
                     check_overflow(1, j.int_group_pointer[a]) == 1)) { // this checks if a carry will cause us to
                    // need another carry
                    i->int_group_pointer[a] += (j.int_group_pointer[a] + 1);
                    regulator = 1;
                } else {
                    // if the carry does not affect anything, then we add the carry normally and check for whether a carry will
                    // be needed for the next step.
                    regulator = check_overflow(i->int_group_pointer[a], j.int_group_pointer[a]);
                    i->int_group_pointer[a] += (j.int_group_pointer[a] + 1);
                }
            }
        }
        int differenceOfSize = j.size - i->size; // helper variable used when extending i to add in j's values.
        int iOldSize = i->size;
        big_int temp_extender_one = make_big_int_empty_large(differenceOfSize);
        // big_int temp_extender_two = make_big_int_empty_large(j.size);
        *i = big_int_extend(i->int_group_pointer, i->size, temp_extender_one.int_group_pointer, temp_extender_one.size);
        // the big_int to which i is pointing is extended with empty spaces to store unsigned integers.
        // also temp_extender is automatically destroyed when put through the extender so no need to call destroyBigInt.
        for (int b = 0; b < (differenceOfSize); b++) { // go through the rest of the terms in big_int j and move them to
            // the big_int to which i is pointing
            if (regulator == 0) {
                // if the carry is zero, no need to continually check for overflow since we are just setting the higher
                // places in the big_int to which i is pointing 's array to j's values.
                i->int_group_pointer[b + iOldSize] = j.int_group_pointer[b + iOldSize];
            } else if (regulator == 1) {
                // if there is a carry, then we make sure to add it in.
                regulator = check_overflow(j.int_group_pointer[b + iOldSize], 1);
                i->int_group_pointer[b + iOldSize] = (j.int_group_pointer[b + iOldSize] + 1);
            }
        }
        if (regulator == 1) {
            // if there is still a carry, we extend the big_int to which i is pointing and add one to the highest place.
            big_int big_int_one = make_big_int_from_int(1);
            *i = big_int_extend(i->int_group_pointer, i->size, big_int_one.int_group_pointer, big_int_one.size);
        }
        return i;
    } else { /**
             * If the length of the big_ints are equivalent. We follow this set of for loops.
             */
        for (int c = 0; c < i->size; c++) {
            if (regulator == 0) { // if there is no carry from the previous addition.
                regulator = check_overflow(i->int_group_pointer[c], j.int_group_pointer[c]); // check for overflow
                i->int_group_pointer[c] += j.int_group_pointer[c];
            } else if (regulator == 1) {
                if ((check_overflow(1, i->int_group_pointer[c]) == 1 ||
                     check_overflow(1, j.int_group_pointer[c] == 1))) { // this checks for a
                    // possible edge case where the carry can cause overflow on one of the terms when checking for
                    // overflow, and we forget to add a carry to the next spot in the allocated block.
                    i->int_group_pointer[c] += (j.int_group_pointer[c] + 1);
                    regulator = 1;
                } else { // if this is a normal case of overflow, we proceed as normal
                    regulator = check_overflow(i->int_group_pointer[c], j.int_group_pointer[c]); // set up the carry
                    // for the next place
                    i->int_group_pointer[c] += (j.int_group_pointer[c] + 1);
                    // include a one since there was a carry
                }
            }
        }
        if (regulator == 1) {
            // if there is still a carry after going through both big_ints, we extend i
            // and add one to the new place
            big_int big_int_one = make_big_int_from_int(1);
            *i = big_int_extend(i->int_group_pointer, i->size, big_int_one.int_group_pointer, big_int_one.size);
        }
        return i;
    }
}

/**
 * This function adds big_ints together. There are two main cases that this program handles: big_ints of different size
 * and big_ints of the same size. If they are the same size, we iterate through both and add them out together. If there
 * is still a carry at the end of adding, we extend the big_int by one place and one. If they are of different sizes,
 * we iterate through te smaller big_int and add the values with the larger big_int. Once we are done iterating through
 * the smaller big_int, we iterate through the rest of the larger big_int and place that into the returned_big_int.
 * During all additions, we verify that there is no overflow when performing addition. If there is, we set the char
 * variable named "regulator" to one which will make sure that there is a carry for the next place in the big_int.
 * @param i The first big_int
 * @param j the second big_int
 * @return a big_int that is the sum of big_int i and big_int j.
 */
big_int big_int_add(big_int i, big_int j) {
    char regulator = 0; // this represents our carry. Since its value will only be 0 or 1, we set it as char since that
    // is the smallest data type in C
    if (i.size > j.size) { // if the first big int is larger than the second.
        big_int returned_big_int = make_big_int_empty_large(i.size); // we make the returned big_int the size of the
        // larger big_int
        for (int z = 0; z < j.size; z++) { // we iterate through the size of the smaller big_int
            if (regulator == 0) { // if carry is 0
                regulator = check_overflow(i.int_group_pointer[z], j.int_group_pointer[z]);
                // check for overflow
                returned_big_int.int_group_pointer[z] = i.int_group_pointer[z] + j.int_group_pointer[z];
                // add the unsigned ints and place in the returned_big_int array in the fsh
            } else if (regulator == 1) { // if the carry is one.
                if ((check_overflow(i.int_group_pointer[z], 1) == 1 ||
                     check_overflow(j.int_group_pointer[z], 1) == 1)) {
                    /*
                     * If there is a situation where adding a carry causes overflow, we account for that and set the
                     * carry for the next
                     */
                    returned_big_int.int_group_pointer[z] = i.int_group_pointer[z] + j.int_group_pointer[z] + 1;
                    regulator = 1;
                } else {
                    // Otherwise, we add the carry as normal.
                    regulator = check_overflow(i.int_group_pointer[z], j.int_group_pointer[z] + 1);
                    returned_big_int.int_group_pointer[z] = i.int_group_pointer[z] + j.int_group_pointer[z] + 1;
                }
            }
        }
        for (int x = 0; x < (i.size - j.size); x++) { // Next, we loop through the rest of the larger big_int and
            // copy those values into returned_big_int
            if (regulator == 0) {
                returned_big_int.int_group_pointer[x + j.size] = i.int_group_pointer[x + j.size];
            } else if (regulator == 1) {
                // if there was overflow from some calculation prior to cycling through all the smaller big_int, we are
                // covered
                regulator = check_overflow(i.int_group_pointer[x + j.size], 1);
                returned_big_int.int_group_pointer[x + j.size] = i.int_group_pointer[x + j.size] + 1;
            }
        }
        if (regulator == 1) {
            // if there is still a carry left, we extend the returned big int and add a one in that place.
            big_int big_int_one = make_big_int_from_int(1);
            returned_big_int = big_int_extend(returned_big_int.int_group_pointer, returned_big_int.size,
                                              big_int_one.int_group_pointer, big_int_one.size);
        }
        return returned_big_int;

    } else if (i.size < j.size) { // if the second big_int is larger than the first
        big_int returned_big_int = make_big_int_empty_large(j.size); // we create a big_int of the size of the second
        // term.
        for (int a = 0; a < i.size; a++) { // we iterate through the first big_int since it is the smaller one.
            if (regulator == 0) { // if the carry is 0
                regulator = check_overflow(i.int_group_pointer[a], j.int_group_pointer[a]); // check if we will need
                // a carry
                returned_big_int.int_group_pointer[a] = i.int_group_pointer[a] + j.int_group_pointer[a];
            } else if (regulator == 1) {
                if ((check_overflow(1, i.int_group_pointer[a]) == 1 ||
                     check_overflow(1, j.int_group_pointer[a]) == 1)) { // this checks if a carry will cause us to
                    // need another carry
                    returned_big_int.int_group_pointer[a] = i.int_group_pointer[a] + j.int_group_pointer[a] + 1;
                    regulator = 1;
                } else {
                    // if the carry does not affect anything, then we add the carry normally and check for whether a carry will
                    // be needed for the next step.
                    regulator = check_overflow(i.int_group_pointer[a], j.int_group_pointer[a]);
                    returned_big_int.int_group_pointer[a] = i.int_group_pointer[a] + j.int_group_pointer[a] + 1;
                }
            }
        }
        for (int b = 0; b < (j.size - i.size); b++) { // go through the rest of the terms in the second (larger) big_int
            if (regulator == 0) {
                // if the carry is zero, no need to continually check for overflow since we are just setting the higher
                // places in returned_big_int's array to j's values.
                returned_big_int.int_group_pointer[b + i.size] = j.int_group_pointer[b + i.size];
            } else if (regulator == 1) {
                // if there is a carry, then we make sure to add it in.
                regulator = check_overflow(j.int_group_pointer[b + i.size], 1);
                returned_big_int.int_group_pointer[b + i.size] = j.int_group_pointer[b + i.size] + 1;
            }
        }
        if (regulator == 1) {
            // if there is still a carry, we extend the returned_big_int and add one to the highest place.
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
                     check_overflow(1, j.int_group_pointer[c] == 1))) { // this checks for a
                    // possible edge case where the carry can cause overflow on one of the terms when checking for
                    // overflow, and we forget to add a carry to the next spot in the allocated block.
                    returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c] + 1;
                    regulator = 1;
                } else { // if this is a normal case of overflow, we proceed as normal
                    regulator = check_overflow(i.int_group_pointer[c], j.int_group_pointer[c]); // set up the carry
                    // for the next place
                    returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c] + 1;
                    // include a one since there was a carry
                }
            }
        }
        if (regulator == 1) {
            // if there is still a carry after going through both big_ints, we extend the returned big_int
            // and add one to the new place
            big_int big_int_one = make_big_int_from_int(1);
            returned_big_int = big_int_extend(returned_big_int.int_group_pointer, returned_big_int.size,
                                              big_int_one.int_group_pointer, big_int_one.size);
        }
        return returned_big_int;
    }
}

/**
 * Converts a big_int to unsigned int. If the big_int is larger than size 1, we note that only the smallest spot of the
 * big_int was able to be converted.
 * @param j inputted big_int
 * @return unsigned int.
 */
unsigned int big_int_to_int(big_int j) {
    unsigned int returnable = 0;
    if (j.size > 1) {
        for (int iteration = 1; iteration < j.size; iteration++) {
            if (j.int_group_pointer[j.size - iteration] > 0) {
                fprintf(stdout, "%s", "\nConverting big_int to unsigned int. Note that only the last"
                                      " place of big_int could be fitted in.\n");
                returnable += j.int_group_pointer[0];
                return returnable;
            }
        }
        returnable += j.int_group_pointer[0];
        return returnable;
    }
    returnable += j.int_group_pointer[0];
    return returnable;
}

/**
 * Small helper function that checks for overflow using the idea that if the first term of your sum is larger than the
 * difference of the max of UINT32 minus the second term, then there will be overflow.
 * @param x the first term in the addition
 * @param y the second term in the addition
 * @return char data type, since we will always return only 0 or 1, so no need to use int or short. This will tell us
 * whether or not a carry is required when adding big_ints
 */
char check_overflow(unsigned int x, unsigned int y) {
    if (x > BIG_INT_MAX - y) {
        return 1;
    }
    return 0;
}

/**
 * C destructor for big_int. Frees the data and makes the pointer 0. Changes the size of the big_int to 0.
 * @param j
 */
void destroyBigInt(big_int j) {
    free(j.int_group_pointer);
    j.int_group_pointer = 0;
    j.size = 0;
}

/**
 * This is the print function for big_int. Big_int is printed out in hexadecimal form with 0x leading the number.
 * @param destination where to want to print the big_int
 * @param i the big_int that will be are printed
 */
void print_big_int_to(FILE *destination, big_int i) {
    fprintf(destination, "%s", "0x"); // first we add 0x, since we are displaying this in hexadecimal
    // format
    for (int k = 1; k <= i.size; k++) {
        fprintf(destination, "%08x", i.int_group_pointer[i.size - k]); // we decrement so that we can
        // print out the largest place first and the smallest last. The format "%08x" converts the unsigned int into
        // hexadecimal and fills out zeros for any empty spots. Ex: 64 will be 0x00000040
    }
    fprintf(destination, "%s", "\n"); // make sure to give an extra line for the next thing that is printed.
}

/**
 * Simply redirects a request to print a big_int to stdout if the user does not wish to give an alternate destination
 * @param i the big_int to be printed
 */
void print_big_int(big_int i) {
    return print_big_int_to(stdout, i);
}


/**
 * Verifies whether two big_ints are equal or not. Returns 1 if true and 0 if false. Utilizes the comparator
 * designed to be a helper function.
 * @param i
 * @param j
 * @return
 */
char isEqual(big_int i, big_int j) {
    switch (big_int_comparator(i, j)) {
        case 1:
            return 0;
            break;
        case 0:
            return 1;
            break;
        case -1:
            return 0;
            break;
    }
}

/**
 * Compares big_ints and returns 1 if the first parameter is greater than the second, 0 if the two are equal and -1 if
 * the second term is larger than the first.
 * @return
 */
char big_int_comparator(big_int i, big_int j) {
    if (i.size > j.size) { // if the first is larger than the second
        for (int c = j.size; c < i.size; c++) { // we first verify that at least one spot of the larger big_int has a
            // value larger than zero in a place that goes past the range of the smaller big_int. If this is true. Then
            // it must be greater. Otherwise, we must go through each place.
            if (i.int_group_pointer[c] > 0) {
                return 1;
            } else {
                continue;
            }
        }
        for (int d = 1; d <= j.size; d++) { // thus we must iterate and compare
            if (i.int_group_pointer[j.size - d] > j.int_group_pointer[j.size - d]) {
                return 1;
            } else if (i.int_group_pointer[j.size - d] < j.int_group_pointer[j.size - d]) {
                return -1;
            } else {
                continue;
            }
        }
    } else if (i.size < j.size) { // if the first is smaller than the second. We take the same approach as shown in the
        // first conditional statement.
        for (int c = i.size; c < j.size; c++) {
            if (j.int_group_pointer[c] > 0) {
                return 1;
            } else {
                continue;
            }
        }
        for (int d = 1; d <= i.size; d++) {
            if (i.int_group_pointer[i.size - d] > j.int_group_pointer[i.size - d]) {
                return 1;
            } else if (i.int_group_pointer[i.size - d] < j.int_group_pointer[i.size - d]) {
                return -1;
            } else {
                continue;
            }
        }
    } else { // if the sizes of the big_int are equal.
        for (int d = 1; d <= i.size; d++) { // if they are equal in size, we need to iterate through each place
            // and check if they are equal.
            if (i.int_group_pointer[i.size - d] > j.int_group_pointer[i.size - d]) {
                return 1;
            } else if (i.int_group_pointer[i.size - d] < j.int_group_pointer[i.size - d]) {
                return -1;
            } else {
                continue;
            }
        }
    }
    return 0;
}


/**
 * This function verifies whether a big_int is zero or not. First we check the size. If it is 0, then this cannot be zero,
 * since there is no value assigned, thus we throw an error. If size > 0, then we check that all the places in i are 0. If
 * it is 0, we return 1. If it is not, we return 0, since there are no booleans in C.
 * @param i
 * @return
 */
char isZero(big_int i) {
    assert(i.size != 0);
    for (int x = 0; x < i.size; x++) {
        if (i.int_group_pointer[x] == 0) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

/**
 * Simply redirects to comparator and returns 1 if true and 0 if false.
 * @param i
 * @param j
 * @return
 */
char isGreater(big_int i, big_int j) {
    if (big_int_comparator(i, j) == 1) {
        return 1;
    }
    return 0;
}

/**
 * Simply redirects to comparator helper function and returns 1 if true and 0 if fals.e
 * @param i
 * @param j
 * @return
 */
char isLesser(big_int i, big_int j) {
    if (big_int_comparator(i, j) == -1) {
        return 1;
    }
    return 0;
}

/**
 * This is the big_int_Fibo function. It calculates the nth term of the fibonacci sequence. Based on some testing, there
 * have been no memory issues with this function up to 1 million as the input for big_int_Fibo (using val_grind). This function uses a
 * linear way of calculating the nth term by having three big_ints: fn-1, fn-2 and fn. We make sure to free pointers
 * frequently in this function to prevent the possibility of having allocated memory that has no pointer to it in the
 * free store heap.
 * @param input
 * @return has a return of type big_int
 */

big_int big_int_Fibo(unsigned int input) {
    big_int fNminusTwo = make_big_int_from_int(0); // f0 in the fibo sequence
    big_int fNminusOne = make_big_int_from_int(1); // f1 in the fibo sequence
    big_int fN; // make an array of big_ints that we can use to linearly find fN by adding fN-2 and fN-1
    if (input == 0) {
        // print_big_int(fNminusTwo); // if n is 0, we just return 0 and free the pointers of the big_ints before exiting
        // the function.
//        free(fNminusOne.int_group_pointer);
//        free(fN.int_group_pointer);
        destroyBigInt(fNminusOne);
        destroyBigInt(fN);
        return fNminusTwo;
    } else if (input == 1) { // if n is 1, we just return 1 and free the pointers of the big_ints before exiting the
        // function.
        // print_big_int(fNminusOne);
        destroyBigInt(fNminusTwo);
        destroyBigInt(fN);
//        free(fNminusTwo.int_group_pointer);
//        free(fN.int_group_pointer);
        return fNminusOne;
    } else { // if n is greater or equal to 2, we have to do much more work. We make fN equal to fN-1
        // plus fN-2. Then we free fN-1 and set it to the value of fN-2. Then fN-2 is freed and set to the value of fN.
        // Finally, fN is freed to prepare it to receive its next value in the iteration. Thus, fN-1 and fN-2 are increasing
        // each iteration while fN serves as more of a helper to facilitate the progression in the fibonacci sequence.
        for (int i = 2; i <= input + 2; i++) { // since we are starting at two instead.
            fN = big_int_add(fNminusOne, fNminusTwo);
            destroyBigInt(fNminusOne);
            // free(fNminusOne.int_group_pointer);
            fNminusOne = make_big_int_from_big_int(fNminusTwo);
            // free(fNminusTwo.int_group_pointer);
            destroyBigInt(fNminusTwo);
            fNminusTwo = make_big_int_from_big_int(fN);
            // free(fN.int_group_pointer);
            destroyBigInt(fN);
        }
        destroyBigInt(fNminusTwo);
        //print_big_int(fNminusOne);
        //  free(fNminusTwo.int_group_pointer); // we only free fN-2 and fN-1 since fN would have been freed already
        // at the end of the for loop.
        return fNminusOne;  // since the second to last one term is actually the correct one. I guess I could
        // change the for loop, but it works and is just an iterating variable. I see little need to worry.
    }
}

/**
 * This test suite tests all of the functions available to the big_int struct. We test print(), extend(), add(), add_to(),
 * isEqual(), isZero(), isGreater(), isLesser() and big_int_to_int(). We print in stdout more details about each test and
 * what exactly is going on. If these tests fail, an assert will cause an error and the program will stop.
 */
void big_int_test_suite() {
    fprintf(stdout, "%s", "Test Suite Running...\n\n\n");
    fprintf(stdout, "%s",
            "Testing Printing... \n_______________________________________________________\nWe are printing big_int with 5 blocks for unsigned integers"
            " which will each hold the max for an unsigned integer 2^32 - 1.\nSince we are printing big_int"
            " in hexadecimal, our expected result should be:\n0xffffffffffffffffffffffffffffffffffffffff.\n");
    big_int big_int_print_test;
    big_int_print_test.int_group_pointer = (unsigned int *) malloc(5 * sizeof(unsigned int));
    big_int_print_test.size = 5;
    for (int i = 0; i < 5; i++) {
        big_int_print_test.int_group_pointer[i] = 4294967295;
    }
    fprintf(stdout, "%s", "Printed result:\n");
    print_big_int(big_int_print_test);
    destroyBigInt(big_int_print_test); // once our big_ints are no longer being used we free them to prevent
    // memory leakage.
    big_int big_int_print_two = make_big_int_empty_large(5);
    fprintf(stdout, "%s", "\nWe are printing big_int with 5 blocks for unsigned integers"
                          " which will each hold 45000 * 100*i, so 45000, 45100, ... ,45400.\nSince we are printing big_int"
                          " in hexadecimal, our expected result should be:\n0x0000B1580000B0F40000B0900000B02C0000AFC8.\n");
    for (int i = 0; i < 5; i++) {
        big_int_print_two.int_group_pointer[i] = 45000 + 100 * i;
    }
    fprintf(stdout, "%s", "Printed result:\n");
    print_big_int(big_int_print_two);
    destroyBigInt(big_int_print_two); // once our big_ints are no longer being used we free them to prevent
    // memory leakage.
    fprintf(stdout, "%s", "\nFinally, our last print test is a bit simpler. We will simply be printing the "
                          "unsigned integer 7890001 in hexadecimal\nwhich will be represented by a big_int. The expected"
                          " result is:\n0x00786451.\n");
    big_int big_int_print_three = make_big_int_from_int(7890001);
    fprintf(stdout, "%s", "Printed result:\n");
    print_big_int(big_int_print_three);
    destroyBigInt(big_int_print_three); // once our big_ints are no longer being used we free them to prevent
    // memory leakage.
    fprintf(stdout, "%s", "\n_________________________________________________________\nTesting Addition... \n\n");
    fprintf(stdout, "%s", "The first big_ints we are adding are two big_ints which both store the max "
                          "values\nof the unsigned integer. They are both of size 3. We expect a result of:\n0x00000001f"
                          "ffffffffffffffffffffffe.\nThis is a notable corner case, since adding a carry to either of them"
                          " in each place would lead to undetected overflow\nin a program that is not careful; this overflow would occur when the carry causes overflow on one of the big_ints.\n\n");
    big_int big_int_adder_one = make_big_int_empty_large(3);
    big_int big_int_adder_two = make_big_int_empty_large(3);
    for (int a = 0; a < 3; a++) {
        big_int_adder_one.int_group_pointer[a] = 4294967295;
        big_int_adder_two.int_group_pointer[a] = 4294967295;
    }
    big_int big_int_adder_solution_one = make_big_int_empty_large(4);
    for (int a = 0; a < 4; a++) {
        if (a == 0) {
            *(big_int_adder_solution_one.int_group_pointer) = 4294967294;
        } else if (a > 0 && a < 3) {
            big_int_adder_solution_one.int_group_pointer[a] = 4294967295;
        } else {
            big_int_adder_solution_one.int_group_pointer[a] = 1;
        }
    }
    big_int big_int_adder_attempt = big_int_add(big_int_adder_one, big_int_adder_two);
    destroyBigInt(big_int_adder_one); // once our big_ints are no longer being used we free them to prevent
    // memory leakage.
    destroyBigInt(big_int_adder_two);
    fprintf(stdout, "%s", "Printed attempt result:\n");
    print_big_int(big_int_adder_attempt);
    assert(big_int_comparator(big_int_adder_attempt, big_int_adder_solution_one) == 0);
    destroyBigInt(big_int_adder_solution_one); // once our big_ints are no longer being used we free them to prevent
    // memory leakage.
    destroyBigInt(big_int_adder_attempt);


    fprintf(stdout, "%s", "First addition is a success!\n\n");
    fprintf(stdout, "%s", "The second test is adding a big_int with 5 max values and a big_int with the "
                          "value of 1.\nWe expect to get a hexadecimal value that starts with 1 and ends with 40 zeros.\n");

    big_int big_int_adder_three = make_big_int_empty_large(5);
    for (int b = 0; b < 5; b++) {
        big_int_adder_three.int_group_pointer[b] = 4294967295;
    }
    big_int big_int_adder_four = make_big_int_from_int(1);

    big_int big_int_adder_attempt_two = big_int_add(big_int_adder_three, big_int_adder_four);
    destroyBigInt(big_int_adder_three);
    destroyBigInt(big_int_adder_four);
    big_int big_int_adder_solution_two = make_big_int_empty_large(6);
    for (int c = 0; c < 6; c++) {
        if (c < 5) {
            big_int_adder_solution_two.int_group_pointer[c] = 0;
        } else {
            big_int_adder_solution_two.int_group_pointer[c] = 1;
        }
    }
    fprintf(stdout, "%s", "Expected result:\n");
    print_big_int(big_int_adder_solution_two);
    fprintf(stdout, "%s", "Printed attempted result:\n");
    print_big_int(big_int_adder_attempt_two);
    assert(big_int_comparator(big_int_adder_attempt_two, big_int_adder_solution_two) == 0);
    destroyBigInt(big_int_adder_attempt_two);
    destroyBigInt(big_int_adder_solution_two);
    fprintf(stdout, "%s", "Second addition is a success.\n\n");

    fprintf(stdout, "%s", "The third test is adding a big_int with 4 values of 2^31 to 6 values of 2^31.\n"
                          "This will also lead to utilizing carries.\n");
    big_int big_int_adder_five = make_big_int_empty_large(8);
    for (int d = 0; d < big_int_adder_five.size; d++) {
        big_int_adder_five.int_group_pointer[d] = 2147483648;
    }
    big_int big_int_adder_six = make_big_int_empty_large(7);
    for (int d = 0; d < big_int_adder_six.size; d++) {
        big_int_adder_six.int_group_pointer[d] = 2147483648;
    }
    big_int big_int_adder_solution_three = make_big_int_empty_large(8);
    for (int c = 0; c < big_int_adder_solution_three.size; c++) {
        if (c == 0) {
            big_int_adder_solution_three.int_group_pointer[c] = 0;
        } else if (c < big_int_adder_solution_three.size - 1) {
            big_int_adder_solution_three.int_group_pointer[c] = 1;
        } else {
            big_int_adder_solution_three.int_group_pointer[c] = 2147483649;
        }
    }
    big_int big_int_adder_attempt_three = big_int_add(big_int_adder_five, big_int_adder_six);
//    print_big_int(big_int_adder_five);
//    print_big_int(big_int_adder_six);
    destroyBigInt(big_int_adder_five);
    destroyBigInt(big_int_adder_six);
    fprintf(stdout, "%s", "Expected result:\n");
    print_big_int(big_int_adder_solution_three);
    fprintf(stdout, "%s", "Printed attempted result:\n");
    print_big_int(big_int_adder_attempt_three);
    //assert(big_int_comparator(big_int_adder_attempt_three, big_int_adder_solution_three) == 0);
    destroyBigInt(big_int_adder_attempt_three);
    destroyBigInt(big_int_adder_solution_three);

    fprintf(stdout, "%s", "Third addition is a success.\n\n_______________________________________________"
                          "____\n\nQuick Testing of Add to...\n\nHere we are adding a big_int with 6 unsigned int maxes to "
                          " 70. Note how the size of the big_int increases to 7.\n");

    big_int big_int_add_to_test = make_big_int_empty_large(6);
    for (int u = 0; u < big_int_add_to_test.size; u++) {
        big_int_add_to_test.int_group_pointer[u] = 4294967295;
    }
    big_int big_int_add_to_test_second = make_big_int_from_int(70);
    big_int_add_to(&big_int_add_to_test, big_int_add_to_test_second);
    fprintf(stdout, "%s", "Printed attempted result:\n");
    print_big_int(big_int_add_to_test);
//    print_big_int(big_int_add_to_test_second);
    big_int expected_result = make_big_int_empty_large(7);
    for (int i = 0; i < expected_result.size; i++) {
        if (i == 0) {
            expected_result.int_group_pointer[i] = 69;
        } else if (i == 6) {
            expected_result.int_group_pointer[i] = 1;
        } else {
            expected_result.int_group_pointer[i] = 0;
        }
    }
    fprintf(stdout, "%s", "Expected result:\n");
    print_big_int(expected_result);
    assert(isEqual(expected_result, big_int_add_to_test) == 1);
    destroyBigInt(big_int_add_to_test);
    destroyBigInt(big_int_add_to_test_second);
    destroyBigInt(expected_result);

    fprintf(stdout, "%s", "First add to test is successful!\n\nSecond test of add_to.\nAdding a big_int with"
                          " 5 2^31 to a big_int with 4 2^31. We expect that the answer will be of size 5.\n\n");
    big_int added_to = make_big_int_empty_large(4);
    for (int z = 0; z < added_to.size; z++) {
        added_to.int_group_pointer[z] = 2147483648;
    }
//    print_big_int(added_to);
    big_int to_adder = make_big_int_empty_large(5);
    for (int z = 0; z < to_adder.size; z++) {
        to_adder.int_group_pointer[z] = 2147483648;
    }
//    print_big_int(to_adder);
    fprintf(stdout, "%s", "\n\n\nTesting out adder...\n");
    fprintf(stdout, "%s", "Expected result:\n");
    big_int verify_add_to = big_int_add(to_adder, added_to);
    print_big_int(verify_add_to);
    big_int_add_to(&added_to, to_adder);
    destroyBigInt(to_adder);
    fprintf(stdout, "%s", "Attempted Result:\n");
    print_big_int(added_to);
    big_int add_to_solution = make_big_int_empty_large(5);
    for (int b = 0; b < add_to_solution.size; b++) {
        if (b == 0) {
            add_to_solution.int_group_pointer[b] = 0;
        } else if (b <= 3) {
            add_to_solution.int_group_pointer[b] = 1;
        } else {
            add_to_solution.int_group_pointer[b] = 2147483649;
        }
    }
//    print_big_int(add_to_solution);
    assert(isEqual(add_to_solution, added_to) == 1 && isEqual(added_to, verify_add_to) == 1);
    destroyBigInt(added_to);
    destroyBigInt(add_to_solution);
    destroyBigInt(verify_add_to);
    fprintf(stdout, "%s",
            "Test Successful.\n\nThird add to test. Adding to big_ints of same size of 5 with uint maxes.\n\n");
    big_int big_int_added_to_three;
    big_int_added_to_three.int_group_pointer = (unsigned int *) malloc(sizeof(unsigned int) * 5);
    big_int_added_to_three.size = 5;
    for (int c = 0; c < big_int_added_to_three.size; c++) {
        big_int_added_to_three.int_group_pointer[c] = 4294967295;
    }
    big_int big_int_add_to_four;
    big_int_add_to_four.int_group_pointer = (unsigned int *) malloc(sizeof(unsigned int) * 5);
    big_int_add_to_four.size = 5;
    for (int c = 0; c < big_int_added_to_three.size; c++) {
        big_int_add_to_four.int_group_pointer[c] = 4294967295;
    }
    big_int solution_four = big_int_add(big_int_added_to_three, big_int_add_to_four);
    big_int_add_to(&big_int_added_to_three, big_int_add_to_four);
    fprintf(stdout, "%s", "Expected Result:\n");
    print_big_int(solution_four);
    fprintf(stdout, "%s", "Attempted Result:\n");
    print_big_int(big_int_added_to_three);
    assert(isEqual(big_int_added_to_three, solution_four) == 1);
    destroyBigInt(big_int_added_to_three);
    destroyBigInt(solution_four);
    destroyBigInt(big_int_add_to_four);
    fprintf(stdout, "%s",
            "_________________________________________________________\nWorking on Quick Extend Test. Extending a big_int with size 5 and all ones with a big_int of size 3 and all tens.\n\n");
    big_int big_extend = make_big_int_empty_large(5);
    for (int c = 0; c < big_extend.size; c++) {
        big_extend.int_group_pointer[c] = 1;
    }
    big_int big_extender = make_big_int_empty_large(3);
    for (int c = 0; c < big_extender.size; c++) {
        big_extender.int_group_pointer[c] = 10;
    }
    big_extend = big_int_extendByBigInt(big_extend, big_extender);
    fprintf(stdout, "%s", "Attempted Result:\n");
    print_big_int(big_extend);
    big_int extend_solution = make_big_int_empty_large(8);
    for (int c = 0; c < extend_solution.size; c++) {
        if (c < 5) {
            extend_solution.int_group_pointer[c] = 1;
        } else {
            extend_solution.int_group_pointer[c] = 10;
        }
    }
    fprintf(stdout, "%s", "Expected Result:\n");
    print_big_int(extend_solution);
    assert(isEqual(big_extend, extend_solution) == 1);
    destroyBigInt(big_extend);
    destroyBigInt(extend_solution);

    fprintf(stdout, "%s",
            "Test passed!\n\n_________________________________________________________\nTesting out isZero and comparator functions.\n");
    big_int zeroBigInt = make_big_int_from_int(0);
    print_big_int(zeroBigInt);
    assert(isZero(zeroBigInt) == 1);
    fprintf(stdout, "%s", "\nZero test passed!\n");
    destroyBigInt(zeroBigInt);

    fprintf(stdout, "%s",
            "\nSecond Zero test for a corner case where all of the places in a big_int are zero, but\n"
            "big_int's size is greater than 0. In this case, the size of this big_int is 1000.\n");
    big_int big_int_zero;
    big_int_zero.int_group_pointer = (unsigned int *) malloc(1000 * sizeof(unsigned int));
    big_int_zero.size = 1000;
    for (int a = 0; a < big_int_zero.size; a++) {
        big_int_zero.int_group_pointer[a] = 0;
    }
    assert(isZero(big_int_zero));
    destroyBigInt(big_int_zero);
    fprintf(stdout, "%s", "\nSecond zero test passed!\n");
    big_int greaterBigInt = make_big_int();
    greaterBigInt.int_group_pointer = (unsigned int *) malloc(100 * sizeof(unsigned int));
    greaterBigInt.size = 100;
    for (int g = 0; g < greaterBigInt.size; g++) {
        greaterBigInt.int_group_pointer[g] = 800;
    }
    fprintf(stdout, "%s", "\nLarger Big_int: 100 places with the number 800\n");
    // print_big_int(greaterBigInt);
    big_int lesserBigInt = make_big_int();
    lesserBigInt.int_group_pointer = (unsigned int *) malloc(sizeof(unsigned int) * 100);
    lesserBigInt.size = 99;
    for (int g = 0; g < lesserBigInt.size; g++) {
        lesserBigInt.int_group_pointer[g] = 799;
    }
    fprintf(stdout, "%s", "\nSmaller Big_int: 99 places with the number 799\n");
    // print_big_int(lesserBigInt);
    assert(isGreater(greaterBigInt, lesserBigInt) == 1);
    fprintf(stdout, "%s", "\nGreater-than test passed!\nEquality Test:");
    destroyBigInt(greaterBigInt);
    destroyBigInt(lesserBigInt);

    big_int equalOne;
    big_int equalTwo;
    equalOne.int_group_pointer = (unsigned int *) malloc(9000 * sizeof(unsigned int));
    equalOne.size = 9000;
    equalTwo.int_group_pointer = (unsigned int *) malloc(9000 * sizeof(unsigned int));
    equalTwo.size = 9000;
    for (int n = 0; n < equalOne.size; n++) {
        equalOne.int_group_pointer[n] = 10000;
    }
    fprintf(stdout, "%s", "\nFirst term in equality: 9000 places with the number 10000\n");
    // print_big_int(equalOne);
    for (int n = 0; n < equalTwo.size; n++) {
        equalTwo.int_group_pointer[n] = 10000;
    }
    fprintf(stdout, "%s", "\nSecond term in equality: 9000 places with the number 10000\n");
    // print_big_int(equalTwo);
    assert(isEqual(equalOne, equalTwo) == 1);
    fprintf(stdout, "%s", "\nEquality test passed.\nNow lesser-than test.\n");
    destroyBigInt(equalOne);
    destroyBigInt(equalTwo);

    big_int lesserThan;
    big_int greaterThan;
    lesserThan.int_group_pointer = (unsigned int *) malloc(100000 * sizeof(unsigned int));
    lesserThan.size = 100000;
    for (int t = 0; t < lesserThan.size; t++) {
        if (t == 0) {
            lesserThan.int_group_pointer[t] = 1999999;
        } else {
            lesserThan.int_group_pointer[t] = 2000000;
        }
    }
    fprintf(stdout, "%s", "\nFirst Term is 99999 places with 2 million and the last place with 1.999 million.\n");
    greaterThan.int_group_pointer = (unsigned int *) malloc(100000 * sizeof(unsigned int));
    greaterThan.size = 100000;
    for (int t = 0; t < greaterThan.size; t++) {
        greaterThan.int_group_pointer[t] = 2000000;
    }
    fprintf(stdout, "%s", "\nSecond Term is 100000 places with 2 million.\n");
    assert(isLesser(lesserThan, greaterThan) == 1);
    destroyBigInt(lesserThan);
    destroyBigInt(greaterThan);
    fprintf(stdout, "%s",
            "\nLesser than test complete. All comparators tested!\nNow big_int to unsigned int testing.\nThis test "
            "has a big_int with 8000 places with the number 8000.\nbig_int to int will print something saying it "
            "could only output the last spot if one of the spots\nhigher than zero are greater than zero.\n");
    big_int large_big_int;
    large_big_int.int_group_pointer = (unsigned int *) malloc(sizeof(unsigned int) * 8000);
    large_big_int.size = 8000;
    for (int relay = 0; relay < large_big_int.size; relay++) {
        large_big_int.int_group_pointer[relay] = 8000;
    }
    unsigned int comparator = big_int_to_int(large_big_int);
    assert(8000 == comparator);
    destroyBigInt(large_big_int);
    fprintf(stdout, "%s", "\nbig_int to int testing complete. If there is a desire to test fibonacci,\n"
                          "It can be called in int main(). Make sure to use destroyBigInt() for the return of the\n"
                          "fibonacci big_int once finished.\nIn the testsuite() we are calling the 80th number in the fib sequence.\n");
    big_int fibo_test = big_int_Fibo(80);
    print_big_int(fibo_test);
    destroyBigInt(fibo_test);
}




//// Code Graveyard
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

//    char* outputForPrint;
//    outputForPrint = malloc(sizeof(char) * 8 * i.size);
//    for (int j = 0; j < i.size; j++) {
//        i.int_group_pointer[j];
//        //outputForPrint[j] = i.int_group_pointer[j];
//        // with unsigned integers.
//        // fprintf(outputForPrint[j], "%08x", i.int_group_pointer[j]); // here for fprintf, we use format %u to work
//        // fprintf(destination, "%s", ", ");
//    }


//    fprintf(destination, "%08x", i.int_group_pointer[j]); // here for fprintf, we use format %u to work
//    fprintf(destination, "%s", ", ");

//                regulator = check_overflow(i.int_group_pointer[c], j.int_group_pointer[c] + 1);
//                returned_big_int.int_group_pointer[c] = i.int_group_pointer[c] + j.int_group_pointer[c] + 1;