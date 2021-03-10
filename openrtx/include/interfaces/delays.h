/***************************************************************************
 *   Copyright (C) 2020 by Silvano Seva IU2KWO and Niccolò Izzo IU2KIN     *
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

#ifndef DELAYS_H
#define DELAYS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function prototypes for microsecond and millisecond delays.
 * Their implementation is device-specific, thus it is placed inside the drivers
 * folder.
 */

/**
 * Exact microsecond delay.
 * @param useconds: delay value
 */
void delayUs(unsigned int useconds);

/**
 * Exact millisecond delay.
 * @param mseconds: delay value
 */
void delayMs(unsigned int mseconds);

/**
 * Puts the calling thread in a sleeping state for the specified amount of time.
 * @param seconds: sleep time, seconds.
 * @param mseconds: sleep time, milliseconds.
 */
void sleepFor(unsigned int seconds, unsigned int mseconds);

/**
 * Get the current value of the system tick.
 * @return current system tick value.
 */
long long getTick();

#ifdef __cplusplus
}
#endif

#endif /* DELAYS_H */
