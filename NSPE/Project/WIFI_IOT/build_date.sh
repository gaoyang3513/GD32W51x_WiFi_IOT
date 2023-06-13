#!/bin/bash

DIR=$1

echo "/* Do not change the content here, it's auto generated */" > ${DIR}/WIFI_IOT/common/_build_date.h
echo "#define BUILD_DATE \"$(date  +"%Y/%m/%d %H:%M")\""        >> ${DIR}/WIFI_IOT/common/_build_date.h
echo "#define DATE_GENERATED"                                   >> ${DIR}/WIFI_IOT/common/_build_date.h
