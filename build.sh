#!/bin/sh

apt-get install cmake g++ libasound2-dev libcurl4-gnutls-dev libgcrypt20-dev libgsm1-dev libspeex-dev libpopt-dev libsigc++-2.0-dev tcl-dev libdbus-1-dev libcurl4-gnutls-dev libjsoncpp-dev

useradd -G audio svxlink

mkdir -p src/build && cd src/build

cmake -DCMAKE_INSTALL_PREFIX=/opt/SVXLink \
      -DSYSCONF_INSTALL_DIR=/opt/SVXLink/etc \
      -DLOCAL_STATE_DIR=/opt/SVXLink/var \
      -DCMAKE_INSTALL_RPATH=/opt/SVXLink/lib \
      -DINTERNAL_SAMPLE_RATE=8000 \
      -DUSE_GPROF=NO \
      -DUSE_QT=NO \
      -DUSE_OSS=NO \
      ..

make -j16 install
