#!/bin/sh

# check for sudo
if [ "$(id -u)" != "0" ]; then
    echo "Please run with sudo"
    exit 1
fi

# install dependencies
apt update

# the x11 packages are needed for the github actions
apt install -y cmake ninja-build libvorbis-dev libflac-dev libfreetype-dev libopenal-dev libx11-dev libxrandr-dev libxcursor-dev mesa-common-dev libudev-dev