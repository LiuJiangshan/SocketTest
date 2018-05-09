APP_STL:=c++_static
APP_ABI:= arm64-v8a
APP_PLATFORM:=android-14
NDK_TOOLCHAIN_VERSION := clang
APP_CPPFLAGS += -std=c++11
# 开启异常控制特性
APP_CPPFLAGS += -fexceptions
