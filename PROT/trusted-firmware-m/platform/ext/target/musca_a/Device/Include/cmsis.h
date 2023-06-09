/*
 * Copyright (c) 2017-2019 Arm Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MUSCA_CMSIS_H__
#define __MUSCA_CMSIS_H__

/* Processor and Core Peripherals and configurations */

/* ========================================================================= */
/* ================  Processor and Core Peripheral Section  ================ */
/* ========================================================================= */

/* ================  Start of section using anonymous unions  ============== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --  Configuration of the Cortex-M33 Processor and Core Peripherals  -- */
#ifdef DUAL_CORE
/* Both cores are used */
#define __CM33_REV                0x0001U   /* Core revision r0p1 */
#define __SAUREGION_PRESENT       1U        /* SAU regions present */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          4U        /* Number of Bits used for Priority
                                             * Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick
                                             * Config is used */

#if defined CORE0
#define __FPU_PRESENT             0U        /* no FPU present */
#define __DSP_PRESENT             0U        /* no DSP extension present */
#elif defined CORE1
#define __FPU_PRESENT             1U        /* FPU present */
#define __DSP_PRESENT             1U        /* DSP extension present */
#else
#error "Either CORE0 or CORE1 must be defined"
#endif /* CORE0/1 */

#else /* DUAL_CORE */

/* Single core is used */
/* -----  Configuration of the Cortex-M33 Processor and Core Peripherals  --- */
#define __CM33_REV                0x0001U   /* Core revision r0p1 */
#define __SAUREGION_PRESENT       1U        /* SAU regions present */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          4U        /* Number of Bits used for Priority
                                             * Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick
                                             * Config is used */
#define __FPU_PRESENT             0U        /* no FPU present */
#define __DSP_PRESENT             0U        /* no DSP extension present */
#endif /* DUAL_CORE */

#include "system_core_init.h"
#include "platform_irq.h"
#include <core_cm33.h>    /*!< Arm Cortex-M33 processor and core peripherals */

/* ============== End of section using anonymous unions  =================== */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#endif /*__MUSCA_CMSIS_H__ */
