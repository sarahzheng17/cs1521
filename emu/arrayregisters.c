////////////////////////////////////////////////////////////////////////
// COMP1521 19t3 ... assignment 1: emu -- a MIPS emulator
//
// 2019-10-15   v1.0    emu squad <cs1521@cse.unsw.edu.au>
//     Initial release onto unsuspecting students.
//
// // // // // // // DO NOT MODIFY THIS FILE! // // // // // // // // //

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "registers.h"

const char *const register_name_map[] = {
    [zero] = "$zero",
    [at] = "$at",
    [v0] = "$v0",
    [v1] = "$v1",
    [a0] = "$a0",
    [a1] = "$a1",
    [a2] = "$a2",
    [a3] = "$a3",
    [t0] = "$t0",
    [t1] = "$t1",
    [t2] = "$t2",
    [t3] = "$t3",
    [t4] = "$t4",
    [t5] = "$t5",
    [t6] = "$t6",
    [t7] = "$t7",
    [s0] = "$s0",
    [s1] = "$s1",
    [s2] = "$s2",
    [s3] = "$s3",
    [s4] = "$s4",
    [s5] = "$s5",
    [s6] = "$s6",
    [s7] = "$s7",
    [t8] = "$t8",
    [t9] = "$t9",
    [k0] = "$k0",
    [k1] = "$k1",
    [gp] = "$gp",
    [sp] = "$sp",
    [fp] = "$fp",
    [ra] = "$ra",
};

static uint32_t registers[N_REGISTERS] = {0};

uint32_t get_register(register_type register_number)
{
    assert(register_number >= 0 && register_number < N_REGISTERS);
    return registers[register_number];
}

void set_register(register_type register_number, uint32_t value)
{
    assert(register_number >= 0 && register_number < N_REGISTERS);
    if (register_number != zero)
    {
        registers[register_number] = value;
    }
}

void print_registers(void)
{
    for (int r = 0; r < N_REGISTERS; r++)
    {
        printf("R%-2d [%s] = %08X\n", r, register_name_map[r], registers[r]);
    }
}
