/*
 * Copyright (c) 2019 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

struct sbiret {
    long error;
    long value;
};

struct sbiret sbi_get_spec_version(void);
void sbi_set_timer(uint64_t stime_value);


