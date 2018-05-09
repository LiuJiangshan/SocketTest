ndk-build
adb push ./libs/arm64-v8a/ddos /sdcard
adb shell su -c cp /sdcard/ddos /data/local/tmp
adb shell su -c chmod 775 /data/local/tmp/ddos
adb shell /data/local/tmp/ddos