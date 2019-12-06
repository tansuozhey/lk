/*
 * Copyright (c) 2015 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <assert.h>
#include <lk/trace.h>
#include <lk/debug.h>
#include <stdint.h>
#include <arch/riscv.h>
#include <arch/ops.h>
#include <lib/console.h>

#define LOCAL_TRACE 0

void arch_early_init(void) {
    // set the top level exception handler
    riscv_csr_write(RISCV_REG(tvec), (uintptr_t)&riscv_exception_entry);

    // mask all exceptions, just in case
    riscv_csr_clear(RISCV_REG(status), RISCV_STATUS_MIE | RISCV_STATUS_SIE);
    riscv_csr_clear(RISCV_REG(ie), RISCV_IE_MTIE | RISCV_IE_MSIE | RISCV_IE_SEIE | RISCV_IE_MEIE);

    // enable cycle counter (disabled for now, unimplemented on sifive-e)
    //riscv_csr_set(mcounteren, 1);
}

void arch_init(void) {
#if 0
    // print some arch info
    dprintf(INFO, "RISCV: mvendorid %#lx marchid %#lx mimpid %#lx mhartid %#lx\n",
            riscv_csr_read(mvendorid), riscv_csr_read(marchid),
            riscv_csr_read(mimpid), riscv_csr_read(mhartid));
    dprintf(INFO, "RISCV: misa %#lx\n", riscv_csr_read(misa));
#endif

    // enable external interrupts
#if ARCH_RISCV_MACHINE_MODE
    riscv_csr_set(RISCV_REG(ie), RISCV_IE_MEIE);
#else
    riscv_csr_set(RISCV_REG(ie), RISCV_IE_SEIE);
#endif

    //for (;;) {
    //    printf("%ld\n", riscv_csr_read("time"));
    //}

    //console_run_script("threadload");
}

void arch_idle(void) {
    // disabled for now, QEMU seems to have some trouble emulating wfi properly
    // also have trouble breaking into sifive-e board with openocd when wfi
    // NOTE: reenabling for now, will need to re-test on sifive board to see if this
    // problem went away.
    //__asm__ volatile("wfi");
}

void arch_chain_load(void *entry, ulong arg0, ulong arg1, ulong arg2, ulong arg3) {
    PANIC_UNIMPLEMENTED;
}

/* unimplemented cache operations */
void arch_disable_cache(uint flags) { PANIC_UNIMPLEMENTED; }
void arch_enable_cache(uint flags) { PANIC_UNIMPLEMENTED; }

void arch_clean_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_clean_invalidate_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_invalidate_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_sync_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
