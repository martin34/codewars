#!/bin/bash 

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

qemu-img create -f qcow2 $SCRIPTPATH/ubuntu-20.04.1-desktop-amd64.qcow2 10G

qemu-system-x86_64 \
  -m 2048 \
  -vga virtio \
  -show-cursor \
  -usb \
  -device usb-tablet \
  -enable-kvm \
  -cdrom $SCRIPTPATH/ubuntu-20.04.1-desktop-amd64.iso \
  -drive file=$SCRIPTPATH/ubuntu-20.04.1-desktop-amd64.qcow2,if=virtio \
  -cpu host

  # -accel hvf \

