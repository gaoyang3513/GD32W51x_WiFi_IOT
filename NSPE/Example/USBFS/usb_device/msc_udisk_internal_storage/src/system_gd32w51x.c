/*!
    \file    system_gd32w51x.c
    \brief   CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
             GD32W51x Device Series
*/

/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#include "gd32w51x.h"

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3))
#include "partition_gd32w51x.h"
#include "main.h"
#endif

/* system frequency define */
#define __IRC16M          (IRC16M_VALUE)            /* internal 16 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)             /* high speed crystal oscillator frequency */
#define __SYS_OSC_CLK     (__IRC16M)                /* main oscillator frequency */

/* select a system clock by uncommenting the following line */
//#define __SYSTEM_CLOCK_IRC16M                       (uint32_t)(__IRC16M)
//#define __SYSTEM_CLOCK_HXTAL                        (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_120M_PLLP_IRC16M             (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_120M_PLLP_8M_HXTAL           (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_120M_PLLP_25M_HXTAL          (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_120M_PLLP_40M_HXTAL          (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_168M_PLLP_IRC16M             (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_168M_PLLP_8M_HXTAL           (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_168M_PLLP_25M_HXTAL          (uint32_t)(168000000)
#define __SYSTEM_CLOCK_168M_PLLP_40M_HXTAL          (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_180M_PLLP_IRC16M             (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_180M_PLLP_8M_HXTAL           (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_180M_PLLP_25M_HXTAL          (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_180M_PLLP_40M_HXTAL          (uint32_t)(180000000)

#define SEL_IRC16M      0x00U
#define SEL_HXTAL       0x01U
#define SEL_PLLP        0x02U
#define SEL_PLLDIG      0x03U

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC16M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC16M;
static void system_clock_16m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_IRC16M;
static void system_clock_120m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_120M_PLLP_8M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_8M_HXTAL;
static void system_clock_120m_8m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_120M_PLLP_25M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_25M_HXTAL;
#elif defined (__SYSTEM_CLOCK_120M_PLLP_40M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_40M_HXTAL;
static void system_clock_120m_40m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_IRC16M;
static void system_clock_168m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_8M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_8M_HXTAL;
static void system_clock_168m_8m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_25M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_25M_HXTAL;
static void system_clock_168m_25m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_40M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_40M_HXTAL;
static void system_clock_168m_40m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_IRC16M;
static void system_clock_180m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_8M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_8M_HXTAL;
static void system_clock_180m_8m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_25M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_25M_HXTAL;
static void system_clock_180m_25m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_40M_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_40M_HXTAL;
static void system_clock_180m_40m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC16M */

/* configure the system clock */
static void system_clock_config(void);

/*!
    \brief      setup the microcontroller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemInit (void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    /* configure SAU region attributes */
    sau_region_config();
#endif

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) || SYS_NS
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif

    /* reset the RCU clock configuration to the default reset state */
    /* set IRC16MEN bit */
    RCU_CTL |= RCU_CTL_IRC16MEN;
    /* reset CFG0 register */
    RCU_CFG0 = 0x00000000U;

    /* reset HXTALEN, CKMEN and PLLEN bits */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN);

    /* reset PLLCFGR register */
    RCU_PLL = 0x00003010U;

    /* disable all interrupts */
    RCU_INT = 0x00000000U;

    /* configure the System clock source, PLL Multiplier and Divider factors, 
       AHB/APBx prescalers and Flash settings */
    system_clock_config();
#endif
}
/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_IRC16M
    system_clock_16m_irc16m();
#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
    system_clock_120m_irc16m();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_8M_HXTAL)
    system_clock_120m_8m_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_25M_HXTAL)
    system_clock_120m_25m_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_40M_HXTAL)
    system_clock_120m_40m_hxtal();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
    system_clock_168m_irc16m();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_8M_HXTAL)
    system_clock_168m_8m_hxtal();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_25M_HXTAL)
    system_clock_168m_25m_hxtal();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_40M_HXTAL)
    system_clock_168m_40m_hxtal();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
    system_clock_180m_irc16m();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_8M_HXTAL)
    system_clock_180m_8m_hxtal();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_25M_HXTAL)
    system_clock_180m_25m_hxtal();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_40M_HXTAL)
    system_clock_180m_40m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC16M */   
}

#ifdef __SYSTEM_CLOCK_IRC16M
/*!
    \brief      configure the system clock to 16M by IRC16M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_16m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    }while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));
    
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)){
        while(1){
        }
    }
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;
    
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;
    
    /* select IRC16M as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_IRC16M;

    /* wait until IRC16M is selected as system clock */
    while(0 != (RCU_CFG0 & RCU_SCSS_IRC16M)){
    }
}

#elif defined (__SYSTEM_CLOCK_HXTAL)
/*!
    \brief      configure the system clock to HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up the HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;
    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* select HXTAL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_HXTAL;

    /* wait until HXTAL is selected as system clock */
    while(0 == (RCU_CFG0 & RCU_SCSS_HXTAL)){
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 120M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_irc16m(void)
{
    uint32_t timeout = 0U; 
    uint32_t stab_flag = 0U;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    }while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 16, PLL_N = 240, PLL_P = 2 */ 
    RCU_PLL = (16U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_IRC16M) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_8M_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_8m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;	
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }
 
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 8, PLL_N = 240, PLL_P = 2 */ 
    RCU_PLL = (8U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_25M_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL(25M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_25m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;	

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 25, PLL_N = 240, PLL_P = 2 */ 
    RCU_PLL = (25U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_40M_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL(40M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_40m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 40, PLL_N = 240, PLL_P = 2 */ 
    RCU_PLL = (40U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 168M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    }while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 16, PLL_N = 336, PLL_P = 2 */ 
    RCU_PLL = (16U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_IRC16M) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_8M_HXTAL)
/*!
    \brief      configure the system clock to 168M by PLL which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_8m_hxtal(void)
{
    uint32_t timeout = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;	
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    while((0U == (RCU_CTL & RCU_CTL_HXTALSTB)) && (HXTAL_STARTUP_TIMEOUT != timeout++)){
    }

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;
    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 8, PLL_N = 336, PLL_P = 2 */ 
    RCU_PLL = (8U | (336 << 6U) | (((2 >> 1U) -1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }
    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_25M_HXTAL)
/*!
    \brief      configure the system clock to 168M by PLL which selects HXTAL(25M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_25m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */    
    RCU_CTL |= RCU_CTL_HXTALPU;	
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 25, PLL_N = 336, PLL_P = 2 */ 
    RCU_PLL = (25U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_40M_HXTAL)
/*!
    \brief      configure the system clock to 168M by PLL which selects HXTAL(40M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_40m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */    
    RCU_CTL |= RCU_CTL_HXTALPU;	
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 40, PLL_N = 336, PLL_P = 2 */ 
    RCU_PLL = (40U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 180M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    }while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 16, PLL_N = 360, PLL_P = 2 */ 
    RCU_PLL = (16U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_IRC16M) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_8M_HXTAL)
/*!
    \brief      configure the system clock to 180M by PLL which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_8m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 8, PLL_N = 360, PLL_P = 2 */ 
    RCU_PLL = (8U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_25M_HXTAL)
/*!
    \brief      configure the system clock to 180M by PLL which selects HXTAL(25M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_25m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;
    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 25, PLL_N = 360, PLL_P = 2 */ 
    RCU_PLL = (25U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLLP as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_40M_HXTAL)
/*!
    \brief      configure the system clock to 180M by PLL which selects HXTAL(40M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_40m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* power up HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;

    RCU_CTL |= RCU_CTL_HXTALREADY;
    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 40, PLL_N = 360, PLL_P = 2 */ 
    RCU_PLL = (40U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
                   (RCU_PLLSRC_HXTAL) );

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLLP as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLLP)){
    }
}

#endif /* __SYSTEM_CLOCK_IRC16M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from cpu registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate (void)
{
    uint32_t sws;
    uint32_t pllpsc, plln, pllsel, pllp, ck_src, idx, clk_exp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws){
    /* IRC16M is selected as CK_SYS */
    case SEL_IRC16M:
        SystemCoreClock = IRC16M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLLP is selected as CK_SYS */
    case SEL_PLLP:
        /* get the value of PLLPSC[5:0] */
        pllpsc = GET_BITS(RCU_PLL, 0U, 5U);
        plln = GET_BITS(RCU_PLL, 6U, 14U);
        pllp = (GET_BITS(RCU_PLL, 16U, 17U) + 1U) * 2U;
        /* PLL clock source selection, HXTAL or IRC8M/2 */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);
        if (RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC16M_VALUE;
        }
        SystemCoreClock = ((ck_src / pllpsc) * plln)/pllp;
        break;
    /* IRC16M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC16M_VALUE;
        break;
    }
    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    SystemCoreClock = SystemCoreClock >> clk_exp;
}
