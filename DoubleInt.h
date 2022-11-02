//
// Created by abenisty on 10/5/22.
//

/*
 * This is the DoubleInt Class header. DoubleInt is a class where we are doubling the max space for the data type int.
 * For now, we are assuming that DoubleInt is an unsigned integer. Thus, the maximum value DoubleInt can hold should be
 * 2^64 - 1.
 */

#include "SafeInt.h"
#include <climits>
#ifndef BIGINT_DOUBLEINT_H
#define BIGINT_DOUBLEINT_H

typedef int DoubleIntBaseType;

class DoubleInt {
public:
    // DoubleInt(SafeInt i);
    DoubleInt(unsigned int i);
    DoubleInt(DoubleInt const &i);
    DoubleInt();




    friend DoubleInt operator+(const DoubleInt &lhs, const int &rhs);
    friend DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs);

    friend DoubleInt operator-(const DoubleInt &lhs, const int &rhs);
    friend DoubleInt operator-(const DoubleInt &lhs, const DoubleInt &rhs);

    friend bool operator>(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator>(const int &lhs, const DoubleInt &rhs);
    friend bool operator>(const DoubleInt &lhs, const int &rhs);

    friend bool operator>=(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator>=(const int &lhs, const DoubleInt &rhs);
    friend bool operator>=(const DoubleInt &lhs, const int &rhs);

    friend bool operator<(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator<(const int &lhs, const DoubleInt &rhs);
    friend bool operator<(const DoubleInt &lhs, const int &rhs);

    friend bool operator<=(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator<=(const int &lhs, const DoubleInt &rhs);
    friend bool operator<=(const DoubleInt &lhs, const int &rhs);

    friend bool operator==(const DoubleInt &lhs, const DoubleInt &rhs);
    friend bool operator==(const int &lhs, const DoubleInt &rhs);
    friend bool operator==(const DoubleInt &lhs, const int &rhs);

    static const DoubleIntBaseType MAX = 429496795;
    static const DoubleIntBaseType MIN = 0;

    unsigned int high32;
    unsigned int low32;
};

DoubleInt DoubleIntTestFibonacci(DoubleInt input);


#endif //BIGINT_DOUBLEINT_H
