//
// Created by abenisty on 10/5/22.
//

#include "DoubleInt.h"
#include "SafeInt.h"
#include <exception>


DoubleInt::DoubleInt() {
    low32 = 0;
    high32 = 0;
}

DoubleInt::DoubleInt(int i) {
    // we want something to change so that a doubleInt is returned
    // that represents int i
    sign = 0;
    if (i > 0) {
        sign = 1;
    } else if (i < 0) {
        sign = -1;
    }
    low32 = abs(i);
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
    if (lhs.sign > 0 && rhs.sign > 0) {

    }   else if (lhs.sign > 0 && rhs.sign < 0) {

    } else if ()
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


int DoubleIntTestFibo(int input) {
    if (input == 0) { // basic recursive design that will need to be fixed.
        return 0;
    } else if (input == 1) {
        return 1;
    } else {
        return DoubleIntTestFibo(input - 1) + DoubleIntTestFibo(input - 2);
    }
}