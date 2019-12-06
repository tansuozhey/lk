/*
 * Copyright (c) 2019 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <lk/reg.h>
#include <lk/debug.h>
#include <lk/trace.h>
#include <lk/err.h>
#include <platform.h>
#include <arch/riscv.h>
#include <arch/riscv/sbi.h>

#define sbi_call(arg0, arg1, arg2, arg3, func, extension, ret0, ret1) \
    register unsigned long a0 asm("a0") = arg0; \
    register unsigned long a1 asm("a1") = arg1; \
    register unsigned long a2 asm("a2") = arg2; \
    register unsigned long a3 asm("a3") = arg3; \
    register unsigned long a6 asm("a6") = func; \
    register unsigned long a7 asm("a7") = extension; \
    __asm__ volatile( \
            "ecall" \
            : "+r"(a0), "+r"(a1)\
            : "r"(a2), "r"(a3), "r"(a6), "r"(a7) \
            : "memory" ); \
    ret0 = a0; \
    ret1 = a1;

// new sbi 0.2 spec
struct sbiret sbi_get_spec_version(void) {
    ulong ret0, ret1;
    sbi_call(0, 0, 0, 0, 0, 0x10, ret0, ret1);

    return (struct sbiret){ ret0, ret1 };
}

void sbi_set_timer(uint64_t stime_value) {
    __UNUSED ulong temp, temp1;
    sbi_call(stime_value, 0, 0, 0, 0, 0, temp, temp1);
}
