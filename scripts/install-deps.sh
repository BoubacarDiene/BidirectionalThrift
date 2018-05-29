#!/bin/sh
ROOT=`pwd`
SRC=${ROOT}/deps
OUT=${SRC}/out

mkdir -p ${OUT}

##
## Installation failed? See:
##   https://thrift.apache.org/docs/install/debian
##   https://thrift.apache.org/docs/BuildingFromSource
##

##
########################## Common packages ##########################
##
sudo apt install -y build-essential
sudo apt install -y automake
sudo apt install -y bison
sudo apt install -y flex
sudo apt install -y g++
sudo apt install -y git
sudo apt install -y libssl-dev
sudo apt install -y libtool
sudo apt install -y make
sudo apt install -y pkg-config

##
############################### Boost ###############################
##
tar xvf ${SRC}/boost_1_67_0.tar.gz -C ${OUT}
cd ${OUT}/boost_1_67_0
./bootstrap.sh
sudo ./b2 install
cd -

##
############################## Thrift ##############################
##
tar xvf ${SRC}/thrift-0.11.0.tar.gz -C ${OUT}
cd ${OUT}/thrift-0.11.0
./bootstrap.sh
./configure --with-boost=/usr/local
make
make install
cd -

rm -rf ${OUT}
