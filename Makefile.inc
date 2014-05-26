export CC=gcc
export CFLAGS:=-m32 -I $(PWD)/kernel/include
export LD=ld
export RM=rm
export QEMU=qemu-system-i386
export NASM=nasm
export BUILD_DIR:=$(PWD)/build
