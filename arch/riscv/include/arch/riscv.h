/*
 * Copyright (c) 2015 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

// status register (machine and supervisor)
#define RISCV_STATUS_UIE        (1u << 0)
#define RISCV_STATUS_SIE        (1u << 1)
#define RISCV_STATUS_MIE        (1u << 3)
#define RISCV_STATUS_UPIE       (1u << 4)
#define RISCV_STATUS_SPIE       (1u << 5)
#define RISCV_STATUS_MPIE       (1u << 7)
#define RISCV_STATUS_SPP        (1u << 8)
#define RISCV_STATUS_MPP_MASK   (3u << 11)

// interrupt enable reigster (machine and supervisor)
#define RISCV_IE_USIE          (1u << 0)
#define RISCV_IE_SSIE          (1u << 1)
#define RISCV_IE_MSIE          (1u << 3)
#define RISCV_IE_UTIE          (1u << 4)
#define RISCV_IE_STIE          (1u << 5)
#define RISCV_IE_MTIE          (1u << 7)
#define RISCV_IE_SEIE          (1u << 9)
#define RISCV_IE_MEIE          (1u << 11)

// interrupt pending register (machine and supervisor)
#define RISCV_IP_USIP          (1u << 0)
#define RISCV_IP_SSIP          (1u << 1)
#define RISCV_IP_MSIP          (1u << 3)
#define RISCV_IP_UTIP          (1u << 4)
#define RISCV_IP_STIP          (1u << 5)
#define RISCV_IP_MTIP          (1u << 7)
#define RISCV_IP_UEIP          (1u << 8)
#define RISCV_IP_SEIP          (1u << 9)
#define RISCV_IP_MEIP          (1u << 11)

#define RISCV_CAUSE_INT        (1u << 31)

// some logic to append a s or a m to the register name depending on
// which mode the kernel is being compiled in.
#if ARCH_RISCV_SUPERVISOR_MODE
#define RISCV_REG(reg) "s" #reg
#elif ARCH_RISCV_MACHINE_MODE
#define RISCV_REG(reg) "m" #reg
#else
#error need to define machine or supervisor mode
#endif

#define riscv_csr_clear(csr, bits) \
({ \
    ulong __val = bits; \
    __asm__ volatile( \
        "csrc   " csr ", %0" \
        :: "rK" (__val) \
        : "memory"); \
})

#define riscv_csr_read_clear(csr, bits) \
({ \
    ulong __val = bits; \
    ulong __val_out; \
    __asm__ volatile( \
        "csrrc   %0, " csr ", %1" \
        : "=r"(__val_out) \
        : "rK" (__val) \
        : "memory"); \
    __val_out; \
})

#define riscv_csr_set(csr, bits) \
({ \
    ulong __val = bits; \
    __asm__ volatile( \
        "csrs   " csr ", %0" \
        :: "rK" (__val) \
        : "memory"); \
})

#define riscv_csr_read(csr) \
({ \
    ulong __val; \
    __asm__ volatile( \
        "csrr   %0, " csr \
        : "=r" (__val) \
        :: "memory"); \
    __val; \
})

#define riscv_csr_write(csr, val) \
({ \
    ulong __val = (ulong)val; \
    __asm__ volatile( \
        "csrw   " csr ", %0" \
        :: "rK" (__val) \
        : "memory"); \
    __val; \
})

void riscv_exception_entry(void);
enum handler_return riscv_timer_exception(void);
