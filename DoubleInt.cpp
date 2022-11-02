//
// Created by abenisty on 10/5/22.
//

#include "DoubleInt.h"
#include "SafeInt.h"
#include <exception>
#include <logic.h>


DoubleInt::DoubleInt() {
    low32 = 0;
    high32 = 0;
}

DoubleInt::DoubleInt(const DoubleInt &i) {
    low32 = i.low32;
    high32 = i.high32;
}

DoubleInt::DoubleInt(unsigned int i) {
    // we want something to change so that a doubleInt is returned
    // that represents int i.
    hccs_assert(i >= 0); // i must be greater or equal to 0 since we are letting doubleint be unsigned.
                         // technically, the assert statement is not needed since we require an unsigned integer to
                         // intialize
    low32 = i;
    high32 = 0;
}

//DoubleInt::DoubleInt(SafeInt i) {
//    // we want something to change so that a doubleInt is returned
//    // that represents safeint i
//    DoubleInt thingy = i;
//}

//friend int DoubleInt::DoubleIntTestFibo(int input) {
//
//
//}

DoubleInt operator+(const int &lhs, const DoubleInt &rhs) {
    if (rhs.low32 > lhs && lhs > INTMAX_MAX - rhs.low32) { // if these are both true,

    }
}

DoubleInt operator+(const DoubleInt &lhs, const int &rhs) {

}


DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs) {

}


DoubleInt operator-(const DoubleInt &lhs, const DoubleInt &rhs) {

}

DoubleInt operator-(const DoubleInt &lhs, const int &rhs) {

}

DoubleInt operator-(const int &lhs, const DoubleInt &rhs) {

}

bool operator>(const DoubleInt &lhs, const int &rhs) {
    if (lhs.low32 > rhs || lhs.high32 > 0) {
        return true;
    }
    return false;
}

bool operator>(const int &lhs, const DoubleInt &rhs) {
    if (lhs > rhs.low32 && rhs.high32 == 0) {
        return true;
    }
    return false;
}

bool operator>(const DoubleInt &lhs, const DoubleInt &rhs) {
    if (lhs.high32 > rhs.high32 || (lhs.high32 == rhs.high32 && lhs.low32 > rhs.low32)) {
        return true;
    }
    return false;
}

bool operator>=(const DoubleInt &lhs, const int &rhs) {
    if (lhs.low32 >= rhs || lhs.high32 > 0) {
        return true;
    }
    return false;
}

bool operator>=(const int &lhs, const DoubleInt &rhs) {
    if (lhs >= rhs.low32 && rhs.high32 == 0) {
        return true;
    }
    return false;
}

bool operator>=(const DoubleInt &lhs, const DoubleInt &rhs) {
    if (lhs.high32 > rhs.high32 || (lhs.high32 == rhs.high32 && lhs.low32 > rhs.low32) || (lhs.high32 == rhs.high32 && lhs.low32 == rhs.low32)) {
        return true;
    }
    return false;
}

bool operator<(const DoubleInt &lhs, const int &rhs) {

}

bool operator<(const int &lhs, const DoubleInt &rhs) {

}

bool operator<(const DoubleInt &lhs, const DoubleInt &rhs) {

}

bool operator<=(const DoubleInt &lhs, const int &rhs) {

}

bool operator<=(const int &lhs, const DoubleInt &rhs) {

}

bool operator<=(const DoubleInt &lhs, const DoubleInt &rhs) {

}

bool operator==(const DoubleInt &lhs, const int &rhs) {
    if (lhs.high32 <= 0 && lhs.low32 == rhs) {
        return true;
    }
    return false;
}

bool operator==(const int &lhs, const DoubleInt &rhs) {
    if (lhs == rhs.low32) {
        return true;
    }
}

bool operator==(const DoubleInt &lhs, const DoubleInt &rhs) {

}

/*
 * Note that this will need to be edited so that this sequence grows ***linearly!*** So the work does not increase so much
 */
DoubleInt DoubleIntTestFibonacci(DoubleInt input) {
    unsigned int fOne = 0;
    unsigned int fTwo = 1;
    auto f_one = DoubleInt(input);
    f_one = fOne;
//    for (int i = 0; i < input.low32; i++) {
//
//    }
//    if (input.low32 == 0) { // basic recursive design that will need to be fixed.
//        return 0;
//    } else if (input == 1) {
//        return 1;
//    } else {
//        return DoubleIntTestFibonacci(input - 1) + DoubleIntTestFibonacci(input - 2);
//    }
    return DoubleInt(1);
}