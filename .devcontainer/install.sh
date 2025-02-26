#!/usr/bin/env bash

cd /tmp
curl -L https://github.com/skvadrik/re2c/archive/refs/tags/3.1.tar.gz > re2c-3.1.tar.gz
tar xf re2c-3.1.tar.gz
cd re2c-3.1
autoreconf -i -W all
./configure
make
make install
