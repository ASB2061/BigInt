//
// Created by abenisty on 10/5/22.
//

#include "DoubleInt.h"
#include "SafeInt.h"
#include <exception>


DoubleInt::DoubleInt() {

}

DoubleInt::DoubleInt(int i) {
    // we want something to change so that a doubleInt is returned
    // that represents int i
    DoubleInt transformed = i;
}

DoubleInt::DoubleInt(SafeInt i) {
    // we want something to change so that a doubleInt is returned
    // that represents safeint i
    DoubleInt thingy = i;
}

//friend int DoubleInt::DoubleIntTestFibo(int input) {
//
//
//}
DoubleInt operator+(const DoubleInt &lhs, const int &rhs) {

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

DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs) {

}
DoubleInt operator+(const DoubleInt &lhs, const SafeInt &rhs) {

}