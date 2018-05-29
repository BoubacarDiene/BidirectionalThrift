#!/bin/sh
ROOT=`pwd`
OUT=${ROOT}/src/generated
SRC=${ROOT}/idl

mkdir -p ${OUT}

for IDL in ${SRC}/*
do
    thrift --gen cpp --out ${OUT} ${IDL}
done
