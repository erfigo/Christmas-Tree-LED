/* --COPYRIGHT--,BSD
 * Copyright (c) 2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//***************************************************************************************
//  Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 inside of a software loop using DriverLib.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP4302355
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  E. Chen
//  Texas Instruments, Inc
//  May 2018
//  Built with Code Composer Studio v8
//***************************************************************************************
#include <msp430.h>
#include <driverlib.h>
#define NUM_PINS 8
unsigned int pins[NUM_PINS] = {BIT3, BIT5, BIT6, BIT7, BIT4, BIT6, BIT5, BIT2};
unsigned int *ports[NUM_PINS] = {&P1OUT, &P1OUT, &P1OUT, &P1OUT, &P3OUT, &P3OUT, &P4OUT, &P5OUT};

unsigned int lfsr = 0xACE1u;  // Any non-zero start state will work.
unsigned int bit;

int main(void) {
    WDTCTL = WDTPW |WDTHOLD;


    // Set P1.3, P1.5, P1.6, P1.7, P3.4, P3.6, P5.2, P4.5 as output direction
       P1DIR |= BIT3 | BIT5 | BIT6 | BIT7;
       P3DIR |= BIT4 | BIT6;
       P4DIR |= BIT5;
       P5DIR |= BIT2;

       // Set all pins as Low
       P1OUT &= ~(BIT3 | BIT5 | BIT6 | BIT7);
       P3OUT &= ~(BIT4 | BIT6);
       P4OUT &= ~BIT5;
       P5OUT &= ~BIT2;


    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();

    while(1)
        {
        __delay_cycles(100000); // Delay for a while



        __delay_cycles(100000); // Delay for a while

                // Generate a random number using LFSR
                bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
                lfsr =  (lfsr >> 1) | (bit << 15);

                // Use the random number to select a pin to toggle
                unsigned int pinIndex = lfsr % NUM_PINS;
                *(ports[pinIndex]) ^= pins[pinIndex];}
    return 0;
    }
