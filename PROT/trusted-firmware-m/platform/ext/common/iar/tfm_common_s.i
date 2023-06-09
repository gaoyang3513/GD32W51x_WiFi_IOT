#include "region_defs.h"
include "..\..\..\ROM-EXPORT\symbol\rom_symbol.icf";

define memory mem with size = 4G;

define region S_CODE_region     = mem:[from S_CODE_START size S_CODE_SIZE];

define region S_RAM_region      = mem:[from S_DATA_START size S_DATA_SIZE];

define block ER_TFM_CODE          with fixed order, alignment = 8 {readonly section .intvec, readonly};

define block TFM_UNPRIV_CODE with alignment = 32 {
       ro object tfm_spm_services.o,
       ro object platform_retarget_dev.o,
       ro object device_definition.o,
       section SFN,
       ro section .rodata object tfm_*_secure_api.o,
       ro object *6M_tl*.a,
       ro object *7M_tl*.a,
       ro object *libtfmsprt.a
       };

    /**** PSA RoT RO part (CODE + RODATA) start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of PSA RoT code.
     */
define block TFM_PSA_CODE_START with alignment = 32, size = 0 { };

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
define block TFM_SP_ITS_LINKER with alignment = 32 {
        ro object *tfm_internal_trusted_storage*,
        section TFM_SP_ITS_ATTR_FN
    };
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_AUDIT_LOG
define block TFM_SP_AUDIT_LOG_LINKER with alignment = 32 {
        ro object *tfm_audit*,
        section TFM_SP_AUDIT_LOG_ATTR_FN
    };
#endif /* TFM_PARTITION_AUDIT_LOG */

#ifdef TFM_PARTITION_CRYPTO
define block TFM_SP_CRYPTO_LINKER with alignment = 32 {
        ro object *tfm_crypto*,
        section TFM_SP_CRYPTO_ATTR_FN
    };
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
define block TFM_SP_PLATFORM_LINKER with alignment = 32 {
        ro object *tfm_platform*,
        section TFM_SP_PLATFORM_ATTR_FN
    };
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
define block TFM_SP_INITIAL_ATTESTATION_LINKER with alignment = 32 {
        ro object *tfm_attest*,
        section TFM_SP_INITIAL_ATTESTATION_ATTR_FN
    };
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
define block TFM_SP_CORE_TEST_LINKER with alignment = 32 {
        ro object *tfm_ss_core_test.*,
        section TFM_SP_CORE_TEST_ATTR_FN
    };
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
define block TFM_SP_SECURE_TEST_PARTITION_LINKER with alignment = 32 {
        ro object *tfm_secure_client_service.*,
        ro object *test_framework*,
        ro object *uart_stdout.*,
        ro object *Driver_USART.*,
        ro object *arm_uart_drv.*,
        ro object *uart_pl011_drv.*,
        ro object *uart_cmsdk_drv*,
        ro object *secure_suites.*,
        ro object *attestation_s_interface_testsuite.*,
        section TFM_SP_SECURE_TEST_PARTITION_ATTR_FN
    };
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
define block TFM_SP_IPC_SERVICE_TEST_LINKER with alignment = 32 {
        ro object *ipc_service_test.*,
        section TFM_SP_IPC_SERVICE_TEST_ATTR_FN
    };
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_PS
define block TFM_SP_PS_TEST_LINKER with alignment = 32 {
        ro object *tfm_ps_test_service.*,
        section TFM_SP_PS_TEST_ATTR_FN
    };
#endif /* TFM_PARTITION_TEST_PS */

    /*
     * This empty, zero long execution region is here to mark the end address
     * of PSA RoT code.
     */
define block TFM_PSA_CODE_END with alignment = 32, size = 0 { };

    /**** APPLICATION RoT RO part (CODE + RODATA) start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of APP RoT code.
     */
define block TFM_APP_CODE_START with alignment = 32, size = 0 { };

#ifdef TFM_PARTITION_PROTECTED_STORAGE
define block TFM_SP_PS_LINKER with alignment = 32 {
        ro object *tfm_storage*,
        ro object *test_ps_nv_counters.*,
    };
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_TEST_CORE
define block TFM_SP_CORE_TEST_2_LINKER with alignment = 32 {
        ro object *tfm_ss_core_test_2.*,
    };
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE_IPC
define block TFM_SP_IPC_CLIENT_TEST_LINKER with alignment = 32 {
        ro object *ipc_client_test.*,
    };
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
define block TFM_IRQ_TEST_1_LINKER with alignment = 32 {
        ro object *tfm_irq_test_service_1.*,
        ro object *timer_cmsdk*,
    };
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
define block TFM_SP_SECURE_CLIENT_2_LINKER with alignment = 32 {
        ro object *tfm_secure_client_2.*,
    };
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_MULTI_CORE_TEST
define block TFM_SP_MULTI_CORE_TEST_LINKER with alignment = 32 {
        ro object *multi_core_test.*,
    };
#endif /* TFM_MULTI_CORE_TEST */

    /*
     * This empty, zero long execution region is here to mark the end address
     * of APP RoT code.
     */
define block TFM_APP_CODE_END with alignment = 32, size = 0 { };

    /**** Base address of secure data area */
define block TFM_SECURE_DATA_START with size = 0 { };

#if !TFM_MULTI_CORE_TOPOLOGY
    /* Shared area between BL2 and runtime to exchange data */
define block TFM_SHARED_DATA with alignment = 32, size = BOOT_TFM_SHARED_DATA_SIZE { };
define block ARM_LIB_STACK_MSP with alignment = 32, size = S_MSP_STACK_SIZE { };
define overlay STACK_DATA {block TFM_SHARED_DATA};
define overlay STACK_DATA {block ARM_LIB_STACK_MSP};

define block ARM_LIB_STACK with alignment = 32, size = S_PSP_STACK_SIZE { };
#endif

#if !defined(TFM_PSA_API)
define block TFM_SECURE_STACK   with size = 0x2000, alignment = 128 {};
#endif /* !defined(TFM_PSA_API) */

define block TFM_UNPRIV_DATA with alignment = 32 {
       rw object tfm_spm_services.o,
       rw object platform_retarget_dev.o,
       rw object device_definition.o,
       };

define block TFM_APP_RW_STACK_START with alignment = 32, size = 0 { };

#ifdef TFM_PARTITION_PROTECTED_STORAGE
define block TFM_SP_PS_LINKER_DATA with alignment = 32 {
        rw object *tfm_storage*,
        rw object *test_ps_nv_counters.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_PS_LINKER_STACK with alignment = 128, size = 0x800 { };
#endif
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_TEST_CORE
define block TFM_SP_CORE_TEST_2_LINKER_DATA with alignment = 32 {
        rw object *tfm_ss_core_test_2.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_CORE_TEST_2_LINKER_STACK with alignment = 128, size = 0x0280 { };
#endif
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE_IPC
define block TFM_SP_IPC_CLIENT_TEST_LINKER_DATA with alignment = 32 {
        rw object *ipc_client_test.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_IPC_CLIENT_TEST_LINKER_STACK with alignment = 128, size = 0x0300 { };
#endif
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
define block TFM_IRQ_TEST_1_LINKER_DATA with alignment = 32 {
        rw object *tfm_irq_test_service_1.*,
        rw object *timer_cmsdk*,
    };

#if defined (TFM_PSA_API)
define block TFM_IRQ_TEST_1_LINKER_STACK with alignment = 128, size = 0x0400 { };
#endif
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
define block TFM_SP_SECURE_CLIENT_2_LINKER_DATA with alignment = 32 {
        rw object *tfm_secure_client_2.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_SECURE_CLIENT_2_LINKER_STACK with alignment = 128, size = 0x300 { };
#endif
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_MULTI_CORE_TEST
define block TFM_SP_MULTI_CORE_TEST_LINKER_DATA with alignment = 32 {
        rw object *multi_core_test.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_MULTI_CORE_TEST_LINKER_STACK with alignment = 128, size = 0x0100 { };
#endif
#endif /* TFM_MULTI_CORE_TEST */


    /*
     * This empty, zero long execution region is here to mark the end address
     * of APP RoT RW and Stack.
     */
define block TFM_APP_RW_STACK_END with alignment = 32, size = 0 { };

#if TFM_MULTI_CORE_TOPOLOGY && defined(S_DATA_PRIV_START)
    /**** Privileged data area base address specified by multi-core platform */
define block TFM_SECURE_PRIV_DATA_BOUNDARY with size = 0 { };
#endif

#if TFM_MULTI_CORE_TOPOLOGY
    /*
     * Move BL2 shared area and MSP stack to the beginning of privileged data
     * area in multi-core topology.
     */
    /* Shared area between BL2 and runtime to exchange data */
define block TFM_SHARED_DATA with alignment = 32, size = BOOT_TFM_SHARED_DATA_SIZE { };

    /* MSP */
define block ARM_LIB_STACK_MSP with alignment = 32, size = S_MSP_STACK_SIZE { };

define overlay STACK_DATA {block TFM_SHARED_DATA};
define overlay STACK_DATA {block ARM_LIB_STACK_MSP};

    /* PSP is privileged in multi-core topology */
define block ARM_LIB_STACK with alignment = 32, size = S_PSP_STACK_SIZE { };
#endif

define block HEAP         with alignment = 8, size = S_HEAP_SIZE { };
define block ARM_LIB_HEAP with alignment = 8, size = S_HEAP_SIZE { };
define overlay HEAP_OVL {block HEAP};
define overlay HEAP_OVL {block ARM_LIB_HEAP};

define block ER_TFM_DATA          with alignment = 8 {readwrite};

    /**** PSA RoT DATA start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of PSA RoT RW and Stack.
     */
define block TFM_PSA_RW_STACK_START with alignment = 32, size = 0 { };

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
define block TFM_SP_ITS_LINKER_DATA with alignment = 32 {
        rw object *tfm_internal_trusted_storage*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_ITS_LINKER_STACK with alignment = 128, size = 0x680 { };
#endif
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_AUDIT_LOG
define block TFM_SP_AUDIT_LOG_LINKER_DATA with alignment = 32 {
        rw object *tfm_audit*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_AUDIT_LOG_LINKER_STACK with alignment = 128, size = 0 { };
#endif
#endif /* TFM_PARTITION_AUDIT_LOG */

#ifdef TFM_PARTITION_CRYPTO
define block TFM_SP_CRYPTO_LINKER_DATA with alignment = 32 {
        rw object *tfm_crypto*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_CRYPTO_LINKER_STACK with alignment = 128, size = 0x2000 { };
#endif
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
define block TFM_SP_PLATFORM_LINKER_DATA with alignment = 32 {
        rw object *tfm_platform*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_PLATFORM_LINKER_STACK with alignment = 128, size = 0x0400 { };
#endif
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
define block TFM_SP_INITIAL_ATTESTATION_LINKER_DATA with alignment = 32 {
        rw object *tfm_attest*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_INITIAL_ATTESTATION_LINKER_STACK with alignment = 128, size = 0x0A80 { };
#endif
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
define block TFM_SP_CORE_TEST_LINKER_DATA with alignment = 32 {
        rw object *tfm_ss_core_test.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_CORE_TEST_LINKER_STACK with alignment = 128, size = 0x0380 { };
#endif
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
define block TFM_SP_SECURE_TEST_PARTITION_LINKER_DATA with alignment = 32 {
        rw object *tfm_secure_client_service.*,
        rw object *test_framework*,
        rw object *uart_stdout.*,
        rw object *Driver_USART.*,
        rw object *arm_uart_drv.*,
        rw object *uart_pl011_drv.*,
        rw object *uart_cmsdk_drv*,
        rw object *secure_suites.*,
        rw object *attestation_s_interface_testsuite.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_SECURE_TEST_PARTITION_LINKER_STACK with alignment = 128, size = 0x0D00 { };
#endif
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
define block TFM_SP_IPC_SERVICE_TEST_LINKER_DATA with alignment = 32 {
        rw object *ipc_service_test.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_IPC_SERVICE_TEST_LINKER_STACK with alignment = 128, size = 0x0220 { };
#endif
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_PS
define block TFM_SP_PS_TEST_LINKER_DATA with alignment = 32 {
        rw object *tfm_ps_test_service.*,
    };

#if defined (TFM_PSA_API)
define block TFM_SP_PS_TEST_LINKER_STACK with alignment = 128, size = 0x500 { };
#endif
#endif /* TFM_PARTITION_TEST_PS */


    /*
     * This empty, zero long execution region is here to mark the end address
     * of PSA RoT RW and Stack.
     */
define block TFM_PSA_RW_STACK_END with alignment = 32, size = 0x0 { };

    /* This empty, zero long execution region is here to mark the limit address
     * of the last execution region that is allocated in SRAM.
     */
define block SRAM_WATERMARK with size = 0 { };

define block LR_CODE with fixed order {
       block ER_TFM_CODE,
       block TFM_UNPRIV_CODE,
       block TFM_PSA_CODE_START,

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
       block TFM_SP_ITS_LINKER,
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */
#ifdef TFM_PARTITION_AUDIT_LOG
       block TFM_SP_AUDIT_LOG_LINKER,
#endif /* TFM_PARTITION_AUDIT_LOG */
#ifdef TFM_PARTITION_CRYPTO
       block TFM_SP_CRYPTO_LINKER,
#endif /* TFM_PARTITION_CRYPTO */
#ifdef TFM_PARTITION_PLATFORM
       block TFM_SP_PLATFORM_LINKER,
#endif /* TFM_PARTITION_PLATFORM */
#ifdef TFM_PARTITION_INITIAL_ATTESTATION
       block TFM_SP_INITIAL_ATTESTATION_LINKER,
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */
#ifdef TFM_PARTITION_TEST_CORE
       block TFM_SP_CORE_TEST_LINKER,
#endif /* TFM_PARTITION_TEST_CORE */
#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
       block TFM_SP_SECURE_TEST_PARTITION_LINKER,
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */
#ifdef TFM_PARTITION_TEST_CORE_IPC
       block TFM_SP_IPC_SERVICE_TEST_LINKER,
#endif /* TFM_PARTITION_TEST_CORE_IPC */
#ifdef TFM_PARTITION_TEST_PS
       block TFM_SP_PS_TEST_LINKER,
#endif /* TFM_PARTITION_TEST_PS */

       block TFM_PSA_CODE_END,

/**** APPLICATION RoT RO part (CODE + RODATA) start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of APP RoT code.
     */
       block TFM_APP_CODE_START,
#ifdef TFM_PARTITION_PROTECTED_STORAGE
       block TFM_SP_PS_LINKER,
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_TEST_CORE
       block TFM_SP_CORE_TEST_2_LINKER,
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE_IPC
       block TFM_SP_IPC_CLIENT_TEST_LINKER,
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
       block TFM_IRQ_TEST_1_LINKER,
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
       block TFM_SP_SECURE_CLIENT_2_LINKER,
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_MULTI_CORE_TEST
       block TFM_SP_MULTI_CORE_TEST_LINKER,
#endif /* TFM_MULTI_CORE_TEST */

    /*
     * This empty, zero long execution region is here to mark the end address
     * of APP RoT code.
     */
       block TFM_APP_CODE_END,
       };

do not initialize  { section .noinit };
initialize by copy { readwrite };
if (isdefinedsymbol(__USE_DLIB_PERTHREAD))
{
  // Required in a multi-threaded application
  initialize by copy { section __DLIB_PERTHREAD };
}

place in S_CODE_region         { block LR_CODE };

define block DATA with fixed order {
    /**** Base address of secure data area */
   block  TFM_SECURE_DATA_START,

    /*
     * MPU on Armv6-M/v7-M core in multi-core topology may require more strict
     * alignment that MPU region base address must align with the MPU region
     * size.
     * As a result, in multi-core topology, to save memory resource and MPU
     * regions, unprivileged data sections and privileged data sections are
     * separated and gathered in unprivileged/privileged data area respectively.
     * Keep BL2 shared data and MSP stack at the beginning of the secure data
     * area in single Armv8-M topology, while move the two areas to the
     * beginning of privileged data region in multi-core topology.
     */
#ifndef TFM_MULTI_CORE_TOPOLOGY
    /* Shared area between BL2 and runtime to exchange data */
    overlay STACK_DATA,
    /* PSP is unprivileged in single-core topology */
    block ARM_LIB_STACK,
#endif

#if !defined(TFM_PSA_API)
    block TFM_SECURE_STACK,
#endif /* !defined(TFM_PSA_API) */

    block TFM_UNPRIV_DATA,

    /**** APP RoT DATA start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of APP RoT RW and Stack.
     */
    block TFM_APP_RW_STACK_START,

#ifdef TFM_PARTITION_PROTECTED_STORAGE
    block TFM_SP_PS_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_PS_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_TEST_CORE
    block TFM_SP_CORE_TEST_2_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_CORE_TEST_2_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    block TFM_SP_IPC_CLIENT_TEST_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_IPC_CLIENT_TEST_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
    block TFM_IRQ_TEST_1_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_IRQ_TEST_1_LINKER_STACK,
#endif
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    block TFM_SP_SECURE_CLIENT_2_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_SECURE_CLIENT_2_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_MULTI_CORE_TEST
    block TFM_SP_MULTI_CORE_TEST_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_MULTI_CORE_TEST_LINKER_STACK,
#endif
#endif /* TFM_MULTI_CORE_TEST */

    /*
     * This empty, zero long execution region is here to mark the end address
     * of APP RoT RW and Stack.
     */
    block TFM_APP_RW_STACK_END,

#ifdef TFM_MULTI_CORE_TOPOLOGY
#ifdef S_DATA_PRIV_START
    /**** Privileged data area base address specified by multi-core platform */
    block TFM_SECURE_PRIV_DATA_BOUNDARY,
 #endif

    /*
     * Move BL2 shared area and MSP stack to the beginning of privileged data
     * area in multi-core topology.
     */
    /* Shared area between BL2 and runtime to exchange data */
    overlay STACK_DATA,
    /* PSP is privileged in multi-core topology */
    block ARM_LIB_STACK,
#endif

    overlay HEAP_OVL,

    block ER_TFM_DATA,

    /**** PSA RoT DATA start here */
    /*
     * This empty, zero long execution region is here to mark the start address
     * of PSA RoT RW and Stack.
     */
    block TFM_PSA_RW_STACK_START,

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
    block TFM_SP_ITS_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_ITS_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_AUDIT_LOG
    block TFM_SP_AUDIT_LOG_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_AUDIT_LOG_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_AUDIT_LOG */

#ifdef TFM_PARTITION_CRYPTO
    block TFM_SP_CRYPTO_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_CRYPTO_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
    block TFM_SP_PLATFORM_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_PLATFORM_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
    block TFM_SP_INITIAL_ATTESTATION_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_INITIAL_ATTESTATION_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
    block TFM_SP_CORE_TEST_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_CORE_TEST_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    block TFM_SP_SECURE_TEST_PARTITION_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_SECURE_TEST_PARTITION_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    block TFM_SP_IPC_SERVICE_TEST_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_IPC_SERVICE_TEST_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_PS
    block TFM_SP_PS_TEST_LINKER_DATA,

#if defined (TFM_PSA_API)
    block TFM_SP_PS_TEST_LINKER_STACK,
#endif
#endif /* TFM_PARTITION_TEST_PS */

    /*
     * This empty, zero long execution region is here to mark the end address
     * of PSA RoT RW and Stack.
     */
    block TFM_PSA_RW_STACK_END,

#if 0
#if defined (S_RAM_CODE_START)
    /* Executable code allocated in RAM */
    TFM_RAM_CODE S_RAM_CODE_START {
        * (.ramfunc)
    }
#endif
#endif

    /* This empty, zero long execution region is here to mark the limit address
     * of the last execution region that is allocated in SRAM.
     */
    block SRAM_WATERMARK,

    /* Make sure that the sections allocated in the SRAM does not exceed the
     * size of the SRAM available.
     */
};

#ifndef TFM_MULTI_CORE_TOPOLOGY
    /*
     * Place the CMSE Veneers (containing the SG instruction) in a separate
     * 32 bytes aligned region so that the SAU can be programmed to
     * just set this region as Non-Secure Callable.
     */
define block LR_VENEER with alignment = 0x20, size = CMSE_VENEER_REGION_SIZE {section Veneer$$CMSE};
place at address CMSE_VENEER_REGION_START {block LR_VENEER};
#endif

    /* Reserved place for NS application.
     * No code will be placed here, just address of this region is used in the
     * secure code to configure certain HW components. This generates an empty
     * execution region description warning during linking.
     */
define block LR_NS_PARTITION with size = NS_PARTITION_SIZE { };
place at address NS_PARTITION_START { block LR_NS_PARTITION };

#ifdef BL2
    /* Reserved place for new image in case of firmware upgrade.
     * No code will be placed here, just address of this region is used in the
     * secure code to configure certain HW components. This generates an empty
     * execution region description warning during linking.
     */
define block LR_SECONDARY_PARTITION with size = SECONDARY_PARTITION_SIZE { };
place at address SECONDARY_PARTITION_START { block LR_SECONDARY_PARTITION };
#endif /* BL2 */

place in S_RAM_region          { block DATA };

define exported symbol Load$$LR$$LR_NS_PARTITION$$Base = NS_PARTITION_START; 
define exported symbol Load$$LR$$LR_VENEER$$Base = CMSE_VENEER_REGION_START;
define exported symbol Load$$LR$$LR_VENEER$$Limit = CMSE_VENEER_REGION_START + CMSE_VENEER_REGION_SIZE;