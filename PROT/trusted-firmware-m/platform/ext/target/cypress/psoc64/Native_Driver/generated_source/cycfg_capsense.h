/*******************************************************************************
* File Name: cycfg_capsense.h
* Version: 2.0
*
* Description:
* CapSense middleware configuration
* This file should not be modified. It was automatically generated by
* CapSense Configurator 2.0.0.1483
*
********************************************************************************
* Copyright 2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
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
*******************************************************************************/

#if !defined(CYCFG_CAPSENSE_H)
#define CYCFG_CAPSENSE_H

#include <stddef.h>
#include "cy_device_headers.h"
#include "cycfg_peripherals.h"

#if (CY_CAPSENSE_CORE == __CORTEX_M)


#if !defined(Cmod_PORT) || !defined(Cmod_PIN) || !defined(Cmod_PORT_NUM)
#error Cmod Capacitor is not assigned: missing #define Cmod_PORT, #define Cmod_PIN, #define Cmod_PORT_NUM
#endif

#if !defined(CintA_PORT) || !defined(CintA_PIN) || !defined(CintA_PORT_NUM)
#error CintA Capacitor is not assigned: missing #define CintA_PORT, #define CintA_PIN, #define CintA_PORT_NUM
#endif

#if !defined(CintB_PORT) || !defined(CintB_PIN) || !defined(CintB_PORT_NUM)
#error CintB Capacitor is not assigned: missing #define CintB_PORT, #define CintB_PIN, #define CintB_PORT_NUM
#endif

#if !defined(Button0_Rx0_PORT) || !defined(Button0_Rx0_PIN)
#error Button0_Rx0 Sensor is not assigned: missing #define Button0_Rx0_PORT, #define Button0_Rx0_PIN
#endif

#if !defined(Button0_Tx_PORT) || !defined(Button0_Tx_PIN)
#error Button0_Tx Sensor is not assigned: missing #define Button0_Tx_PORT, #define Button0_Tx_PIN
#endif

#if !defined(Button1_Rx0_PORT) || !defined(Button1_Rx0_PIN)
#error Button1_Rx0 Sensor is not assigned: missing #define Button1_Rx0_PORT, #define Button1_Rx0_PIN
#endif

#if !defined(Button1_Tx_PORT) || !defined(Button1_Tx_PIN)
#error Button1_Tx Sensor is not assigned: missing #define Button1_Tx_PORT, #define Button1_Tx_PIN
#endif

#if !defined(LinearSlider0_Sns0_PORT) || !defined(LinearSlider0_Sns0_PIN)
#error LinearSlider0_Sns0 Sensor is not assigned: missing #define LinearSlider0_Sns0_PORT, #define LinearSlider0_Sns0_PIN
#endif

#if !defined(LinearSlider0_Sns1_PORT) || !defined(LinearSlider0_Sns1_PIN)
#error LinearSlider0_Sns1 Sensor is not assigned: missing #define LinearSlider0_Sns1_PORT, #define LinearSlider0_Sns1_PIN
#endif

#if !defined(LinearSlider0_Sns2_PORT) || !defined(LinearSlider0_Sns2_PIN)
#error LinearSlider0_Sns2 Sensor is not assigned: missing #define LinearSlider0_Sns2_PORT, #define LinearSlider0_Sns2_PIN
#endif

#if !defined(LinearSlider0_Sns3_PORT) || !defined(LinearSlider0_Sns3_PIN)
#error LinearSlider0_Sns3 Sensor is not assigned: missing #define LinearSlider0_Sns3_PORT, #define LinearSlider0_Sns3_PIN
#endif

#if !defined(LinearSlider0_Sns4_PORT) || !defined(LinearSlider0_Sns4_PIN)
#error LinearSlider0_Sns4 Sensor is not assigned: missing #define LinearSlider0_Sns4_PORT, #define LinearSlider0_Sns4_PIN
#endif

#if !defined(CY_CAPSENSE_CPU_CLK)
#error CPU clock frequency is not set: missing #define CY_CAPSENSE_CPU_CLK
#endif

#if !defined(CY_CAPSENSE_PERI_CLK)
#error Peripheral clock core is not set: missing #define CY_CAPSENSE_PERI_CLK
#endif

#if !defined(CY_CAPSENSE_VDDA_MV)
#error VDDA voltage is not set: missing #define CY_CAPSENSE_VDDA_MV
#endif

#if !defined(CY_CAPSENSE_PERI_DIV_TYPE)
#error Peripheral clock divider type is not set: missing #define CY_CAPSENSE_PERI_DIV_TYPE
#endif

#if !defined(CY_CAPSENSE_PERI_DIV_INDEX)
#error Peripheral clock divider index is not set: missing #define CY_CAPSENSE_PERI_DIV_INDEX
#endif



#include "cy_capsense.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*Widget names */
#define CY_CAPSENSE_BUTTON0_WDGT_ID                            (0u)
#define CY_CAPSENSE_BUTTON1_WDGT_ID                            (1u)
#define CY_CAPSENSE_LINEARSLIDER0_WDGT_ID                      (2u)

/* Button0 sensor names */
#define CY_CAPSENSE_BUTTON0_SNS0_ID                            (0u)

/* Button0 node names */
#define CY_CAPSENSE_BUTTON0_RX0_TX0_ID                         (0u)

/* Button0 sensor element IDs */
#define CY_CAPSENSE_BUTTON0_RX0_ID                             (0u)
#define CY_CAPSENSE_BUTTON0_TX0_ID                             (1u)

/* Button1 sensor names */
#define CY_CAPSENSE_BUTTON1_SNS0_ID                            (0u)

/* Button1 node names */
#define CY_CAPSENSE_BUTTON1_RX0_TX0_ID                         (0u)

/* Button1 sensor element IDs */
#define CY_CAPSENSE_BUTTON1_RX0_ID                             (0u)
#define CY_CAPSENSE_BUTTON1_TX0_ID                             (1u)

/* LinearSlider0 sensor names */
#define CY_CAPSENSE_LINEARSLIDER0_SNS0_ID                      (0u)
#define CY_CAPSENSE_LINEARSLIDER0_SNS1_ID                      (1u)
#define CY_CAPSENSE_LINEARSLIDER0_SNS2_ID                      (2u)
#define CY_CAPSENSE_LINEARSLIDER0_SNS3_ID                      (3u)
#define CY_CAPSENSE_LINEARSLIDER0_SNS4_ID                      (4u)

/* Sensing Methods */
#define CY_CAPSENSE_CSD_EN                                     (1u)
#define CY_CAPSENSE_CSX_EN                                     (1u)
#define CY_CAPSENSE_CSD_CALIBRATION_EN                         (1u)
#define CY_CAPSENSE_CSX_CALIBRATION_EN                         (1u)
#define CY_CAPSENSE_SMARTSENSE_FULL_EN                         (1u)
#define CY_CAPSENSE_SMARTSENSE_HW_EN                           (0u)
#define CY_CAPSENSE_SMARTSENSE_DISABLED                        (0u)
#define CY_CAPSENSE_CSD_SHIELD_EN                              (0u)
#define CY_CAPSENSE_CSD_SHIELD_CAP_EN                          (0u)

/* Filtering */
#define CY_CAPSENSE_ADAPTIVE_FILTER_EN                         (0u)
#define CY_CAPSENSE_BALLISTIC_MULTIPLIER_EN                    (0u)
#define CY_CAPSENSE_RAWCOUNT_FILTER_EN                         (0u)
#define CY_CAPSENSE_POSITION_FILTER_EN                         (0u)
#define CY_CAPSENSE_CSD_POSITION_FILTER_EN                     (0u)
#define CY_CAPSENSE_CSX_POSITION_FILTER_EN                     (0u)

/* Widgets */
#define CY_CAPSENSE_CSD_BUTTON_EN                              (0u)
#define CY_CAPSENSE_CSD_MATRIX_EN                              (0u)
#define CY_CAPSENSE_CSD_SLIDER_EN                              (1u)
#define CY_CAPSENSE_CSD_TOUCHPAD_EN                            (0u)
#define CY_CAPSENSE_CSD_PROXIMITY_EN                           (0u)
#define CY_CAPSENSE_CSX_BUTTON_EN                              (1u)
#define CY_CAPSENSE_CSX_MATRIX_EN                              (0u)
#define CY_CAPSENSE_CSX_TOUCHPAD_EN                            (0u)
#define CY_CAPSENSE_ADVANCED_CENTROID_5X5_EN                   (0u)
#define CY_CAPSENSE_CSD_LINEAR_SLIDER_EN                       (1u)
#define CY_CAPSENSE_CSD_RADIAL_SLIDER_EN                       (0u)
#define CY_CAPSENSE_CSD_DIPLEX_SLIDER_EN                       (0u)

/* Features */
#define CY_CAPSENSE_GESTURE_EN                                 (0u)
#define CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN                    (0u)
#define CY_CAPSENSE_SNS_AUTO_RESET_EN                          (0u)

typedef struct {
    cy_stc_capsense_common_context_t commonContext;
    cy_stc_capsense_widget_context_t widgetContext[3];
    cy_stc_capsense_sensor_context_t sensorContext[7];
    cy_stc_capsense_position_t position[1];
} cy_stc_capsense_tuner_t;

extern cy_stc_capsense_tuner_t cy_capsense_tuner;

extern cy_stc_capsense_context_t cy_capsense_context;

#if defined(__cplusplus)
}
#endif

#endif /* CY_CAPSENSE_CORE == __CORTEX_M */

#endif /* CYCFG_CAPSENSE_H */

/* [] END OF FILE */

