/***************************************************************************
 *   Copyright (C) 2020 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN,                            *
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

#include <calibUtils.h>

uint8_t interpCalParameter(const freq_t freq, const freq_t *calPoints,
                           const uint8_t *param, const uint8_t elems)
{

    if(freq <= calPoints[0])         return param[0];
    if(freq >= calPoints[elems - 1]) return param[elems - 1];

    /* Find calibration point nearest to target frequency */
    uint8_t pos = 0;
    for(; pos < elems; pos++)
    {
        if(calPoints[pos] >= freq) break;
    }

    uint8_t interpValue = 0;
    freq_t  delta = calPoints[pos] - calPoints[pos - 1];

    if(param[pos - 1] < param[pos])
    {
        interpValue = param[pos - 1] + ((freq - calPoints[pos - 1]) *
                                        (param[pos] - param[pos - 1]))/delta;
    }
    else
    {
        interpValue = param[pos - 1] - ((freq - calPoints[pos - 1]) *
                                       (param[pos - 1] - param[pos]))/delta;
    }

    return interpValue;
}
