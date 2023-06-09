/*!
    \file    main.c
    \brief   wakeup from deepsleep

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
#include <stdio.h>
#include "I2C_IE.h"
#include "gd32w515p_eval.h"
#include "systick.h"

#define I2C0_OWN_ADDRESS7 0x82
uint8_t i2c_buffer_receiver[16] = {0};
volatile uint8_t* i2c_rxbuffer;

void rcu_config(void);
void i2c_gpio_config(void);
void i2c_config(void);
void i2c_nvic_config(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* systick configure */
    systick_config();
    /* initialize LED1 */
    gd_eval_led_init(LED1);
    /* wakeup key configure */
    gd_eval_key_init(KEY_TAMPER_WAKEUP, KEY_MODE_GPIO);
    /* configure the I2C0 clock source selection */
    rcu_i2c0_clock_config(RCU_I2C0SRC_IRC16M);

    /* RCU configure */
    rcu_config();
    /* GPIO configure */
    i2c_gpio_config();
    /* I2C configure */
    i2c_config();
    /* NVIC configure */
    i2c_nvic_config();
    /* initialize the EXTI line 26 */
    exti_init(EXTI_26, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    /* enable wakeup from deep-sleep mode */
    i2c_wakeup_from_deepsleep_enable(I2C0);
    /* enable the I2C0 interrupt */
    i2c_interrupt_enable(I2C0, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_ADDM | I2C_INT_RBNE);
    while(1){
        if(SET != gpio_input_bit_get(TAMPER_WAKEUP_KEY_GPIO_PORT, TAMPER_WAKEUP_KEY_PIN)){
            pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, PMU_LOWDRIVER_ENABLE, WFI_CMD);
        }
    }
}

/*!
    \brief      enable the peripheral clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable GPIOA clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable GPIOB clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    /* enable I2C0 clock */
    rcu_periph_clock_enable(RCU_I2C0);
    /* enable PMU clock */
    rcu_periph_clock_enable(RCU_PMU);
}

/*!
    \brief      configure the I2C0 GPIO ports
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_gpio_config(void)
{
    /* connect PA15 to I2C0_SCL */
    gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_15);
    /* connect PB7 to I2C0_SDA */
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_7);
    /* configure GPIO pins of I2C0 */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_15);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO_PIN_15);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO_PIN_7);
}

/*!
    \brief      configure the I2C0 interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_config(void)
{
    /* configure I2C address */
    i2c_address_config(I2C0, I2C0_OWN_ADDRESS7, I2C_ADDFORMAT_7BITS);
    /* enable I2C0 */
    i2c_enable(I2C0);
}
/*!
    \brief      configure the NVIC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_nvic_config(void)
{
    nvic_irq_enable(I2C0_EV_IRQn, 0, 3);
    nvic_irq_enable(I2C0_ER_IRQn, 0, 2);
    nvic_irq_enable(I2C0_WKUP_IRQn, 0, 1);
}

/*!
    \brief      toggle the led every 200ms
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_spark(void)
{
    static __IO uint32_t timingdelaylocal = 0U;

    if(timingdelaylocal){

        if(timingdelaylocal < 200U){
            gd_eval_led_on(LED1);
        }else{
            gd_eval_led_off(LED1);
        }

        timingdelaylocal--;
    }else{
        timingdelaylocal = 400U;
    }
}
