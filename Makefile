# Makefile
# Created by Matheus Leme Da Silva

SOURCEDIR := $(CURDIR)/Source
BUILDDIR := $(CURDIR)/Build
BINDIR := $(BUILDDIR)/Bin
OBJDIR := $(BUILDDIR)/Obj
DEPDIR := $(BUILDDIR)/Dep

SFDISK := /sbin/sfdisk
NASM := nasm
QEMU := QEMU_AUDIO_DRV=pa qemu-system-i386
MKFS := /sbin/mkfs.fat

IMAGE_SIZE := 16M
IMAGE_FAT := 16
IMAGE := $(BUILDDIR)/Quark.img

QEMU_FLAGS := -drive file=$(IMAGE),if=ide,format=raw,media=disk -m 16M
BOOTLOADER := $(BINDIR)/Bootload.bin

.PHONY: all
all: $(IMAGE)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: qemu
qemu: $(IMAGE)
	$(QEMU) $(QEMU_FLAGS)

# IMAGE =======================================================================

$(IMAGE): $(BOOTLOADER)
	mkdir -p $(dir $@)
	dd if=/dev/zero of=$@ bs=512 count=63 status=progress
	dd if=$(BOOTLOADER) of=$@ bs=1 status=progress conv=notrunc
	dd if=/dev/zero of=$(basename $@).p1 bs=$(IMAGE_SIZE) count=1 status=progress
	$(MKFS) -F $(IMAGE_FAT) -n "QUARK" $(basename $@).p1
	dd if=$(basename $@).p1 >> $@
	echo "label:dos\n63,$(IMAGE_SIZE),0E,*\n" | $(SFDISK) $@

# BOOTLOADER ==================================================================

include Bootload.mk

