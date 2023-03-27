TARGET_KERNEL_USE ?= 5.15

SYSTEM_KERNEL_MODULES_INCLUDE := \
    bluetooth.ko \
    btbcm.ko \
    can-dev.ko \
    cfg80211.ko \
    libarc4.ko \
    mac80211.ko \
    rfkill.ko \

# Deprecated; do not use downstream. This location only includes vendor
# modules, but system modules may be needed as dependencies
KERNEL_MODULES_PATH := \
    kernel/prebuilts/common-modules/virtual-device/$(TARGET_KERNEL_USE)/arm64

SYSTEM_KERNEL_MODULES := \
    $(foreach _ko,$(SYSTEM_KERNEL_MODULES_INCLUDE),\
        kernel/prebuilts/$(TARGET_KERNEL_USE)/arm64/$(_ko))
VENDOR_KERNEL_MODULES := $(wildcard $(KERNEL_MODULES_PATH)/*.ko)

# b/274586753: it seems that striping is needed, for now, until
# we figured out what exactly caused the problem when modules are
# not stripped
# originally, "Do not strip modules again to preserve GKI modules signature"
# but it broke snapshot boot, so strip again
# BOARD_DO_NOT_STRIP_VENDOR_RAMDISK_MODULES := true
BOARD_VENDOR_RAMDISK_KERNEL_MODULES += \
    $(SYSTEM_KERNEL_MODULES) \
    $(VENDOR_KERNEL_MODULES)

EMULATOR_KERNEL_FILE := kernel/prebuilts/$(TARGET_KERNEL_USE)/arm64/kernel-$(TARGET_KERNEL_USE)-gz
