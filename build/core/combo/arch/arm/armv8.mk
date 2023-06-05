# Configuration for Linux on ARM.
# Generating binaries for the ARMv5TE architecture and higher
#

# Note: Hard coding the 'tune' value here is probably not ideal,
# and a better solution should be found in the future.
#
arch_variant_cflags := \
    -march=armv8

