// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// Note: Couldn't #include "float_bits.c" because of error when using 'give'

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {

    // PUT YOUR CODE HERE
    
    // Create and malloc a float_components_t struct
    float_components_t *fs = malloc(sizeof(float_components_t));
    // Extract sign
    fs->sign = (f >> 31) & (uint32_t)1;
    // Extract biased exponent
    fs->exponent = (f >> 23) & 0xFF;
    // Extract fraction
    fs->fraction = f & 0x7FFFFF;
    
    return *fs;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {

    // PUT YOUR CODE HERE
    // is_nan() does not take into account +/-NaN
    if ((f.exponent == 0xFF) && (f.fraction != 0)) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {

    // PUT YOUR CODE HERE

    if ((f.sign == 0) && (f.exponent == 0xFF) && (f.fraction == 0)) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {

    // PUT YOUR CODE HERE

    if ((f.sign == 1) && (f.exponent == 0xFF) && (f.fraction == 0)) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {

    // PUT YOUR CODE HERE
    // is_zero() does not take into account +/- 0
    if ((f.exponent == 0) && (f.fraction == 0)) {
        return 1;
    } else {
        return 0;
    }
    
}

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {

    // PUT YOUR CODE HERE

    float_components_t f1 = float_bits(bits1);
    float_components_t f2 = float_bits(bits2);

/*
    Note: This approach does not entirely work becauese when both numbers are negative,
    2's complement works in such a way that the number with more 1's is < number with less 1's
    if(((int32_t)bits1) < ((int32_t)bits2)) {
        return 1;
    } else {
        return 0;
    }

*/
    // If either input is NaN, return 0
    if (is_nan(f1) == 1 || is_nan(f2) == 1) {
        return 0;
    }

    // Consider the 0, -0 input case
    if (is_zero(f1) == 1 && is_zero(f2) == 1) {
        return 0;
    }

    if (f1.sign == 1 && f2.sign == 0) {
        return 1;
    } else if (f1.sign == 0 && f2.sign == 1) {
        return 0;
    } else if (f1.sign == 0 && f2.sign == 0) {
        if (f1.exponent < f2.exponent) {
            return 1;
        } else if (f1.exponent > f2.exponent) {
            return 0;
        }
    // These cases will be reached only when both inputs have equal exponents
        if (f1.fraction < f2.fraction) {
            return 1;
        } else {
            return 0;
        }
    } else {
    // When both inputs are negative, the one with the larger magnitude is smaller
        if (f1.exponent > f2.exponent) {
            return 1;
        } else if (f1.exponent < f2.exponent) {
            return 0;
        }
        // These cases will be reached only when both inputs have equal exponents
        if (f1.fraction > f2.fraction) {
            return 1;
        } else {
            return 0;
        }
    }
}


