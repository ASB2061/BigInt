//
// Created by abenisty on 10/5/22.
//

#include "SafeInt.h"
#include <climits>
#ifndef BIGINT_DOUBLEINT_H
#define BIGINT_DOUBLEINT_H

typedef int DoubleIntBaseType;

class DoubleInt {
public:
    // DoubleInt(SafeInt i);
    DoubleInt(int i);
    DoubleInt();
    friend int DoubleIntTestFibo(int input);




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

    static const DoubleIntBaseType MAX = 2147483647;
    static const DoubleIntBaseType MIN = -2147483648;

    int high32;
    int low32;
    int sign;
};


#endif //BIGINT_DOUBLEINT_H
