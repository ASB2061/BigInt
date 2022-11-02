//
// Created by abenisty on 10/5/22.
//

#include "DoubleInt.h"
#include "SafeInt.h"
#include <exception>
#include <logic.h>


DoubleInt::DoubleInt() {
    this->low32 = 0;
    this->high32 = 0;
}

DoubleInt::DoubleInt(const DoubleInt &i) {
    this->low32 = i.low32;
    this->high32 = i.high32;
}

DoubleInt::DoubleInt(unsigned int i) {
    // we want something to change so that a doubleInt is returned
    // that represents int i.
    hccs_assert(i >= 0); // i must be greater or equal to 0 since we are letting doubleint be unsigned.
                         // technically, the assert statement is not needed since we require an unsigned integer to
                         // intialize
    this->low32 = i;
    this->high32 = 0;
}

DoubleInt::DoubleInt(unsigned int low, unsigned int high) {
    this->low32 = low;
    this->high32 = high;
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

DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs) {
    hccs_assert(!(lhs.high32 > UINT32_MAX - rhs.high32));
    // Essentially, we are trying to make sure that adding these two DoubleInts will not go over the storage limit of
    // the DoubleInt class by making sure that we will not overflow the higher 32 bits.
    DoubleInt returnable = DoubleInt();
    if (lhs.high32 == UINT32_MAX - rhs.high32) {
        hccs_assert(lhs.low32 <= UINT32_MAX - rhs.low32);
        // If the high bits add up to the maximum, the low bits have to not add to their maximum or there will be overflow.
        returnable.low32 = lhs.low32 + rhs.low32;
        returnable.high32 = lhs.high32 + rhs.high32;
        return returnable;
    } else if (lhs.high32 < UINT32_MAX - rhs.high32) {
        if (lhs.low32 > UINT32_MAX - rhs.low32) {
            returnable.low32 = lhs.low32 + rhs.low32;
            returnable.high32 = lhs.high32 + rhs.high32 + 1;
            return returnable;
        } else {
            returnable.low32 = lhs.low32 + rhs.low32;
            returnable.high32 = lhs.high32 + rhs.high32;
            return returnable;
        }
    }
    return returnable;
}

DoubleInt &DoubleInt::operator+=(const DoubleInt &rhs) {
    DoubleInt sum = *this + rhs;
    *this = sum;
    return *this;
}


DoubleInt operator-(const DoubleInt &lhs, const DoubleInt &rhs) {
    hccs_assert(lhs.high32 >= rhs.low32);

    return DoubleInt();
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


bool operator==(const DoubleInt &lhs, const int &rhs) {
    if (lhs.high32 <= 0 && lhs.low32 == rhs) {
        return true;
    }
    return false;
}

bool operator==(const int &lhs, const DoubleInt &rhs) {
    if (lhs == rhs.low32 && rhs.high32 == 0) {
        return true;
    }
    return false;
}

bool operator==(const DoubleInt &lhs, const DoubleInt &rhs) {
    if (lhs.high32 == rhs.high32 && lhs.low32 == rhs.low32)
        return true;
    return false;
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

void DoubleIntTestSuite() {
    std::cout << "Testing addition..." << std::endl;
    DoubleInt testingVarOne = DoubleInt();
    testingVarOne.low32 = UINT32_MAX;
    DoubleInt testingVarTwo = DoubleInt();
    testingVarTwo.low32 = 1;
    DoubleInt correctAnswerOne = DoubleInt(0, 1);
    DoubleInt testAnswer = testingVarOne + testingVarTwo;
    hccs_assert(correctAnswerOne == testAnswer);
    hccs_assert(DoubleInt(32, 32) == DoubleInt(UINT32_MAX, 15) + DoubleInt(33,16));

    std::cout << "Testing complete!" << std::endl;
}