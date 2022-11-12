//
// Created by abenisty on 10/5/22.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
extern "C" {
#endif

typedef unsigned int bigIntBaseType;
#define UNSIGNED_INT_MAX = 4294967295 // as in the max for one 'place' in the bigint structure
#define UNSIGNED_INT_MIN = 0

typedef struct {
    bigIntBaseType theValue;
}; bigIntBaseType















#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
}  // End of C/C++ bilingual code
#endif

#endif //BIGINT_BIGINT_H
