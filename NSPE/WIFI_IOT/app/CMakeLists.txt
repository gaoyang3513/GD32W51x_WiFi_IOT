
cmake_minimum_required(VERSION 3.15)

add_library(app)

if (CONFIG_IPERF_TEST)
    if (CONFIG_STATIC_LIB_BUILDED)
        add_library(iperf3 STATIC IMPORTED GLOBAL)

        set_target_properties(iperf3
            PROPERTIES IMPORTED_LOCATION
            ${PROJECT_SOURCE_DIR}/NSPE/WIFI_IOT/lib/GCC/libiperf3.a)
    endif()
endif()

target_sources(app
    PRIVATE
        atcmd.c
        cmd_shell.c
        console.c
        main.c
    )

target_sources(app
    PRIVATE
        ../demo/iperf3_main.c
        ../demo/ota_demo.c
        ../demo/ssl_certs.c
        ../demo/ssl_client.c
        ../demo/tcp_test.c
        ../demo/udp_test.c
        ../demo/cmsis_os_demo.c
    )

if(CONFIG_GY3513)
    target_sources(app
        PRIVATE
        ../../Utilities/gd32w515p_eval.c
    )
endif(CONFIG_GY3513)

target_link_libraries(app
    gd32w51x_peripheral_api
    gd32w51x_wifi_api
    bsp_api
    common_api
    lwIP_api
    mbedtls_ssl_api
    wifi_api
    os_api
    cmsis_api
    $<$<BOOL:${CONFIG_ALICLOUD_SUPPORT}>:alicloud>
    $<$<BOOL:${CONFIG_IPERF_TEST}>:iperf3>
    $<$<BOOL:${CONFIG_IPERF_TEST}>:iperf3_api>
    $<$<BOOL:${CONFIG_FATFS_SUPPORT}>:fatfs>
    )

target_sources(app
    PRIVATE
        _build_date.h
)

if(CMAKE_HOST_UNIX)
    set(BUILD_DATE_SCRIPT ${TAGET_PROJECT_DIR}/build_date.sh)
elseif(CMAKE_HOST_WIN32)
    set(BUILD_DATE_SCRIPT ${TAGET_PROJECT_DIR}/build_date.bat)
endif()

message("Build script: ${BUILD_DATE_SCRIPT}")
add_custom_command(OUTPUT _build_date.h
    COMMAND ${BUILD_DATE_SCRIPT} ${PROJECT_SOURCE_DIR}/NSPE
)
