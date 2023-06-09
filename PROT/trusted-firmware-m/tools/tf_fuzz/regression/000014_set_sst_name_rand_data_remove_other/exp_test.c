/*
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*
 * Test purpose:
 *     to remove something that doesn't exist
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#include "../sst/non_secure/ns_test_helpers.h"
#include "psa/protected_storage.h"
#include "test/framework/test_framework_helpers.h"
#include "crypto_tests_common.h"
#include "tfm_memory_utils.h"

/* This is not yet right for how to run a test;  need to register tests, etc. */

void test_thread (struct test_result_t *ret) {
    psa_status_t crypto_status;  // result from Crypto calls
    psa_status_t sst_status;

    /* To prevent unused variable warning, as the variable might not be used
     * in this testcase
     */
    (void)sst_status;

    crypto_status = psa_crypto_init();
    if (crypto_status != PSA_SUCCESS) {
        TEST_FAIL("Could not initialize Crypto.");
        return;
    }

    TEST_LOG("Test to remove something that doesn't exist");


    /* Variables (etc.) to initialize and check PSA assets: */
    static uint8_t george_data[] = "@@002@10@@********";
    static int george_data_size = \d+;


    /* PSA calls to test: */

    /* Creating SST asset "george," with data "@@002@10@@...". */
    sst_status = psa_ps_set(@@@001@@@, george_data_size, george_data,
                            PSA_STORAGE_FLAG_********);
    if (sst_status != PSA_SUCCESS) {
        TEST_FAIL("psa_ps_set() expected PSA_SUCCESS.");
        return;
    }

    sst_status = psa_ps_remove(********);
    if (sst_status != PSA_ERROR_DOES_NOT_EXIST) {
        TEST_FAIL("psa_ps_remove() expected PSA_ERROR_DOES_NOT_EXIST.");
        return;
    }

    /* Removing assets left over from testing: */
    psa_ps_remove(@@@001@@@);
    if (sst_status != PSA_SUCCESS) {
        TEST_FAIL("Failed to tear down an SST asset upon test completion.");
        return;
    }

    /* Test completed */
    ret->val = TEST_PASSED;
}
