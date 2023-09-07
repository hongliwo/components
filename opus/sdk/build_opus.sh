#!/bin/bash
TOOLCHAIN_NAME=mips-linux-uclibc-gnu
USR_PATH=${PWD}
CROSS_COMPILE=${TOOLCHAIN_NAME}-
unset CC
CXX=${CROSS_COMPILE}g++
CC=${CROSS_COMPILE}gcc
STRIP=${CROSS_COMPILE}strip
MIDDLEWARE_INS_DIR=${USR_PATH}/out
PACKAGE=libopus

rm -fr ${PACKAGE}
tar xzvf ${PACKAGE}.tar.gz
pushd ${PACKAGE}
rm -rf ${MIDDLEWARE_INS_DIR}
mkdir -p ${MIDDLEWARE_INS_DIR}

CONFIG_PARAMS="--host=mipsel-linux --build=x86_64 CC=${CC} CXX=${CXX} --prefix=${MIDDLEWARE_INS_DIR}"

echo "./configure ${CONFIG_PARAMS}"

#./configure ${CONFIG_PARAMS}
./configure ${CONFIG_PARAMS} CFLAGS='-Os -ffunction-sections -fdata-sections'

make
make install
popd

${STRIP} ${MIDDLEWARE_INS_DIR}/lib/libopus.so.0.5.0
