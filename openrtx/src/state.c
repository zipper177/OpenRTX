/***************************************************************************
 *   Copyright (C) 2020 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN,                            *
 *                         Frederik Saraci IU2NRO,                         *
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

#include <stdio.h>
#include <state.h>
#include <battery.h>
#include <hwconfig.h>
#include <interfaces/platform.h>

state_t state;

void state_init()
{
    /*
     * TODO: Read current state parameters from hardware, 
     * or initialize them to sane defaults
     */
    state.radioStateUpdated = true;
#ifdef HAS_RTC
    state.time = rtc_getTime();
#endif
    state.v_bat = platform_getVbat();
    state.charge = battery_getCharge(state.v_bat);
    state.rssi = rtx_getRssi();

    state.channelInfoUpdated = true;
    state.channel.mode = FM;
    state.channel.bandwidth = BW_25;
    state.channel.power = 1.0;
    state.channel.rx_frequency = 430000000;
    state.channel.tx_frequency = 430000000;
    state.channel.fm.rxToneEn = 0;
    state.channel.fm.rxTone = 2; // 71.9Hz
    state.channel.fm.txToneEn = 1;
    state.channel.fm.txTone = 2; // 71.9Hz

    state.rtxStatus = RTX_OFF;
#ifdef HAS_ABSOLUTE_KNOB // If the radio has an absolute position knob
    state.sqlLevel = platform_getChSelector() - 1;
#else
    state.sqlLevel = 3;
#endif
    state.voxLevel = 0;

    state.emergency = false;
}
