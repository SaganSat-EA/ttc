/*
 * obdh_hal.c
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
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
 * \file obdh_hal.c
 * 
 * \brief OBDH HAL functions.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/03/2017
 * 
 * \addtogroup obdh_hal
 * \{
 */

#include <stdbool.h>

#include <config/config.h>

#include "obdh_hal.h"
#include "obdh_hal_config.h"

Queue obdh_queue;

bool obdh_init()
{
#if BEACON_MODE == DEBUG_MODE
    debug_print_msg("OBDH communication initialization... ");
#endif // BEACON_MODE
    
    if (obdh_hal_spi_init() == true)
    {
        queue_init(&obdh_queue);
        
#if BEACON_MODE == DEBUG_MODE
        debug_print_msg("SUCCESS!\n");
#endif // BEACON_MODE
        
        return true;
    }
    else
    {
#if BEACON_MODE == DEBUG_MODE
        debug_print_msg("FAIL!\n");
#endif // BEACON_MODE
        
        return false;
    }
}

static bool obdh_hal_spi_init()
{
    // SPI pins init.
    GPIO_setAsPeripheralModuleFunctionInputPin(OBDH_SPI_PORT, OBDH_SPI_MOSI_PIN + OBDH_SPI_MISO_PIN + OBDH_SPI_SCLK_PIN + OBDH_SPI_NSEL_PIN);
    
    if (USCI_A_SPI_initSlave(OBDH_SPI_BASE_ADDRESS, USCI_A_SPI_MSB_FIRST,
                             USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
                             USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW) == STATUS_SUCCESS)
    {
        // Set SPI Mode 2 (The initSlave function from DriverLib, only initializes in Mode 0)
        HWREG8(OBDH_SPI_BASE_ADDRESS + OFS_UCAxCTL0) |= UCMODE_2;
        
        // Enable SPI Module
        USCI_A_SPI_enable(OBDH_SPI_BASE_ADDRESS);
        
        // Enable Receive interrupt
        USCI_A_SPI_clearInterrupt(OBDH_SPI_BASE_ADDRESS, USCI_A_SPI_RECEIVE_INTERRUPT);
        USCI_A_SPI_enableInterrupt(OBDH_SPI_BASE_ADDRESS, USCI_A_SPI_RECEIVE_INTERRUPT);
        
        return true;
    }
    else
    {
        return false;
    }
}

uint8_t obdh_available()
{
    return queue_size(&obdh_queue);
}

static void obdh_push(uint8_t byte)
{
    queue_push_back(&obdh_queue, byte);
}

uint8_t obdh_pop()
{
    return queue_pop_front(&obdh_queue);
}

void obdh_read(uint8_t *data, uint8_t bytes)
{
    uint8_t i = 0;
    for(i=0; i<bytes; i++)
    {
        data[i] = obdh_pop();
    }
}

void obdh_send(uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    for(i=0; i<len; i++)
    {
        // USCI_An TX buffer ready?
        while(!USCI_A_SPI_getInterruptStatus(OBDH_SPI_BASE_ADDRESS, USCI_A_SPI_TRANSMIT_INTERRUPT))
        {
            
        }
        
        // Transmit data to master
        USCI_A_SPI_transmitData(OBDH_SPI_BASE_ADDRESS, data[i]);
    }
}

void obdh_clear()
{
    while(obdh_available())
    {
        obdh_pop();
    }
}

/**
 * \fn USCI_A2_IST
 * 
 * \brief USCI_A2 interrupt vector service routine.
 * 
 * \return None
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A2_VECTOR)))
#endif
void USCI_A2_ISR()
{
    switch(__even_in_range(UCA2IV, 4))
    {
        //Vector 2 - RXIFG
        case 2:
            obdh_push(USCI_A_SPI_receiveData(OBDH_SPI_BASE_ADDRESS));
            break;
        default:
            break;
    }
}

//! \} End of obdh_com group