#!/bin/sh

# check for sudo
if [ "$(id -u)" != "0" ]; then
    echo "Please run with sudo"
    exit 1
fi

# install dependencies
dnf update

dnf install \
    clang-format \
    ninja-build \