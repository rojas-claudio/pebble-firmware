/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef const struct QSPIFlashPart {
  struct {
    uint8_t fast_read;
    uint8_t fast_read_ddr;
    uint8_t page_program;
    uint8_t erase_sector_4k;
    uint8_t erase_block_64k;
    uint8_t write_enable;
    uint8_t write_disable;
    uint8_t read_status;
    uint8_t read_flag_status;
    uint8_t erase_suspend;
    uint8_t erase_resume;
    uint8_t enter_low_power;
    uint8_t exit_low_power;
    uint8_t enter_quad_mode;
    uint8_t exit_quad_mode;
    uint8_t reset_enable;
    uint8_t reset;
    uint8_t qspi_id;
    uint8_t block_lock;
    uint8_t block_lock_status;
    uint8_t block_unlock_all;
    uint8_t write_protection_enable;
    uint8_t read_protection_status;
  } instructions;
  struct {
    uint8_t busy;
    uint8_t write_enable;
  } status_bit_masks;
  struct {
    uint8_t erase_suspend;
  } flag_status_bit_masks;
  struct {
    uint8_t fast_read;
    uint8_t fast_read_ddr;
  } dummy_cycles;
  struct {
    bool has_lock_data; //<! true ifdata needs to be send along with the block_lock instruction
    uint8_t lock_data; //<! The data to be sent on a block_lock command, if has_lock_data is true
    uint8_t locked_check; //<! Value block_lock_status instruction should return if sector is locked
    uint8_t protection_enabled_mask; //<! Mask read_protection_status instr to check if enabled
  } block_lock;
  uint32_t reset_latency_ms;
  uint32_t suspend_to_read_latency_us;
  uint32_t standby_to_low_power_latency_us;
  uint32_t low_power_to_standby_latency_us;
  bool supports_fast_read_ddr;
  bool supports_block_lock;
  uint32_t qspi_id_value;
  const char *name;
} QSPIFlashPart;

