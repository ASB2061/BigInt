//
// Created by abenisty on 10/5/22.
//

//// This is the DoubleInt class .cpp file. Inside we have +, +=, >, >=, ==, and < operators. There is also a function
//// for outputting DoubleInt and two test functions, one that is a test suite and the other holds the fibonacci function.

#include "DoubleInt.h"
#include "SafeInt.h"
#include <exception>
#include <logic.h>
#include <iomanip>


// Basic constructor that makes the fields 0
DoubleInt::DoubleInt() {
    this->low32 = 0;
    this->high32 = 0;
}

// constructor that works with another DoubleInt
DoubleInt::DoubleInt(const DoubleInt &i) {
    this->low32 = i.low32;
    this->high32 = i.high32;
}

// constructor that works with unsigned int
DoubleInt::DoubleInt(unsigned int i) {
    // we want something to change so that a doubleInt is returned
    // that represents int i.
    hccs_assert(i >= 0); // i must be greater or equal to 0 since we are letting doubleint be unsigned.
                         // technically, the assert statement is not needed since we require an unsigned integer to
                         // intialize
    this->low32 = i;
    this->high32 = 0;
}

// constructor that works with two unsigned ints to make the high and low fields
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
        // if we have already reached the max number for the higher field, the lower field cannot go over.
        hccs_assert(lhs.low32 <= UINT32_MAX - rhs.low32);
        // If the high bits add up to the maximum, the low bits have to not go past the maximum or there will be overflow.
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

DoubleInt::operator int() const {
    // could throw bad_cast exception, except that can't happen since SafeInt must be in bounds :-)
    hccs_assert(this->high32 == 0);
    return this->low32;
}


DoubleInt &DoubleInt::operator+=(const DoubleInt &rhs) {
    // fairly simple mutator that mostly borrows from the add operator. We make sure to use *this and then return it.
    // mostly borrowed from the safeInt class.
    DoubleInt sum = *this + rhs;
    *this = sum;
    return *this;
}


DoubleInt operator-(const DoubleInt &lhs, const DoubleInt &rhs) { // this needs to be edited
    hccs_assert(lhs.high32 > rhs.high32 || (lhs.high32 == rhs.high32 && lhs.low32 > rhs.low32)); // otherwise we will get a negative value
    DoubleInt returnable = DoubleInt();
    if (lhs.high32 > rhs.high32) {
        returnable.high32 = lhs.high32 - rhs.high32;
        if (lhs.low32 >= rhs.low32) {
            returnable.low32 = lhs.low32 - rhs.low32;
            return returnable;
        } else {
            returnable.low32 = lhs.low32 - rhs.low32;
            returnable.high32 -= 1; // this is a way of representing 'borrowing' a higher bit
            return returnable;
        }
    }
    returnable = DoubleInt(lhs.low32 - rhs.low32, 0);
    return returnable;
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

bool operator<(const DoubleInt &lhs, const DoubleInt &rhs) {
    if (lhs.high32 < rhs.high32) {
        return true;
    } else if (lhs.high32 == rhs.high32) {
        if (lhs.low32 < rhs.low32) {
            return true;
        }
        return false;
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
    if ((lhs.high32 > rhs.high32) || (lhs.high32 == rhs.high32 && lhs.low32 >= rhs.low32)) {
        return true;
    }
    return false;
}

bool operator==(const DoubleInt &lhs, const int &rhs) {
    if (lhs.high32 == 0 && lhs.low32 == rhs) {
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
    if (lhs.high32 == rhs.high32 && lhs.low32 == rhs.low32) {
        return true;
    }
    return false;
}

bool isZero(const DoubleInt &lhs) {
    if (lhs == DoubleInt(0, 0)) {
        return true;
    }
    return false;
}

/*
 * Fibonacci Test using DoubleInt. Start with F1 and F2 being 0 and 1 and DoubleInt types. We create an array of DoubleInts
 * and return the last value in the array that was produced.
 */
void DoubleIntTestFibonacci(unsigned int input) {
    auto fOne = DoubleInt(0);
    auto fTwo = DoubleInt(1);
    DoubleInt fArray[input];
    for (int i = 0; i <= input; i++) {
        if (i<=1) {
            fArray[i] = fOne + fTwo;
        } else {
            fArray[i] = fOne + fTwo;
            fOne = fTwo; // fOne and fTwo continue to change each loop so that we are always adding f(n-1) + f(n-2)
            // without actually doing that recursive step
            fTwo = fArray[i];
        }
    }
    std::cout << "Result: " << fArray[input] << std::endl;
}

std::ostream &operator<<(std::ostream &any_ostream, const DoubleInt &printMe)             // output operation
{
    std::stringstream stream; // this method was partially helped with an answer from stackoverflow by user Kornel Kisielewicz
    // viewed on November 2, 2022 link: https://stackoverflow.com/a/5100745 . Here the library <iomanip> is used along
    // with std::stringstream and std::hex to convert the double int parts to hexadecimal. 0x is also added to the front
    // of the hexadecimal representation and std::setfill and std::setw make sure that there are sixteen places in total
    // to represent all of DoubleInt
    return any_ostream << "0x" << std::setfill('0') << std::setw(8) << std::hex << printMe.high32 << std::setfill('0')
    << std::setw(8) << std::hex << printMe.low32 << std::dec;  // note that std::dec is used b/c the library used to
    // convert double int to hexadecimal is a bit finicky with everything else and started converting things outside
    // the DoubleInt class into hexadecimal even though std::hex was not called, but perhaps because we forgot to revert
    // to std::dec
}

void DoubleIntTestSuite() {
    std::cout << "Testing addition...\n" << std::endl;
    auto testingVarOne = DoubleInt(UINT32_MAX);
    auto testingVarTwo = DoubleInt(1);
    DoubleInt correctAnswerOne = DoubleInt(0, 1);
    DoubleInt testAnswer = testingVarOne + testingVarTwo;
    hccs_assert(correctAnswerOne == testAnswer);
    hccs_assert(DoubleInt(0, 1) == DoubleInt(UINT32_MAX, 0) + DoubleInt(1,0));
    hccs_assert(DoubleInt(95, UINT32_MAX) == DoubleInt(20, 150000) + DoubleInt(75,4294817295));
    hccs_assert(DoubleInt(0, 1) == DoubleInt(2147483648, 0) + DoubleInt(2147483648,0));

    std::cout << "Testing addition mutator...\n" << std::endl;
    hccs_assert((DoubleInt(1,1)+= DoubleInt(UINT32_MAX, 2)) == DoubleInt(0, 4));
    std::cout << "Testing comparison operators and zero testing\n" << std::endl;
    hccs_assert(DoubleInt(UINT32_MAX - 7, 1) > DoubleInt(32, 0));
    hccs_assert(DoubleInt(UINT32_MAX - 7, 0) > DoubleInt(UINT32_MAX - 8, 0));
    hccs_assert(DoubleInt(UINT32_MAX - 7, 1) >= DoubleInt(UINT32_MAX - 7, 1));
    hccs_assert(DoubleInt(32, 0) < DoubleInt(UINT32_MAX - 7, 1));
    hccs_assert(DoubleInt(32, 1) < DoubleInt(33, 1));
    hccs_assert(isZero(DoubleInt(0, 0)));

    std::cout << "Testing subtraction...\n" << std::endl;
    hccs_assert(DoubleInt(UINT32_MAX, 0) == DoubleInt(0, 1) - DoubleInt(1,0));
    hccs_assert(DoubleInt(0, 0) == DoubleInt(1, 0) - DoubleInt(1,0));




    std::cout << "Testing output for DoubleInt. Decimal Value for this test is 47244640255\n" << std::endl;
    std::cout << "Got: " << DoubleInt(4294967295, 10) << "\nExpected: 0x0000000affffffff" << std::endl;
    std::cout << "Testing complete!" << std::endl;
}