#!/bin/bash

#set -x
#echo "Args: $@"

OUTPUT_PATH=$1
TOOLKIT=$2
TOOLKIT_PATH=$3
OUTPUT_PATH=${OUTPUT_PATH%/}
ROOT=$(realpath ${OUTPUT_PATH}/../../../../../..)

TOOLKIT=${TOOLKIT}
TOOLKIT_PATH=${TOOLKIT_PATH}

INDEX=0
SREC_CAT=/usr/bin/srec_cat

OUTPUT_FILE=nspe
OUTPUT_IMAGE_PATH=${ROOT}/scripts/images

mkdir -p ${OUTPUT_PATH}
if [ -n "$(ls ${OUTPUT_PATH}/../nspe*)" ]; then
    rm -rf ${OUTPUT_PATH}/../nspe*
fi

if [ "${TOOLKIT}" == "KEIL" ]; then
    # Generate txt for debug
     ${TOOLKIT_PATH}/ARM/ARMCC/bin/fromelf.exe --text -c -d --output=${OUTPUT_PATH}/../${OUTPUT_FILE}.txt ${OUTPUT_PATH}/${OUTPUT_FILE}.axf

    # Generate binary image
     ${TOOLKIT_PATH}/ARM/ARMCC/bin/fromelf.exe --bin --8x1 --bincombined --output=${OUTPUT_PATH}/../nspe.bin ${OUTPUT_PATH}/${OUTPUT_FILE}.axf
elif [ "${TOOLKIT}" == "IAR" ]; then
    # Generate ASM file
    ${TOOLKIT_PATH}/bin/ielfdumparm.exe ${OUTPUT_PATH}/${OUTPUT_FILE}.axf  --output ${OUTPUT_PATH}/../${OUTPUT_FILE}.asm --code

    # Generate binary image
    ${TOOLKIT_PATH}/bin/ielftool.exe ${OUTPUT_PATH}/${OUTPUT_FILE}.axf  --bin ${OUTPUT_PATH}/../${OUTPUT_FILE}.bin
elif [ "${TOOLKIT}" == "GCC" ]; then
    arm-none-eabi-objdump -xS  ${OUTPUT_PATH}/${OUTPUT_FILE}.axf   > ${OUTPUT_PATH}/../${OUTPUT_FILE}.txt
    arm-none-eabi-objcopy -Obinary ${OUTPUT_PATH}/${OUTPUT_FILE}.axf ${OUTPUT_PATH}/../${OUTPUT_FILE}.bin
fi

mkdir -p ${OUTPUT_IMAGE_PATH}
# Copy nspe.bin to the image path as ota image
cp -rf ${OUTPUT_PATH}/../nspe.bin  ${OUTPUT_IMAGE_PATH}/image-ota.bin

# concatenate mbl-ns.bin and nspe.bin
${SREC_CAT} ${OUTPUT_IMAGE_PATH}/mbl-ns.bin -Binary -offset 0 ${OUTPUT_PATH}/../nspe.bin -Binary -offset 0xa000 -fill 0xFF 0x7FFC 0xA000 -o ${OUTPUT_IMAGE_PATH}/image-all.bin -Binary

# Convert to HEX file
if [ -e ${OUTPUT_IMAGE_PATH}/image-all.bin ]; then
    ${SREC_CAT} ${OUTPUT_IMAGE_PATH}/image-all.bin -Binary -offset 0x0C000000 -o ${OUTPUT_IMAGE_PATH}/image-all.hex -Intel
fi
