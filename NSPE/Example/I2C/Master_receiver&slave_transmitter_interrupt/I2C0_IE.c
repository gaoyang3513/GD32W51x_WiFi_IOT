/*!
    \file    I2C0_IE.c
    \brief   I2C0 master receiver interrupt program

    \version 2021-10-30, V1.0.0, firmware for gd32w51x
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

#include "I2C_IE.h"

/*!
    \brief      handle I2C0 event interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c0_event_irq_handler(void)
{
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_STPDET)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_STPDET);
        /* disable the I2C0 interrupt */
        i2c_interrupt_disable(I2C0, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TC);
    }else if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_RBNE)){
        /* read a data byte from I2C_RDATA*/
        *i2c_rxbuffer++ = i2c_data_receive(I2C0);
    }else if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_TC)){
        i2c_stop_on_bus(I2C0);
        status = SUCCESS;
    }
}

/*!
    \brief      handle I2C0 error interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c0_error_irq_handler(void)
{
    /* bus error */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_BERR)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_BERR);
    }

    /* arbitration lost */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_LOSTARB)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_LOSTARB);
    }

    /* over-run or under-run when SCL stretch is disabled */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_OUERR)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_OUERR);
    }

    /* PEC error */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_PECERR)){
       i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_PECERR);
    }

    /* timeout error */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_TIMEOUT)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_TIMEOUT);
    }

    /* SMBus alert */
    if(i2c_interrupt_flag_get(I2C0, I2C_INT_FLAG_SMBALT)){
        i2c_interrupt_flag_clear(I2C0, I2C_INT_FLAG_SMBALT);
    }

    /* disable the I2C0 interrupt */
    i2c_interrupt_disable(I2C0, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TC);
}
