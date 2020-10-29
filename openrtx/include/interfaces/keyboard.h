/***************************************************************************
 *   Copyright (C) 2020 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

/**
 * The following enum provides a set of flags to be used to check whose buttons
 * are pressed by bit-masking the uint32_t value returned by kbd_getKeys().
 */
enum keys
{
    KEY_0     = (1 << 0),   /* Keypad digit "0"                  */
    KEY_1     = (1 << 1),   /* Keypad digit "1"                  */
    KEY_2     = (1 << 2),   /* Keypad digit "2"                  */
    KEY_3     = (1 << 3),   /* Keypad digit "3"                  */
    KEY_4     = (1 << 4),   /* Keypad digit "4"                  */
    KEY_5     = (1 << 5),   /* Keypad digit "5"                  */
    KEY_6     = (1 << 6),   /* Keypad digit "6"                  */
    KEY_7     = (1 << 7),   /* Keypad digit "7"                  */
    KEY_8     = (1 << 8),   /* Keypad digit "8"                  */
    KEY_9     = (1 << 9),   /* Keypad digit "9"                  */
    KEY_STAR  = (1 << 10),  /* Keypad digit "*"                  */
    KEY_HASH  = (1 << 11),  /* Keypad digit "#"                  */
    KEY_ENTER = (1 << 12),  /* Keypad green button/enter         */
    KEY_ESC   = (1 << 13),  /* Keypad red button/esc             */
    KEY_UP    = (1 << 14),  /* Keypad upward arrow               */
    KEY_DOWN  = (1 << 15),  /* Keypad downward arrow             */
    KEY_LEFT  = (1 << 16),  /* Keypad leftward arrow             */
    KEY_RIGHT = (1 << 17),  /* Keypad rightward arrow            */
    KEY_MONI  = (1 << 18),  /* Monitor button                    */
    KEY_F1    = (1 << 19),  /* Function button                   */
    KEY_F2    = (1 << 20),  /* Function button (device specific) */
    KEY_F3    = (1 << 21),  /* Function button (device specific) */
    KEY_F4    = (1 << 22),  /* Function button (device specific) */
    KEY_F5    = (1 << 23),  /* Function button (device specific) */
    KEY_F6    = (1 << 24),  /* Function button (device specific) */
    KEY_F7    = (1 << 25),  /* Function button (device specific) */
    KEY_F8    = (1 << 26),  /* Function button (device specific) */
    KEY_F9    = (1 << 27),  /* Function button (device specific) */
    KEY_F10   = (1 << 28),  /* Function button (device specific) */
    KEY_F11   = (1 << 29),  /* Function button (device specific) */
    KEY_F12   = (1 << 30),  /* Function button (device specific) */
    KEY_F13   = (1 << 31)   /* Function button (device specific) */
};

/**
 * This function initialises the keyboard subsystem, configuring the GPIOs as
 * needed.
 */
void kbd_init();

/**
 * When called, this function terminates the keyboard driver.
 */
void kbd_terminate();

/**
 * When called, this function takes a snapshot of the current configuration of
 * all the keyboard buttons and returns it as a 32-bit variable.
 * 
 * @return an uint32_t representing the current keyboard configuration.
 */
uint32_t kbd_getKeys();

#endif /* KEYBOARD_H */