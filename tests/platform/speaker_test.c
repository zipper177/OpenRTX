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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <interfaces/gpio.h>
#include <interfaces/delays.h>
#include <interfaces/platform.h>
#include <rtx.h>
#include <hwconfig.h>

extern int16_t m17_buf[];
// extern size_t nSamples;

int main(void)
{
    platform_init();

    /* AF2 is TIM3 channel 3 */
    gpio_setMode(BEEP_OUT, ALTERNATE);
    gpio_setAlternateFunction(BEEP_OUT, 2);


    /*
     * Prepare buffer for 8-bit waveform samples
     */
    size_t nSamples = 60*1024;
    uint16_t *buf = ((uint16_t *) malloc(nSamples * sizeof(uint16_t)));

    if(buf == NULL)
    {
        platform_ledOn(RED);
        while(1) ;
    }

    for(size_t i = 0; i < nSamples; i++)
    {
        int16_t sample = 32768 - m17_buf[i];
        buf[i] = ((uint16_t) sample) >> 8;
    }

    /*
     * Enable peripherals
     */
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN
                 |  RCC_APB1ENR_TIM7EN;
    __DSB();

    /*
     * PWM for tone generator time base: 328kHz
     */
    TIM3->ARR   = 0xFF;
    TIM3->PSC   = 0;
    TIM3->CCMR2 = TIM_CCMR2_OC3M_2
                | TIM_CCMR2_OC3M_1
                | TIM_CCMR2_OC3PE;
    TIM3->CR1  |= TIM_CR1_ARPE;

    TIM3->CCER |= TIM_CCER_CC3E;
    TIM3->CR1  |= TIM_CR1_CEN;

    /*
     * Timebase for 48kHz sample rate
     */
    TIM7->CNT  = 0;
    TIM7->PSC  = 0;
    TIM7->ARR  = 1749;//(84000000/48000) - 1;
    TIM7->EGR  = TIM_EGR_UG;
    TIM7->DIER = TIM_DIER_UDE;
    TIM7->CR1  = TIM_CR1_CEN;

    /*
     * DMA stream for sample transfer
     */
    DMA1_Stream2->NDTR = nSamples;
    DMA1_Stream2->PAR  = ((uint32_t) &(TIM3->CCR3));
    DMA1_Stream2->M0AR = ((uint32_t) buf);
    DMA1_Stream2->CR = DMA_SxCR_CHSEL_0       /* Channel 1                   */
                     | DMA_SxCR_PL            /* Very high priority          */
                     | DMA_SxCR_MSIZE_0
                     | DMA_SxCR_PSIZE_0
                     | DMA_SxCR_MINC          /* Increment source pointer    */
                     | DMA_SxCR_CIRC          /* Circular mode               */
                     | DMA_SxCR_DIR_0         /* Memory to peripheral        */
                     | DMA_SxCR_EN;           /* Start transfer              */


    /* Turn on audio amplifier and unmute speaker */
    gpio_setMode(AUDIO_AMP_EN, OUTPUT);
    gpio_setMode(SPK_MUTE,     OUTPUT);

    gpio_setPin(AUDIO_AMP_EN);
    delayMs(10);
    gpio_clearPin(SPK_MUTE);

    while(1)
    {
        platform_ledOn(GREEN);
        delayMs(300);
        platform_ledOff(GREEN);
        delayMs(300);
    }

    return 0;
}
