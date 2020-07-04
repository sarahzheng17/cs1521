// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define EXP_2048 11
#define EXP_SHIFT 23
#define EXP_PLUS_SIGN 9
#define EIGHT_BIT_MAX 255
#define BITS_32 32

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {

    // PUT YOUR CODE HERE
    // Sign does not change when multipling 2048
    // 2048 = 2^11. Therefore, fraction does not change
    // exp = exp + 11;
    
    // Note: since f is unsigned int, C will perform logical shift using << and >>

    uint32_t sign = f >> (BITS_32 - 1);
    uint32_t exp = (f << 1) >> (EXP_SHIFT + 1);
    uint32_t frac = (f << EXP_PLUS_SIGN) >> EXP_PLUS_SIGN;

    uint32_t p_inf = (uint32_t)0 | (0xFF << EXP_SHIFT);
    uint32_t n_inf = (uint32_t)0 | (0xFF << EXP_SHIFT);
    n_inf = n_inf | (((uint32_t)1) << (BITS_32 - 1));
    
    // 1) If INPUT is 'special case'
    if (exp == 0xFF) {
    // NaN or +/-inf
        return f;
    } else if (exp == 0 && frac == 0) {
    // +/- 0. Can assume non-normalised numbers, but just to be safe using frac == 0
        return f;
    }
    
    // 2) If RESULT WILL BE 'special case' i.e. +/-inf
    if (sign == 0 && (exp > EIGHT_BIT_MAX - EXP_2048)) {
        return p_inf;
    } else if (sign == 1 && (exp > EIGHT_BIT_MAX - EXP_2048)) {
        return n_inf;
    }

    // 3) Normal calculation case
    return f + (EXP_2048 << EXP_SHIFT);
}