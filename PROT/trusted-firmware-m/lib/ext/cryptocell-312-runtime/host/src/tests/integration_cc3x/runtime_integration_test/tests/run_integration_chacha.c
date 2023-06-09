/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <limits.h>

/* mbedtls lib */
#include "mbedtls/timing.h"

/* CC pal */
#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
#include "mbedtls/chacha20.h"
#include "mbedtls/poly1305.h"
#include "mbedtls/chachapoly.h"
#endif
#include "cc_pal_types.h"
#include "cc_common.h"

/* pal */
#include "test_pal_mem.h"

/* local */
#include "run_integration_pal_log.h"
#include "run_integration_test.h"
#include "run_integration_helper.h"

/************************************************************
 *
 * static functions prototypes
 *
 ************************************************************/
static RunItError_t runIt_Chacha(void);
static RunItError_t runIt_ChachaPolyEncrypt(void);
static RunItError_t runIt_ChachaPolyDecrypt(void);

/************************************************************
 *
 * static functions
 *
 ************************************************************/
static RunItError_t runIt_Chacha(void)
{
    RunItError_t rc = RUNIT_ERROR__OK;

#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
    static mbedtls_chacha_nonce pIVCounter = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00 };
    static mbedtls_chacha_key pKey = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    static uint32_t initialCounter = 1;
    static uint8_t pExpectedDataOut[] = { 0x6e, 0x2e, 0x35, 0x9a, 0x25, 0x68, 0xf9, 0x80, 0x41, 0xba, 0x07, 0x28, 0xdd, 0x0d, 0x69, 0x81, 0xe9, 0x7e, 0x7a, 0xec, 0x1d, 0x43, 0x60, 0xc2, 0x0a, 0x27, 0xaf, 0xcc, 0xfd, 0x9f, 0xae, 0x0b, 0xf9, 0x1b, 0x65, 0xc5, 0x52, 0x47, 0x33, 0xab, 0x8f, 0x59, 0x3d, 0xab, 0xcd, 0x62, 0xb3, 0x57, 0x16, 0x39, 0xd6, 0x24, 0xe6, 0x51, 0x52, 0xab, 0x8f, 0x53, 0x0c, 0x35, 0x9f, 0x08, 0x61, 0xd8, 0x07, 0xca, 0x0d, 0xbf, 0x50, 0x0d, 0x6a, 0x61, 0x56, 0xa3, 0x8e, 0x08, 0x8a, 0x22, 0xb6, 0x5e, 0x52, 0xbc, 0x51, 0x4d, 0x16, 0xcc, 0xf8, 0x06, 0x81, 0x8c, 0xe9, 0x1a, 0xb7, 0x79, 0x37, 0x36, 0x5a, 0xf9, 0x0b, 0xbf, 0x74, 0xa3, 0x5b, 0xe6, 0xb4, 0x0b, 0x8e, 0xed, 0xf2, 0x78, 0x5e, 0x42, 0x87, 0x4d };
    uint8_t pDataIn[] = { 0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f, 0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20, 0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69, 0x74, 0x2e };
    uint32_t j=0;
    static const uint32_t DATA_OUT_SIZE = 114;
    uint8_t *pDataOut = NULL;
    mbedtls_chacha20_context ctx;
    RunItPtr dataOutPtr;
    uint32_t blockSize = MBEDTLS_CHACHA_BLOCK_SIZE_BYTES;
    uint32_t dataLen = sizeof(pDataIn);
    const char* TEST_NAME = "ChaCha";
    RUNIT_SUB_TEST_START(TEST_NAME);

    ALLOC(dataOutPtr, pDataOut, DATA_OUT_SIZE);

    /*
     * integrated test
     */
    memset(pDataOut, 0, DATA_OUT_SIZE);
    RUNIT_ASSERT_W_PARAM("encrypt", mbedtls_chacha20_crypt( pKey,
                                                            pIVCounter,
                                                            initialCounter,
                                                            sizeof(pDataIn),
                                                            pDataIn,
                                                            pDataOut ) == CC_OK);

    RUNIT_ASSERT(memcmp(pDataOut, pExpectedDataOut, sizeof(pDataIn)) == 0);

    /*
     * non integrated test
     */
    memset(pDataOut, 0, DATA_OUT_SIZE);

    /* Initialise chacha */
    RUNIT_API(mbedtls_chacha20_init(&ctx));

    RUNIT_ASSERT_WITH_RESULT(mbedtls_chacha20_setkey( &ctx, pKey ), CC_OK);

    RUNIT_ASSERT_WITH_RESULT(mbedtls_chacha20_starts( &ctx, pIVCounter, initialCounter ), CC_OK);
    /* Iterate over all  blocks */
    for (j = 0; j < (blockSize * (dataLen / blockSize)); j += blockSize)
    {
        RUNIT_ASSERT_WITH_RESULT(mbedtls_chacha20_update( &ctx, blockSize , pDataIn + j, pDataOut + j ), CC_OK);
    }

    /* process remainder of last block */
    blockSize = dataLen % blockSize;
    if (blockSize)
    {
        RUNIT_ASSERT_WITH_RESULT(mbedtls_chacha20_update(&ctx, blockSize ,pDataIn + j, pDataOut + j), CC_OK);
    }

    /* free context */
    RUNIT_API(mbedtls_chacha20_free(&ctx));

    RUNIT_ASSERT(memcmp(pDataOut, pExpectedDataOut, sizeof(pDataIn)) == 0);


bail:

    FREE_IF_NOT_NULL(dataOutPtr);

    RUNIT_SUB_TEST_RESULT_W_PARAMS(TEST_NAME, "KEY[%ub] DATA_IN[%uB]", sizeof(pKey) * 8, sizeof(pDataIn));
#endif
    return rc;
}

static RunItError_t runIt_ChachaPolyEncrypt(void)
{
    RunItError_t rc = RUNIT_ERROR__OK;

#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
    static const uint8_t DATA_IN[] = { 0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f, 0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20, 0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73, 0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69, 0x74, 0x2e };
    static const uint8_t ADD_DATA[] = { 0x50, 0x51, 0x52, 0x53, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7 };

    static mbedtls_chacha_key pKey = { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f };    //pKey
    static mbedtls_chacha_nonce pNonce = { 0x07, 0x00, 0x00, 0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 };
    static const uint8_t pExpectedDataOut[] = { 0xd3, 0x1a, 0x8d, 0x34, 0x64, 0x8e, 0x60, 0xdb, 0x7b, 0x86, 0xaf, 0xbc, 0x53, 0xef, 0x7e, 0xc2, 0xa4, 0xad, 0xed, 0x51, 0x29, 0x6e, 0x08, 0xfe, 0xa9, 0xe2, 0xb5, 0xa7, 0x36, 0xee, 0x62, 0xd6, 0x3d, 0xbe, 0xa4, 0x5e, 0x8c, 0xa9, 0x67, 0x12, 0x82, 0xfa, 0xfb, 0x69, 0xda, 0x92, 0x72, 0x8b, 0x1a, 0x71, 0xde, 0x0a, 0x9e, 0x06, 0x0b, 0x29, 0x05, 0xd6, 0xa5, 0xb6, 0x7e, 0xcd, 0x3b, 0x36, 0x92, 0xdd, 0xbd, 0x7f, 0x2d, 0x77, 0x8b, 0x8c, 0x98, 0x03, 0xae, 0xe3, 0x28, 0x09, 0x1b, 0x58, 0xfa, 0xb3, 0x24, 0xe4, 0xfa, 0xd6, 0x75, 0x94, 0x55, 0x85, 0x80, 0x8b, 0x48, 0x31, 0xd7, 0xbc, 0x3f, 0xf4, 0xde, 0xf0, 0x8e, 0x4b, 0x7a, 0x9d, 0xe5, 0x76, 0xd2, 0x65, 0x86, 0xce, 0xc6, 0x4b, 0x61, 0x16 };
    static const uint8_t pExpectedMac[] = { 0x1a, 0xe1, 0x0b, 0x59, 0x4f, 0x09, 0xe2, 0x6a, 0x7e, 0x90, 0x2e, 0xcb, 0xd0, 0x60, 0x06, 0x91 };

    uint8_t *pCcDataOutBuff = NULL;
    uint8_t *pMacBuffRaw = NULL;
    uint8_t *pDataInRaw = NULL;
    uint8_t *pAddDataRaw = NULL;

    RunItPtr ccDataOutBuffPtr;
    RunItPtr macBuffRawPtr;
    RunItPtr dataInRawPtr;
    RunItPtr addDataRawPtr;

    mbedtls_chachapoly_context ctx;

    const char* TEST_NAME = "ChaCha-POLY-Encrypt";
    RUNIT_SUB_TEST_START(TEST_NAME);

    ALLOC(ccDataOutBuffPtr, pCcDataOutBuff, sizeof(pExpectedDataOut));
    ALLOC(macBuffRawPtr, pMacBuffRaw, MBEDTLS_POLY_MAC_SIZE_BYTES);
    ALLOC_AND_COPY(dataInRawPtr, pDataInRaw, DATA_IN, sizeof(DATA_IN));
    ALLOC_AND_COPY(addDataRawPtr, pAddDataRaw, ADD_DATA, sizeof(ADD_DATA));

    RUNIT_API(mbedtls_chachapoly_init(&ctx));

    RUNIT_ASSERT_WITH_RESULT( mbedtls_chachapoly_setkey( &ctx, pKey ), CC_OK);

    RUNIT_ASSERT_W_PARAM("encrypt", mbedtls_chachapoly_encrypt_and_tag( &ctx,
                                                                        sizeof(DATA_IN),
                                                                        pNonce,
                                                                        pAddDataRaw,
                                                                        sizeof(ADD_DATA),
                                                                        pDataInRaw,
                                                                        pCcDataOutBuff,
                                                                        pMacBuffRaw ) == CC_OK);


    RUNIT_PRINT_BUF(pCcDataOutBuff, sizeof(pExpectedDataOut), "ccDataOutBuff");
    RUNIT_PRINT_BUF(pExpectedDataOut, sizeof(pExpectedDataOut), "pExpectedDataOut");

    RUNIT_ASSERT(memcmp(pCcDataOutBuff, pExpectedDataOut, sizeof(pExpectedDataOut)) == 0);
    RUNIT_ASSERT(memcmp(pMacBuffRaw, pExpectedMac, sizeof(pExpectedMac)) == 0);

bail:
    FREE_IF_NOT_NULL(ccDataOutBuffPtr);
    FREE_IF_NOT_NULL(dataInRawPtr);
    FREE_IF_NOT_NULL(macBuffRawPtr);
    FREE_IF_NOT_NULL(addDataRawPtr);

    RUNIT_API(mbedtls_chachapoly_free(&ctx));

    RUNIT_SUB_TEST_RESULT_W_PARAMS(TEST_NAME, "KEY[%ub] DATA_IN[%uB] AAD[%uB]", sizeof(pKey) * 8, sizeof(DATA_IN), sizeof(ADD_DATA));
#endif
    return rc;
}

static RunItError_t runIt_ChachaPolyDecrypt(void)
{
    RunItError_t rc = RUNIT_ERROR__OK;

#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
    static const uint8_t DATA_IN[] = {0x64,0xa0,0x86,0x15,0x75,0x86,0x1a,0xf4,0x60,0xf0,0x62,0xc7,0x9b,0xe6,0x43,0xbd,0x5e,0x80,0x5c,0xfd,0x34,0x5c,0xf3,0x89,0xf1,0x08,0x67,0x0a,0xc7,0x6c,0x8c,0xb2,0x4c,0x6c,0xfc,0x18,0x75,0x5d,0x43,0xee,0xa0,0x9e,0xe9,0x4e,0x38,0x2d,0x26,0xb0,0xbd,0xb7,0xb7,0x3c,0x32,0x1b,0x01,0x00,0xd4,0xf0,0x3b,0x7f,0x35,0x58,0x94,0xcf,0x33,0x2f,0x83,0x0e,0x71,0x0b,0x97,0xce,0x98,0xc8,0xa8,0x4a,0xbd,0x0b,0x94,0x81,0x14,0xad,0x17,0x6e,0x00,0x8d,0x33,0xbd,0x60,0xf9,0x82,0xb1,0xff,0x37,0xc8,0x55,0x97,0x97,0xa0,0x6e,0xf4,0xf0,0xef,0x61,0xc1,0x86,0x32,0x4e,0x2b,0x35,0x06,0x38,0x36,0x06,0x90,0x7b,0x6a,0x7c,0x02,0xb0,0xf9,0xf6,0x15,0x7b,0x53,0xc8,0x67,0xe4,0xb9,0x16,0x6c,0x76,0x7b,0x80,0x4d,0x46,0xa5,0x9b,0x52,0x16,0xcd,0xe7,0xa4,0xe9,0x90,0x40,0xc5,0xa4,0x04,0x33,0x22,0x5e,0xe2,0x82,0xa1,0xb0,0xa0,0x6c,0x52,0x3e,0xaf,0x45,0x34,0xd7,0xf8,0x3f,0xa1,0x15,0x5b,0x00,0x47,0x71,0x8c,0xbc,0x54,0x6a,0x0d,0x07,0x2b,0x04,0xb3,0x56,0x4e,0xea,0x1b,0x42,0x22,0x73,0xf5,0x48,0x27,0x1a,0x0b,0xb2,0x31,0x60,0x53,0xfa,0x76,0x99,0x19,0x55,0xeb,0xd6,0x31,0x59,0x43,0x4e,0xce,0xbb,0x4e,0x46,0x6d,0xae,0x5a,0x10,0x73,0xa6,0x72,0x76,0x27,0x09,0x7a,0x10,0x49,0xe6,0x17,0xd9,0x1d,0x36,0x10,0x94,0xfa,0x68,0xf0,0xff,0x77,0x98,0x71,0x30,0x30,0x5b,0xea,0xba,0x2e,0xda,0x04,0xdf,0x99,0x7b,0x71,0x4d,0x6c,0x6f,0x2c,0x29,0xa6,0xad,0x5c,0xb4,0x02,0x2b,0x02,0x70,0x9b};
    static const uint8_t ADD_DATA[] = {0xf3,0x33,0x88,0x86,0x00,0x00,0x00,0x00,0x00,0x00,0x4e,0x91};

    static mbedtls_chacha_key pKey = {0x1c,0x92,0x40,0xa5,0xeb,0x55,0xd3,0x8a,0xf3,0x33,0x88,0x86,0x04,0xf6,0xb5,0xf0,0x47,0x39,0x17,0xc1,0x40,0x2b,0x80,0x09,0x9d,0xca,0x5c,0xbc,0x20,0x70,0x75,0xc0};
    static mbedtls_chacha_nonce pNonce = {0x00,0x00,0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    static const uint8_t pExpectedDataOut[] = {0x49, 0x6e, 0x74, 0x65, 0x72, 0x6e, 0x65, 0x74, 0x2d, 0x44, 0x72, 0x61, 0x66, 0x74, 0x73, 0x20, 0x61, 0x72, 0x65, 0x20, 0x64, 0x72, 0x61, 0x66, 0x74, 0x20, 0x64, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x61, 0x20, 0x6d, 0x61, 0x78, 0x69, 0x6d, 0x75, 0x6d, 0x20, 0x6f, 0x66, 0x20, 0x73, 0x69, 0x78, 0x20, 0x6d, 0x6f, 0x6e, 0x74, 0x68, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x6d, 0x61, 0x79, 0x20, 0x62, 0x65, 0x20, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x64, 0x2c, 0x20, 0x72, 0x65, 0x70, 0x6c, 0x61, 0x63, 0x65, 0x64, 0x2c, 0x20, 0x6f, 0x72, 0x20, 0x6f, 0x62, 0x73, 0x6f, 0x6c, 0x65, 0x74, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x6f, 0x74, 0x68, 0x65, 0x72, 0x20, 0x64, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x61, 0x74, 0x20, 0x61, 0x6e, 0x79, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x2e, 0x20, 0x49, 0x74, 0x20, 0x69, 0x73, 0x20, 0x69, 0x6e, 0x61, 0x70, 0x70, 0x72, 0x6f, 0x70, 0x72, 0x69, 0x61, 0x74, 0x65, 0x20, 0x74, 0x6f, 0x20, 0x75, 0x73, 0x65, 0x20, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x6e, 0x65, 0x74, 0x2d, 0x44, 0x72, 0x61, 0x66, 0x74, 0x73, 0x20, 0x61, 0x73, 0x20, 0x72, 0x65, 0x66, 0x65, 0x72, 0x65, 0x6e, 0x63, 0x65, 0x20, 0x6d, 0x61, 0x74, 0x65, 0x72, 0x69, 0x61, 0x6c, 0x20, 0x6f, 0x72, 0x20, 0x74, 0x6f, 0x20, 0x63, 0x69, 0x74, 0x65, 0x20, 0x74, 0x68, 0x65, 0x6d, 0x20, 0x6f, 0x74, 0x68, 0x65, 0x72, 0x20, 0x74, 0x68, 0x61, 0x6e, 0x20, 0x61, 0x73, 0x20, 0x2f, 0xe2, 0x80, 0x9c, 0x77, 0x6f, 0x72, 0x6b, 0x20, 0x69, 0x6e, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x65, 0x73, 0x73, 0x2e, 0x2f, 0xe2, 0x80, 0x9d};
    static const uint8_t pExpectedMac[] = {0xee,0xad,0x9d,0x67,0x89,0x0c,0xbb,0x22,0x39,0x23,0x36,0xfe,0xa1,0x85,0x1f,0x38};

    uint8_t *pDataInRaw = NULL;
    uint8_t *pAddDataRaw = NULL;
    uint8_t *pCcDataOutBuff = NULL;
    uint8_t *pMacBuffRaw = NULL;

    RunItPtr ccDataOutBuffPtr;
    RunItPtr macBuffRawPtr;
    RunItPtr dataInRawPtr;
    RunItPtr addDataRawPtr;

    mbedtls_chachapoly_context ctx;

    const char* TEST_NAME = "ChaCha-POLY-Decrypt";
    RUNIT_SUB_TEST_START(TEST_NAME);

    ALLOC(ccDataOutBuffPtr, pCcDataOutBuff, sizeof(pExpectedDataOut));
    ALLOC(macBuffRawPtr, pMacBuffRaw, MBEDTLS_POLY_MAC_SIZE_BYTES);
    ALLOC_AND_COPY(dataInRawPtr, pDataInRaw, DATA_IN, sizeof(DATA_IN));
    ALLOC_AND_COPY(addDataRawPtr, pAddDataRaw, ADD_DATA, sizeof(ADD_DATA));

    memcpy(pMacBuffRaw, pExpectedMac, MBEDTLS_POLY_MAC_SIZE_BYTES);

    RUNIT_API(mbedtls_chachapoly_init(&ctx));

    RUNIT_ASSERT_WITH_RESULT( mbedtls_chachapoly_setkey( &ctx, pKey ), CC_OK);

    RUNIT_ASSERT_W_PARAM("decrypt", mbedtls_chachapoly_auth_decrypt( &ctx,
                                                                     sizeof(DATA_IN),
                                                                     pNonce,
                                                                     pAddDataRaw,
                                                                     sizeof(ADD_DATA),
                                                                     pMacBuffRaw,
                                                                     pDataInRaw,
                                                                     pCcDataOutBuff) == CC_OK);

    RUNIT_PRINT_BUF(pCcDataOutBuff, sizeof(pExpectedDataOut), "ccDataOutBuff");
    RUNIT_PRINT_BUF(pExpectedDataOut, sizeof(pExpectedDataOut), "pExpectedDataOut");

    RUNIT_ASSERT(memcmp(pCcDataOutBuff, pExpectedDataOut, sizeof(pExpectedDataOut)) == 0);

bail:

    FREE_IF_NOT_NULL(ccDataOutBuffPtr);
    FREE_IF_NOT_NULL(dataInRawPtr);
    FREE_IF_NOT_NULL(macBuffRawPtr);
    FREE_IF_NOT_NULL(addDataRawPtr);

    RUNIT_API(mbedtls_chachapoly_free(&ctx));

    RUNIT_SUB_TEST_RESULT_W_PARAMS(TEST_NAME, "KEY[%ub] DATA_IN[%uB] AAD[%uB]", sizeof(pKey) * 8, sizeof(DATA_IN), sizeof(ADD_DATA));
#endif
    return rc;
}

static RunItError_t runIt_Poly(void)
{
    RunItError_t rc = RUNIT_ERROR__OK;

#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
    /* The following test vectors were taken from: https://tools.ietf.org/html/rfc7539 */
    /* section 2.5.2 */
    uint8_t KEY[] = {0X85, 0Xd6, 0Xbe, 0X78, 0X57, 0X55, 0X6d, 0X33, 0X7f, 0X44, 0X52, 0Xfe, 0X42, 0Xd5, 0X06, 0Xa8, 0X01, 0X03, 0X80, 0X8a, 0Xfb, 0X0d, 0Xb2, 0Xfd, 0X4a, 0Xbf, 0Xf6, 0Xaf, 0X41, 0X49, 0Xf5, 0X1b};
    uint8_t DATA_IN[] = {0x43, 0x72, 0X79, 0X70, 0X74, 0X6f, 0X67, 0X72, 0X61, 0X70, 0X68, 0X69, 0X63, 0X20, 0X46, 0X6f, 0x72, 0x75, 0X6d, 0X20, 0X52, 0X65, 0X73, 0X65, 0X61, 0X72, 0X63, 0X68, 0X20, 0X47, 0X72, 0X6f, 0x75, 0x70};
    uint8_t EXPECTED_MAC[] = {0xa8, 0x06, 0x1d, 0xc1, 0x30, 0x51, 0x36, 0xc6, 0xc2, 0x2b, 0x8b, 0xaf, 0x0c, 0x01, 0x27, 0xa9};

    uint8_t *pDataIn = NULL;
    uint8_t *pKey = NULL;
    uint8_t *pMacBuff = NULL;

    RunItPtr dataInPtr;
    RunItPtr keyPtr;
    RunItPtr macBuffPtr;

    const char* TEST_NAME = "POLY";
    RUNIT_SUB_TEST_START(TEST_NAME);

    ALLOC(dataInPtr, pDataIn, sizeof(DATA_IN));
    ALLOC(keyPtr, pKey, sizeof(KEY));
    ALLOC(macBuffPtr, pMacBuff, MBEDTLS_POLY_MAC_SIZE_BYTES);

    memcpy(pDataIn, DATA_IN, sizeof(DATA_IN));
    memcpy(pKey, KEY, sizeof(mbedtls_poly_key));

    RUNIT_ASSERT_WITH_RESULT(mbedtls_poly1305_mac(pKey,
                                          (uint8_t*)pDataIn,
                                          sizeof(DATA_IN),
                                          pMacBuff), CC_OK);

    RUNIT_ASSERT(memcmp(pMacBuff, EXPECTED_MAC, sizeof(EXPECTED_MAC)) == 0);

bail:
    FREE_IF_NOT_NULL(dataInPtr);
    FREE_IF_NOT_NULL(keyPtr);
    FREE_IF_NOT_NULL(macBuffPtr);

    RUNIT_SUB_TEST_RESULT_W_PARAMS(TEST_NAME, "KEY[%ub] PLAIN[%uB]", sizeof(mbedtls_poly_key) * 8, sizeof(DATA_IN));
#endif
    return rc;
}
/************************************************************
 *
 * public functions
 *
 ************************************************************/
RunItError_t runIt_ChachaTest(void)
{
    RunItError_t rc = RUNIT_ERROR__OK;

#if defined(CC_CONFIG_CC_CHACHA_POLY_SUPPORT)
    const char* TEST_NAME = "ChaCha";
    RUNIT_TEST_START(TEST_NAME);

    RUNIT_ASSERT(runIt_Poly() == RUNIT_ERROR__OK);
    RUNIT_ASSERT(runIt_Chacha() == RUNIT_ERROR__OK);
    RUNIT_ASSERT(runIt_ChachaPolyEncrypt() == RUNIT_ERROR__OK);
    RUNIT_ASSERT(runIt_ChachaPolyDecrypt() == RUNIT_ERROR__OK);

bail:
    RUNIT_TEST_RESULT(TEST_NAME);

#else
    (void) runIt_Poly;
    (void) runIt_Chacha;
    (void) runIt_ChachaPolyEncrypt;
    (void) runIt_ChachaPolyDecrypt;
#endif

    return rc;
}
