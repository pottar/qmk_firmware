/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Pedro Castillo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This library is a modified version of the STM32 library under drivers/arm
 * to add support for the Kinetis processor in the K-Type keyboard.
 * This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 * Please ensure that HAL_USE_I2C is TRUE in the halconf.h file and that both
 * KINETIS_I2C_USE_I2C1 and KINETIS_I2C_USE_I2C2 are TRUE in the mcuconf.h file.
 */

#include "i2c_master.h"
// #include "quantum.h"
#include "ch.h"
#include <string.h>
#include <hal.h>

I2CHelper i2c_drivers[DRIVER_COUNT] = {
#if defined(KINETIS_I2C_USE_I2C0)
    { .driver = &I2CD1, .address = DRIVER_ADDR_1 },
#endif
#if defined(KINETIS_I2C_USE_I2C1)
    { .driver = &I2CD2, .address = DRIVER_ADDR_2 },
#endif
};

// static const I2CConfig i2cconfig = {
//     1000000,
// };

I2CHelper* get_helper(uint8_t drvid) {
    if (drvid < DRIVER_COUNT) {
        return &i2c_drivers[drvid];
    }
    return NULL;
}

static i2c_status_t chibios_to_qmk(const msg_t* status) {
    switch (*status) {
    case I2C_NO_ERROR:
        return I2C_STATUS_SUCCESS;
    case I2C_TIMEOUT:
        return I2C_STATUS_TIMEOUT;
    // I2C_BUS_ERROR, I2C_ARBITRATION_LOST, I2C_ACK_FAILURE, I2C_OVERRUN, I2C_PEC_ERROR, I2C_SMB_ALERT
    default:
        return I2C_STATUS_ERROR;
    }
}

__attribute__ ((weak))
void i2c_init(void)
{
    // Enable I2C internal clock for bus 0
    SIM->SCGC4 |= SIM_SCGC4_I2C0;

    // External pull-up resistor for bus 0
    PORTB->PCR[0] = PORTx_PCRn_ODE | PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(2);
    PORTB->PCR[1] = PORTx_PCRn_ODE | PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(2);

    // I2C speed for bus 0
    I2C0->F = 0x40;
    I2C0->FLT = 0x02;
    I2C0->C1 = I2Cx_C1_IICEN;
    I2C0->C2 = I2Cx_C2_HDRS;

    // Enable I2C interrupt and set priority for bus 0
    NVIC_EnableIRQ(I2C0_IRQn);
    NVIC_SetPriority(PITChannel0_IRQn, 150);

    // Enable I2C internal clock for bus 1
    SIM->SCGC4 |= SIM_SCGC4_I2C1;

    // External pull-up resistor for bus 1
    PORTC->PCR[10] = PORTx_PCRn_ODE | PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(2);
    PORTC->PCR[11] = PORTx_PCRn_ODE | PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(2);

    // I2C speed for bus 1
    I2C1->F = 0x40;
    I2C1->FLT = 0x02;
    I2C1->C1 = I2Cx_C1_IICEN;
    I2C1->C2 = I2Cx_C2_HDRS;

    // Enable I2C interrupt and set priority for bus 1
    NVIC_EnableIRQ(I2C1_IRQn);
    NVIC_SetPriority(PITChannel1_IRQn, 150);

    // Up to this point, I2C is initialized, but now we need to initialize the
    // pin config for the ISSI chips. The code below does this but it was moved
    // to is31fl3733.c
    // // Hardware Shutdown pin B,16
    // GPIOB->PDDR |= (1 << 16);
    // PORTB->PCR[0] = PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    // GPIOB->PCOR |= (1 << 16);

    // // This is supposed to reset the I2C bus.
    // // IIRST pin A,5
    // GPIOA->PDDR |= (1 << 5);
    // PORTA->PCR[0] = PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(1);
    // GPIOA->PSOR |= (1 << 5);
    // chThdSleepMicroseconds(50);
    // GPIOA->PCOR |= (1 << 5);

    // // Zero out issi register pages...

    // // Hardware Shutdown pin B,16
    // GPIOB->PSOR |= (1 << 16);

    // Old stuff that was in the original file. Again i have no idea what it does.

    // Try releasing special pins for a short time
    // palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
    // palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);

    // chThdSleepMilliseconds(10);

    // palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
    // palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);

    //i2cInit(); //This is invoked by halInit() so no need to redo it.
}

i2c_status_t i2c_start(I2CHelper *i2c)
{
    // i2cStart(i2c->driver, &i2cconfig);
    i2cStart(i2c->driver, NULL);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_transmit(I2CHelper *i2c, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    // i2cStart(i2c->driver, &i2cconfig);
    i2cStart(i2c->driver, NULL);
    msg_t status = i2cMasterTransmitTimeout(
        i2c->driver,
        (i2c->address >> 1),
        data,
        length,
        0,
        0,
        MS2ST(timeout)
    );
    return chibios_to_qmk(&status);
}

i2c_status_t i2c_receive(I2CHelper *i2c, uint8_t* data, uint16_t length, uint16_t timeout)
{
    // i2cStart(i2c->driver, &i2cconfig);
    i2cStart(i2c->driver, NULL);
    msg_t status = i2cMasterReceiveTimeout(
        i2c->driver,
        (i2c->address >> 1),
        data,
        length,
        MS2ST(timeout)
    );
    return chibios_to_qmk(&status);
}

i2c_status_t i2c_writeReg(I2CHelper *i2c, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    uint8_t complete_packet[length + 1];
    for(uint8_t i = 0; i < length; i++)
    {
        complete_packet[i+1] = data[i];
    }
    complete_packet[0] = regaddr;

    // i2cStart(i2c->driver, &i2cconfig);
    i2cStart(i2c->driver, NULL);
    msg_t status = i2cMasterTransmitTimeout(
        i2c->driver,
        (i2c->address >> 1),
        complete_packet,
        length + 1,
        0,
        0,
        MS2ST(timeout)
    );
    return chibios_to_qmk(&status);
}

i2c_status_t i2c_readReg(I2CHelper *i2c, uint8_t* regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
    // i2cStart(i2c->driver, &i2cconfig);
    i2cStart(i2c->driver, NULL);
    msg_t status = i2cMasterTransmitTimeout(
        i2c->driver,
        (i2c->address >> 1),
        regaddr,
        1,
        data,
        length,
        MS2ST(timeout)
    );
    return chibios_to_qmk(&status);
}

void i2c_stop(I2CHelper *i2c)
{
    i2cStop(i2c->driver);
}
