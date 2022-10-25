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

DoubleInt operator+(const DoubleInt &lhs, const int &rhs) {

}

DoubleInt operator+(const DoubleInt &lhs, const DoubleInt &rhs) {

}
DoubleInt operator+(const DoubleInt &lhs, const SafeInt &rhs) {

}