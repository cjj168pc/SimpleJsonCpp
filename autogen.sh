#!/usr/bin/env bash

aclocal

libtoolize -f -c

autoconf

automake -a
