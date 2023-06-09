/*!
    \file    main.c
    \brief   HASH SHA1 MD5 example
    
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

#include "gd32w515p_eval.h"
#include "stdio.h"
#include "string.h"

const uint8_t message_input[] =
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
static uint8_t md5_output[16];
static uint8_t sha1_output[20];

/* printf data in bytes */
static void data_display(uint32_t datalength, uint8_t *data);

uint32_t i = 0, len = 0;

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    gd_eval_com_init(EVAL_COM0);
    /* enable HAU clock */
    rcu_periph_clock_enable(RCU_HAU);  

    len = sizeof(message_input);
    printf("\r\nmessage to be hashed:\r\n\r\n");
    for(i = 0; i < len ; i++){
        printf("%c", message_input[i]);
    }

    /* SHA-1 digest computation */
    hau_hash_sha_1((uint8_t *)message_input, len, sha1_output);
    printf("  \r\n\r\nSHA1 message digest (160 bits):\r\n\r\n");
    data_display(20, sha1_output);

    /* MD5 digest computation */
    hau_hash_md5((uint8_t *)message_input, len, md5_output);
    printf("  \r\n\r\nMD5 message digest (128 bits):\r\n\r\n");
    data_display(16, md5_output);

    while(1){
    }
}

/*!
    \brief      printf data in bytes
    \param[in]  datalength: length of the data to display
    \param[in]  data: pointer to the data to display
    \param[out] none
    \retval     none
*/
static void data_display(uint32_t datalength, uint8_t *data)
{
    uint32_t i =0, count = 0;

    for(i = 0; i < datalength; i++){
        printf("0x%02X ", data[i]);
        count++;

        if(4 == count){
            count = 0;
            printf("\r\n");
        }
    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM0, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));

    return ch;
}
