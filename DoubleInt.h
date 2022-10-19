//
// Created by abenisty on 10/5/22.
//

#include "SafeInt.h"
#ifndef BIGINT_DOUBLEINT_H
#define BIGINT_DOUBLEINT_H


class DoubleInt {
public:
    DoubleInt(SafeInt i);
    DoubleInt(int i);
    DoubleInt();





    friend DoubleInt operator+();
private:
    DoubleInt theValue;
};


#endif //BIGINT_DOUBLEINT_H
