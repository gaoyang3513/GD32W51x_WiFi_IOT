
#==============================================================================#
# Path information
#==============================================================================#
LOCAL_DIR   := $(strip $(shell pwd))
SDK_TOP     := $(LOCAL_DIR)
CMAKE_DIR   := $(LOCAL_DIR)/.cmake

OUTPUT_DIR  ?= $(LOCAL_DIR)/output
INSTALL_DIR ?= $(LOCAL_DIR)/__install

#==============================================================================#
# Functions
#==============================================================================#

#==============================================================================#
# Variables
#==============================================================================#
MULTI_CORES ?= $(shell grep -c ^processor /proc/cpuinfo)

BUILD_ALL :=
CLEAN_ALL :=
#==============================================================================#
# Compile configure
#==============================================================================#

#==============================================================================#
# Target
#==============================================================================#
.PHONY: all $(BUILD_ALL) $(CLEAN_ALL)
all: check_env $(BUILD_ALL)
	$(MAKE) -C $(CMAKE_DIR) -j$(MULTI_CORES)

check_env:
	if [ ! -e $(CMAKE_DIR) ]; then \
		mkdir -p $(CMAKE_DIR); \
		cmake -G "Unix Makefiles" \
			-DCMAKE_TOOLCHAIN_FILE:PATH=$(SDK_TOP)/scripts/cmake/toolchain.cmake \
			-S $(LOCAL_DIR) -B $(CMAKE_DIR); \
	fi;
