/*
 * config.h
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-Beacon.
 * 
 * FloripaSat-Beacon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-Beacon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-Beacon. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief General configuration definitions.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 08/06/2017
 * 
 * \defgroup config Configuration
 * \{
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <drivers/driverlib/driverlib.h>

#include "modes.h"
#include "pinmap.h"
#include "hardware.h"

//########################################################
//-- SATELLITE DATA --------------------------------------
//########################################################

#define SATELLITE_ID                        "FLORIPASAT"

#define SATELLITE_ENERGY_LEVEL_1            0
#define SATELLITE_ENERGY_LEVEL_2            1
#define SATELLITE_ENERGY_LEVEL_3            2
#define SATELLITE_ENERGY_LEVEL_4            3
#define SATELLITE_ENERGY_LEVEL_5            4

//########################################################
//-- BEACON OPERATION ------------------------------------
//########################################################

#define BEACON_MODE                         TEST_MODE

#define BEACON_TX_PERIOD_SEC_L1             10
#define BEACON_TX_PERIOD_SEC_L2             10
#define BEACON_TX_PERIOD_SEC_L3             20
#define BEACON_TX_PERIOD_SEC_L4             30
#define BEACON_TX_PERIOD_SEC_L5             30

#define BEACON_HIBERNATION_PERIOD_SECONDS   (24*60*60*1UL)
#define BEACON_HIBERNATION_PERIOD_MINUTES   (24*60)
#define BEACON_HIBERNATION_PERIOD_HOURS     24

#define BEACON_ANTENNA_DEPLOY_SLEEP_SEC     (45*60)
#define BEACON_ANTENNA_DEPLOY_SLEEP_MIN     45
#define BEACON_ANTENNA_DEPLOY_SLEEP_HOUR    0

#define BEACON_RADIO_RESET_PERIOD_MIN       10
#define BEACON_RADIO_RESET_PERIOD_SEC       (BEACON_RADIO_RESET_PERIOD_MIN*60*1UL)

#define BEACON_SYSTEM_RESET_PERIOD_HOURS    12
#define BEACON_SYSTEM_RESET_PERIOD_MIN      (BEACON_SYSTEM_RESET_PERIOD_HOURS*60)
#define BEACON_SYSTEM_RESET_PERIOD_SEC      (BEACON_SYSTEM_RESET_PERIOD_MIN*60*1UL)

#define BEACON_TIMEOUT_RADIO_SHUTDOWN       1000000UL

#define BEACON_BOOT_DELAY_SEC               2
#define BEACON_BOOT_DELAY_MS                (BEACON_BOOT_DELAY_SEC*1000)

//########################################################
//-- BEACON PACKETS --------------------------------------
//########################################################

#define BEACON_PACKET_PAYLOAD_CONTENT       (PAYLOAD_SAT_ID | PAYLOAD_OBDH_DATA | PAYLOAD_EPS_DATA)

#define BEACON_PACKET_PROTOCOL              (PACKET_NGHAM | PACKET_AX25)

//########################################################
//-- RADIO -----------------------------------------------
//########################################################

#define BEACON_RADIO                        RF4463F30
#define BEACON_RADIO_SPI_CLK                100000

#define RADIO_INIT_TIMEOUT_MS               100

//########################################################
//-- RADIO SIM -------------------------------------------
//########################################################

#define RADIO_SIM_UART_CLOCK_SOURCE         USCI_A_UART_CLOCKSOURCE_SMCLK
#define RADIO_SIM_UART_CLOCK_PRESCALAR      208
#define RADIO_SIM_UART_FIRST_MOD_REG        5
#define RADIO_SIM_UART_SECOND_MOD_REG       0
#define RADIO_SIM_UART_PARITY               USCI_A_UART_NO_PARITY
#define RADIO_SIM_UART_ENDIENESS            USCI_A_UART_LSB_FIRST
#define RADIO_SIM_UART_STOP_BITS            USCI_A_UART_ONE_STOP_BIT
#define RADIO_SIM_UART_MODE                 USCI_A_UART_MODE
#define RADIO_SIM_UART_OVERSAMPLING         USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

//########################################################
//-- PA --------------------------------------------------
//########################################################

#define BEACON_PA                           HW_NONE

#define BEACON_PA_VREF                      3.3

#define BEACON_PA_DAC_BASE_ADDRESS          DAC12_A_BASE
#define BEACON_PA_DAC_SUBMODULE             DAC12_A_SUBMODULE_0

#define BEACON_PA_INIT_TIMEOUT_MS           100

//########################################################
//-- RF SWITCH -------------------------------------------
//########################################################

#define BEACON_RF_SWITCH                    HW_NONE

//########################################################
//-- ANTENNA ---------------------------------------------
//########################################################

#define BEACON_ANTENNA                      PASSIVE_ANTENNA
#define BEACON_ANTENNA_I2C_CLK              100000

#define BEACON_ANTENNA_INIT_TIMEOUT_MS      100

//########################################################
//-- CPU -------------------------------------------------
//########################################################

#define BEACON_CPU_FREQ_HZ                  16000000UL
#define BEACON_CPU_FREQ_KHZ                 (BEACON_CPU_FREQ_HZ/1000)
#define BEACON_CPU_FREQ_MHZ                 (BEACON_CPU_FREQ_HZ/1000000)

//########################################################
//-- WATCHDOG --------------------------------------------
//########################################################

#define WATCHDOG_BASE_ADDRESS               WDT_A_BASE
#define WATCHDOG_CLK_SOURCE                 WDT_A_CLOCKSOURCE_ACLK
#define WATCHDOG_CLK_DIVIDER                WDT_A_CLOCKDIVIDER_512K  // 16 seconds WDT

//########################################################
//-- TIME ------------------------------------------------
//########################################################

#define TIME_TIMER_BASE_ADDRESS             TIMER_A1_BASE
#define TIME_TIMER_VECTOR                   TIMER1_A0_VECTOR

#define TIME_TIMER_CLOCK_SOURCE             TIMER_A_CLOCKSOURCE_SMCLK
#define TIME_TIMER_CLOCK_SOURCE_DIVIDER     TIMER_A_CLOCKSOURCE_DIVIDER_64
#define TIME_TIMER_INTERRUPT_ENABLE_TAIE    TIMER_A_TAIE_INTERRUPT_DISABLE
#define TIME_TIMER_CLEAR                    TIMER_A_DO_CLEAR

#define TIME_TIMER_COMPARE_MODE             TIMER_A_CAPTURECOMPARE_REGISTER_0
#define TIME_TIMER_COMPARE_REGISTER         TIMER_A_CAPTURECOMPARE_REGISTER_0
#define TIME_TIMER_COMPARE_INTERRUPT_ENABLE TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE
#define TIME_TIMER_COMPARE_OUTPUT_MODE      TIMER_A_OUTPUTMODE_OUTBITVALUE
#define TIME_TIMER_COMPARE_DIVIDER_VALUE    64

#define TIME_TIMER_MODE                     TIMER_A_CONTINUOUS_MODE

//########################################################
//-- OBDH ------------------------------------------------
//########################################################

#define OBDH_TIMEOUT                        1000000UL
#define OBDH_TIMEOUT_SEC                    60
#define OBDH_TIMEOUT_MIN                    1

#define OBDH_INIT_TIMEOUT_MS                100

#define OBDH_RADIO_TIMEOUT_SEC              2

#define OBDH_PKT_ENERGY_LEVEL_POS           30

//########################################################
//-- EPS -------------------------------------------------
//########################################################

#define EPS_TIMEOUT                         1000000UL
#define EPS_TIMEOUT_SEC                     60
#define EPS_TIMEOUT_MIN                     1

#define EPS_INIT_TIMEOUT_MS                 100

#define EPS_PKT_ENERGY_LEVEL_POS            30

//########################################################
//-- LOW-POWER MODE --------------------------------------
//########################################################

#define LOW_POWER_MODE_ON                   (LPM1_bits + GIE)
#define LOW_POWER_MODE_OFF                  LPM1_EXIT

//########################################################
//-- DEBUG -----------------------------------------------
//########################################################

#define SYS_DEBUG_UART_CLOCK_SOURCE         USCI_A_UART_CLOCKSOURCE_SMCLK
#define SYS_DEBUG_UART_CLOCK_PRESCALAR      2
#define SYS_DEBUG_UART_FIRST_MOD_REG        2
#define SYS_DEBUG_UART_SECONDS_MOD_REG      3
#define SYS_DEBUG_UART_PARITY               USCI_A_UART_NO_PARITY
#define SYS_DEBUG_UART_ENDIANESS            USCI_A_UART_LSB_FIRST
#define SYS_DEBUG_UART_STOP_BITS            USCI_A_UART_ONE_STOP_BIT
#define SYS_DEBUG_UART_MODE                 USCI_A_UART_MODE
#define SYS_DEBUG_UART_OVER_SAMPLING        USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

#define DEBUG_INIT_TIMEOUT_MS               100

#endif // CONFIG_H_

//! \} End of config group