LOCAL_PATH := $(call my-dir)
CORE_DIR   := $(LOCAL_PATH)/../../../src

include $(CORE_DIR)/../Makefile.common

COREFLAGS := -DHAVE_STDINT_H -DHAVE_INTTYPES_H -D__LIBRETRO__

include $(CLEAR_VARS)
LOCAL_MODULE    := retro
LOCAL_SRC_FILES := $(SOURCES_CXX)
LOCAL_CXXFLAGS  := $(COREFLAGS)
LOCAL_LDFLAGS   := -Wl,-version-script=$(CORE_DIR)/../link.T
include $(BUILD_SHARED_LIBRARY)
