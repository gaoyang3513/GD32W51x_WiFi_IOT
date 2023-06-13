#!/bin/bash

#set -x
#echo "Args: $@"

OUTPUT_PATH=$1
OUTPUT_NAME=$2
TOOLKIT=$3
TOOLKIT_PATH=$4
OUTPUT_PATH=${OUTPUT_PATH%/}

ROOT=$(realpath ${OUTPUT_PATH}/../../../../..)
SREC_CAT=/usr/bin/srec_cat
OUTPUT_IMAGE_PATH=${ROOT}/scripts/images

if [ "${TOOLKIT}" == "KEIL" ]; then
    # Generate txt for debug
    ${TOOLKIT_PATH}/ARM/ARMCC/bin/fromelf.exe --text -c -d --output=${OUTPUT_PATH}/../${OUTPUT_NAME}.txt ${OUTPUT_PATH}/${OUTPUT_NAME}.axf
    # Generate binary image
    %TOOLKIT_PATH%/ARM/ARMCC/bin/fromelf.exe --bin --8x1  --bincombined --output=${OUTPUT_PATH}/../${OUTPUT_NAME}.bin ${OUTPUT_PATH}/${OUTPUT_NAME}.axf
elif [ "${TOOLKIT}" == "IAR" ]; then
    # Generate ASM file
    %TOOLKIT_PATH%/bin/ielfdumparm.exe ${OUTPUT_PATH}/${OUTPUT_NAME}.axf  --output ${OUTPUT_PATH}/../${OUTPUT_NAME}.asm --code
    # Generate binary image
    %TOOLKIT_PATH%/bin/ielftool.exe ${OUTPUT_PATH}/${OUTPUT_NAME}.axf  --bin ${OUTPUT_PATH}/../${OUTPUT_NAME}.bin
elif [ "${TOOLKIT}" == "GCC" ]; then
    arm-none-eabi-objdump -xS  ${OUTPUT_PATH}/${OUTPUT_NAME}.axf   > ${OUTPUT_PATH}/../${OUTPUT_NAME}.txt
    arm-none-eabi-objcopy -Obinary ${OUTPUT_PATH}/${OUTPUT_NAME}.axf ${OUTPUT_PATH}/../${OUTPUT_NAME}.bin
fi

mkdir -p ${OUTPUT_IMAGE_PATH}
if [ -n "$(ls ${OUTPUT_IMAGE_PATH}/${OUTPUT_NAME}*)" ]; then
    rm -rf ${OUTPUT_IMAGE_PATH}/${OUTPUT_NAME}*
fi

# Copy to output image path
cp ${OUTPUT_PATH}/../${OUTPUT_NAME}.bin ${OUTPUT_IMAGE_PATH}
# Generate Hex file
${SREC_CAT}  ${OUTPUT_IMAGE_PATH}/${OUTPUT_NAME}.bin -Binary -offset 0x0C000000 -o ${OUTPUT_IMAGE_PATH}/${OUTPUT_NAME}.hex -Intel

