//
// Created by abenisty on 10/5/22.
//

/*
 * This is the DoubleInt Class header. DoubleInt is a class where we are doubling the max space for the data type int.
 * For now, we are assuming that DoubleInt is an unsigned integer. Thus, the maximum value DoubleInt can hold should be
 * 2^64 - 1. We utilize two data fields, both unsigned integers. One represents the high 32 bits and the other the low 32 bits.
 */

#include "SafeInt.h"
#include <climits>
#ifndef BIGINT_DOUBLEINT_H
#define BIGINT_DOUBLEINT_H

class DoubleInt {
public:
    // DoubleInt(SafeInt i);

    // Constructors
    DoubleInt();
    DoubleInt(unsigned int i);
    DoubleInt(DoubleInt const &i);
    DoubleInt(unsigned int low, unsigned int high);

   // friend DoubleInt operator+(const DoubleInt &lhs, const int &rhs);
    friend DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs);

   // friend DoubleInt operator-(const DoubleInt &lhs, const int &rhs);
    friend DoubleInt operator-(const DoubleInt &lhs, const DoubleInt &rhs);

    DoubleInt &operator+=(const DoubleInt &rhs);

    friend bool operator>(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator>(const int &lhs, const DoubleInt &rhs);
    friend bool operator>(const DoubleInt &lhs, const int &rhs);

    friend bool operator<(const DoubleInt &lhs, const DoubleInt &rhs);

    friend bool operator>=(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator>=(const int &lhs, const DoubleInt &rhs);
    friend bool operator>=(const DoubleInt &lhs, const int &rhs);

//    friend bool operator<(const DoubleInt &lhs, const DoubleInt &rhs);
//    friend bool operator<(const int &lhs, const DoubleInt &rhs);
//    friend bool operator<(const DoubleInt &lhs, const int &rhs);
//
//    friend bool operator<=(const DoubleInt &lhs, const DoubleInt &rhs);
//    friend bool operator<=(const int &lhs, const DoubleInt &rhs);
//    friend bool operator<=(const DoubleInt &lhs, const int &rhs);

    friend bool operator==(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator==(const int &lhs, const DoubleInt &rhs);
    friend bool operator==(const DoubleInt &lhs, const int &rhs);

    friend bool isZero(const DoubleInt &lhs);

    explicit operator int() const;

    unsigned int high32;
    unsigned int low32;
};

void DoubleIntTestFibonacci(unsigned int input);

std::ostream &operator<<(std::ostream &any_ostream, const DoubleInt &printMe); // output operation

void DoubleIntTestSuite();

#endif //BIGINT_DOUBLEINT_H
