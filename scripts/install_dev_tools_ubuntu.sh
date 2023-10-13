#!/bin/sh

# check for sudo
if [ "$(id -u)" != "0" ]; then
    echo "Please run with sudo"
    exit 1
fi

# install dependencies
apt update

apt install -y cmake clang-format ninja-build libvorbis-dev libflac-dev libfreetype-dev libopenal-dev