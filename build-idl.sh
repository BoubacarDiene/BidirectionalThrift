#!/bin/sh
out=src/generated
src=idl

mkdir -p ${out}

for idl in ${src}/*
do
    thrift --gen cpp --out ${out} ${idl}
done
