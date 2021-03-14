/***************************************************************************
 *   Copyright (C) 2020 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include "AT24Cx.h"
#include <interfaces/gpio.h>
#include <interfaces/delays.h>
#include <hwconfig.h>
#include <stdint.h>
#include <I2C0.h>

static const uint8_t devAddr = 0xA0;    /* EEPROM I2C address */

void AT24Cx_init()
{
    /*
     * Nothing to do here, on GDx devices the I2C bus is initialised in
     * platform_init() before starting all the other modules.
     */
}

void AT24Cx_terminate()
{

}

void AT24Cx_readData(uint32_t addr, void* buf, size_t len)
{
    uint16_t a = __builtin_bswap16((uint16_t) addr);

    /*
     * On GDx devices the I2C bus is shared between the EEPROM and the AT1846S,
     * so we have to acquire exclusive ownership before exchanging data
     */
    i2c0_lockDeviceBlocking();

    i2c0_write(devAddr, &a, 2, false);
    delayUs(10);
    i2c0_read(devAddr, buf, len);

    i2c0_releaseDevice();
}
