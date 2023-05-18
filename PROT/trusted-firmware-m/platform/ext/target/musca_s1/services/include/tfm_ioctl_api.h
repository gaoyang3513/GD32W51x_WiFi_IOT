/*
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_IOCTL_API__
#define __TFM_IOCTL_API__

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include "tfm_api.h"
#include "tfm_platform_api.h"

#ifdef __cplusplus
extern "C" {
#endif

enum tfm_platform_ioctl_reqest_types_t {
    TFM_PLATFORM_IOCTL_GPIO_SERVICE,
};

/*!
 * \enum tfm_gpio_service_type_t
 *
 * \brief GPIO service types (supported types may vary based on the platform)
 */
enum tfm_gpio_service_type_t {
    TFM_GPIO_SERVICE_TYPE_INIT = 0,          /*!< Init */
    TFM_GPIO_SERVICE_TYPE_PIN_CONFIG,        /*!< Pin config */
    TFM_GPIO_SERVICE_TYPE_PIN_WRITE,         /*!< Pin write */
    TFM_GPIO_SERVICE_TYPE_PIN_READ,          /*!< Pin read */
    TFM_GPIO_SERVICE_TYPE_PORT_CONFIG,       /*!< Port config */
    TFM_GPIO_SERVICE_TYPE_PORT_WRITE,        /*!< Port write */
    TFM_GPIO_SERVICE_TYPE_PORT_READ,         /*!< Port read */
    TFM_GPIO_SERVICE_TYPE_MAX = INT_MAX      /*!< Max to force enum max size */
};

/*!
 * \struct tfm_gpio_service_args_t
 *
 * \brief Argument list for each platform GPIO service
 */
struct tfm_gpio_service_args_t {
    enum tfm_gpio_service_type_t type;
    union {
        struct gpio_config_args { /*!< TFM_GPIO_SERVICE_TYPE_PIN_CONFIG ||
                                       TFM_GPIO_SERVICE_TYPE_PORT_CONFIG  */
            uint32_t pin_num_or_mask;
            uint32_t direction;
        } gpio_config;
        struct gpio_write_args { /*!< TFM_GPIO_SERVICE_TYPE_PIN_WRITE ||
                                      TFM_GPIO_SERVICE_TYPE_PORT_WRITE */
            uint32_t pin_num_or_mask;
            uint32_t value;
        } gpio_write;
        struct gpio_read_args { /*!< TFM_GPIO_SERVICE_TYPE_PIN_READ ||
                                     TFM_GPIO_SERVICE_TYPE_PORT_READ */
            uint32_t pin_num_or_mask;
        } gpio_read;
    } u;
};

/*!
 * \struct tfm_gpio_service_out_t
 *
 * \brief Output list for each GPIO platform service
 */
struct tfm_gpio_service_out_t {
    union {
        uint32_t result;               /*!< Generic result */
        struct gpio_read_result { /*!< TFM_GPIO_SERVICE_TYPE_PIN_READ ||
                                       TFM_GPIO_SERVICE_TYPE_PORT_READ */
            uint32_t result;
            uint32_t data;
        } gpio_read_result;
    } u;
};

/*!
 * \brief Initializes GPIO module
 *
 * \param[out] result       Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t tfm_platform_gpio_init(uint32_t *result);

/*!
 * \brief Configures a GPIO pin as input or output
 *
 * \param[in]  pin_num       Pin number of the selected pin
 * \param[in]  direction     Direction of the pin: 0 for input, 1 for output
 * \param[out] result        Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_pin_config(uint32_t pin_num, uint32_t direction,
                             uint32_t *result);

/*!
 * \brief Sets state of a selected GPIO pin
 *
 * \param[in]  pin_num  Pin number of the selected pin
 * \param[in]  value    Value to set for the pin
 * \param[out] result   Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_pin_write(uint32_t pin_num, uint32_t value, uint32_t *result);

/*!
 * \brief Reads state of a selected GPIO pin
 *
 * \param[in]     pin_num  Pin number of the selected pin
 * \param[in,out] data     Bit value read from the IO pin
 * \param[out]    result   Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_pin_read(uint32_t pin_num, uint32_t *data, uint32_t *result);

/*!
 * \brief Configures GPIO pins as input or output
 *
 * \param[in]  pin_mask      Pin mask of the selected pins
 * \param[in]  direction     Direction of the pin: 0 for input, 1 for output
 * \param[out] result        Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_port_config(uint32_t pin_mask, uint32_t direction,
                              uint32_t *result);

/*!
 * \brief Sets state of a selected GPIO pins
 *
 * \param[in]  pin_mask  Pin mask of the selected pins
 * \param[in]  value     Value mask to set for the pins
 * \param[out] result    Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_port_write(uint32_t pin_mask, uint32_t value,
                             uint32_t *result);

/*!
 * \brief Reads state of a selected GPIO pins
 *
 * \param[in]     pin_mask Pin mask of the selected pins
 * \param[in,out] data     Bit value mask read from the IO pins
 * \param[out]    result   Return error value
 *
 * \return Returns values as specified by the \ref tfm_platform_err_t
 */
enum tfm_platform_err_t
tfm_platform_gpio_port_read(uint32_t pin_mask, uint32_t *data,
                            uint32_t *result);

#ifdef __cplusplus
}
#endif

#endif /* __TFM_IOCTL_API__ */
