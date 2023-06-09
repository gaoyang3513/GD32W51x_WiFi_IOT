/*!
    \file    main.c
    \brief   HASH SHA1 DMA trustzone, non-secure code with TZEN = 1

    \version 2021-10-30, V1.0.0, firmware for GD32W51x
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32w51x.h"
#include "gd32w515p_eval.h"

__attribute__((aligned(4)))
static uint8_t message_input[] =
              {0x54,0x68,0x65,0x20,0x68,0x61,0x73,0x68,
               0x20,0x70,0x72,0x6f,0x63,0x65,0x73,0x73,
               0x6f,0x72,0x20,0x69,0x73,0x20,0x61,0x20,
               0x66,0x75,0x6c,0x6c,0x79,0x20,0x63,0x6f,
               0x6d,0x70,0x6c,0x69,0x61,0x6e,0x74,0x20,
               0x69,0x6d,0x70,0x6c,0x65,0x6d,0x65,0x6e,
               0x74,0x61,0x74,0x69,0x6f,0x6e,0x20,0x6f,
               0x66,0x20,0x74,0x68,0x65,0x20,0x73,0x65,
               0x63,0x75,0x72,0x65,0x20,0x68,0x61,0x73,
               0x68,0x20,0x61,0x6c,0x67,0x6f,0x72,0x69,
               0x74,0x68,0x6d,0x20,0x28,0x53,0x48,0x41,
               0x2d,0x31,0x29,0x2c,0x20,0x74,0x68,0x65,
               0x20,0x4d,0x44,0x35,0x20,0x28,0x6d,0x65,
               0x73,0x73,0x61,0x67,0x65,0x2d,0x64,0x69,
               0x67,0x65,0x73,0x74,0x20,0x61,0x6c,0x67,
               0x6f,0x72,0x69,0x74,0x68,0x6d,0x20,0x35,
               0x29,0x20,0x68,0x61,0x73,0x68,0x20,0x61,
               0x6c,0x67,0x6f,0x72,0x69,0x74,0x68,0x6d,
               0x20,0x61,0x6e,0x64,0x20,0x74,0x68,0x65,
               0x20,0x48,0x4d,0x41,0x43,0x20,0x28,0x6b,
               0x65,0x79,0x65,0x64,0x2d,0x68,0x61,0x73,
               0x68,0x20,0x6d,0x65,0x73,0x73,0x61,0x67,
               0x65,0x20,0x61,0x75,0x74,0x68,0x65,0x6e,
               0x74,0x69,0x63,0x61,0x74,0x69,0x6f,0x6e,
               0x20,0x63,0x6f,0x64,0x65,0x29,0x20,0x61,
               0x6c,0x67,0x6f,0x72,0x69,0x74,0x68,0x6d,
               0x20,0x73,0x75,0x69,0x74,0x61,0x62,0x6c,
               0x65,0x20,0x66,0x6f,0x72,0x20,0x61,0x20,
               0x76,0x61,0x72,0x69,0x65,0x74,0x79,0x20,
               0x6f,0x66,0x20,0x61,0x70,0x70,0x6c,0x69,
               0x63,0x61,0x74,0x69,0x6f,0x6e,0x73,0x2e,
               };

uint8_t digest[20];
uint8_t expected_digest[20] = {0x08, 0x54, 0x77, 0x5E, 
                               0xC2, 0xA1, 0x0C, 0x7F, 
                               0x4B, 0x80, 0x37, 0xD9, 
                               0xE7, 0x7C, 0xA7, 0x30, 
                               0xF0, 0x5D, 0xFA, 0x2E}; 
uint32_t i = 0, len = 0;

void secure_fault(void);
void secure_error(void);

extern void hash_sha1_dma(uint8_t *input, uint32_t in_length, uint8_t output[20]);
extern void callback_config(void *fault, void *error);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* configure LEDs */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);

    /* callback function configuration */
    callback_config((void *)secure_fault, (void *)secure_error);
    
    /* SHA-1 digest computation */
    len = sizeof(message_input);      
    hash_sha1_dma(message_input, len, digest);
    
    for(i = 0; i < 20; i++){
        /* compare result right -- LED1 on */
        if(digest[i] == expected_digest[i]){
            gd_eval_led_on(LED1);
        }else{
            /* compare result error -- LED2 on */
            gd_eval_led_on(LED2);
            gd_eval_led_off(LED1);
            break;
        }
    }

    while(1){
    }
}

/*!
    \brief      callback function called by SecureFault_Handler from secure code
    \param[in]  none
    \param[out] none
    \retval     none
*/
void secure_fault(void)
{
    gd_eval_led_on(LED2);
    while(1){
    }
} 

/*!
    \brief      callback function called by TZIAC_S_IRQHandler from secure code
    \param[in]  none
    \param[out] none
    \retval     none
*/
void secure_error(void)
{
    gd_eval_led_on(LED2);
    while(1){
    }
}
