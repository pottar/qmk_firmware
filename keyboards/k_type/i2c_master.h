/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 *
 * This program is free sofare: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Sofare Foundation, either version 2 of the License, or
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

#include "ch.h"
#include <hal.h>

struct I2CHelper {
    I2CDriver *driver;
    uint8_t address;
};
typedef struct I2CHelper I2CHelper;

I2CHelper* get_helper(uint8_t idx);

#ifdef I2C1_BANK
    #define I2C1_SCL_BANK I2C1_BANK
    #define I2C1_SDA_BANK I2C1_BANK
#endif

#ifndef I2C1_SCL_BANK
    #define I2C1_SCL_BANK GPIOB
#endif

#ifndef I2C1_SDA_BANK
    #define I2C1_SDA_BANK GPIOB
#endif

#ifndef I2C1_SCL
    #define I2C1_SCL 6
#endif
#ifndef I2C1_SDA
    #define I2C1_SDA 7
#endif

// The default PAL alternate modes are used to signal that the pins are used for I2C
#ifndef I2C1_SCL_PAL_MODE
    #define I2C1_SCL_PAL_MODE 4
#endif
#ifndef I2C1_SDA_PAL_MODE
    #define I2C1_SDA_PAL_MODE 4
#endif

// The default timing values below configures the I2C clock to 400khz assuming a 72Mhz clock
// For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
#ifndef I2C1_TIMINGR_PRESC
    #define I2C1_TIMINGR_PRESC 15U
#endif
#ifndef I2C1_TIMINGR_SCLDEL
    #define I2C1_TIMINGR_SCLDEL 4U
#endif
#ifndef I2C1_TIMINGR_SDADEL
    #define I2C1_TIMINGR_SDADEL 2U
#endif
#ifndef I2C1_TIMINGR_SCLH
    #define I2C1_TIMINGR_SCLH 15U
#endif
#ifndef I2C1_TIMINGR_SCLL
    #define I2C1_TIMINGR_SCLL 21U
#endif

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR   (-1)
#define I2C_STATUS_TIMEOUT (-2)

void i2c_init(void);
i2c_status_t i2c_start(I2CHelper *i2c);
i2c_status_t i2c_transmit(I2CHelper *i2c, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_receive(I2CHelper *i2c, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_transmit_receive(I2CHelper *i2c, uint8_t * tx_body, uint16_t tx_length, uint8_t * rx_body, uint16_t rx_length);
i2c_status_t i2c_writeReg(I2CHelper *i2c, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_readReg(I2CHelper *i2c, uint8_t* regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
void i2c_stop(I2CHelper *i2c);
