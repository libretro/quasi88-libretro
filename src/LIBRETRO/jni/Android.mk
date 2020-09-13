LOCAL_PATH := $(call my-dir)
BASE_DIR   := $(LOCAL_PATH)/../../..
CORE_DIR   := $(BASE_DIR)/src

INCFLAGS := -I$(CORE_DIR) \
   -I$(CORE_DIR)/snddrv/quasi88 \
   -I$(CORE_DIR)/snddrv/src \
   -I$(CORE_DIR)/snddrv/src/sound \
   -I$(CORE_DIR)/snddrv/quasi88 \
   -I$(CORE_DIR)/fmgen \
   -I$(CORE_DIR)/LIBRETRO

include $(BASE_DIR)/Makefile.common

#ROMDIR = rom/
#DISKDIR = disk/
#TAPEDIR = tape/

COREFLAGS := -DROM_DIR='"$(ROMDIR)"' -DDISK_DIR='"$(DISKDIR)"' -DTAPE_DIR='"$(TAPEDIR)"' \
   -DQUASI88_MINI -DCLIB_DECL='' -DUSE_SOUND=1 -DUSE_FMGEN=1 -DINLINE="static inline" $(INCFLAGS) -D__LIBRETRO__

include $(CLEAR_VARS)
LOCAL_MODULE    := retro
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_SRC_FILES := $(SOURCES_C) $(SOURCES_CXX)
LOCAL_CFLAGS    := $(COREFLAGS)
LOCAL_CPPFLAGS  := $(COREFLAGS)
LOCAL_CXXFLAGS  := $(COREFLAGS)
LOCAL_LDFLAGS   := -Wl,-version-script=$(BASE_DIR)/link.T
include $(BUILD_SHARED_LIBRARY)
