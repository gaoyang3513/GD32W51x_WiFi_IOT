/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MBEDTLS_SHA256_ALT_H
#define MBEDTLS_SHA256_ALT_H

#include <stddef.h>
#include <stdint.h>

#include "cc_hash_defs_proj.h"
#if defined (MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#endif


#define MBEDTLS_ERR_SHA256_HW_ACCEL_FAILED                -0x0037  /**< SHA-256 hardware accelerator failed */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SHA-256 context structure
 */
typedef struct mbedtls_sha256_context {
        /*! Internal buffer */
        uint32_t buff[CC_HASH_USER_CTX_SIZE_IN_WORDS]; // defined in cc_hash_defs.h
} mbedtls_sha256_context;

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_SHA256_ALT_H */
