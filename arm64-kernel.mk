TARGET_KERNEL_USE ?= 6.1

KERNEL_ARTIFACTS_PATH := kernel/prebuilts/$(TARGET_KERNEL_USE)/arm64

VIRTUAL_DEVICE_KERNEL_MODULES_PATH := \
    kernel/prebuilts/common-modules/virtual-device/$(TARGET_KERNEL_USE)/arm64

# The list of modules to reach the second stage. For performance reasons we
# don't want to put all modules into the ramdisk.
RAMDISK_KERNEL_MODULES := \
    virtio_blk.ko \
    virtio_console.ko \
    virtio_dma_buf.ko \
    virtio_mmio.ko \
    virtio_pci.ko \
    virtio_pci_legacy_dev.ko \
    virtio_pci_modern_dev.ko \
    virtio-rng.ko \
    vmw_vsock_virtio_transport.ko \

BOARD_SYSTEM_KERNEL_MODULES := $(wildcard $(KERNEL_ARTIFACTS_PATH)/*.ko)

BOARD_VENDOR_RAMDISK_KERNEL_MODULES := \
    $(patsubst %,$(VIRTUAL_DEVICE_KERNEL_MODULES_PATH)/%,$(RAMDISK_KERNEL_MODULES))

BOARD_VENDOR_KERNEL_MODULES := \
    $(filter-out $(BOARD_VENDOR_RAMDISK_KERNEL_MODULES),\
                 $(wildcard $(VIRTUAL_DEVICE_KERNEL_MODULES_PATH)/*.ko))

BOARD_VENDOR_KERNEL_MODULES_BLOCKLIST_FILE := \
    device/generic/goldfish/kernel_modules.blocklist

EMULATOR_KERNEL_FILE := $(KERNEL_ARTIFACTS_PATH)/kernel-$(TARGET_KERNEL_USE)-gz
