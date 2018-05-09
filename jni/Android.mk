LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := ddos
LOCAL_SRC_FILES := ddos.cpp
# 成可执行的二进制文件
include $(BUILD_EXECUTABLE)
