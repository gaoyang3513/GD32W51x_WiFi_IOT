cmake_minimum_required(VERSION 3.15)
set(APP_CFG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/app/app_cfg.h)

FILE(STRINGS ${APP_CFG_FILE} APP_ALI_CLOUD REGEX "^\#define CONFIG_ALICLOUD_SUPPORT")
FILE(STRINGS ${APP_CFG_FILE} APP_IPERF REGEX "^\#define CONFIG_IPERF_TEST")
FILE(STRINGS ${APP_CFG_FILE} APP_FATFS REGEX "^\#define CONFIG_FATFS_SUPPORT")

if (APP_ALI_CLOUD)
    MESSAGE("Support ali cloud")
    SET(CONFIG_ALICLOUD_SUPPORT ON)
endif()

if (APP_IPERF)
    SET(CONFIG_IPERF_TEST ON)
endif()

if (APP_FATFS)
    MESSAGE("Support FatFs")
    SET(CONFIG_FATFS_SUPPORT ON)
endif()

add_subdirectory(app)
add_subdirectory(bsp)
add_subdirectory(common)
add_subdirectory(network)
add_subdirectory(os)
add_subdirectory(wifi)
if (CONFIG_ALICLOUD_SUPPORT)
    add_subdirectory(cloud/alicloud)
endif()

if (CONFIG_FATFS_SUPPORT)
    add_subdirectory(FatFS)
endif()