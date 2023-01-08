#include <Arduino.h>
#include "config.h"
#include "key.h"
#include "vendor.h"

void setup() {
    DebugSerialDevice.begin(115200);
    DebugSerialDevice.setTimeout(0);
    // eraseEEPROM();
    EEPROMSetup();
    VendorSetup();
    KeySetup();
    sliderSetup();
    IRAutoSetup();
    readEEPROM();
    Wire.setClock(3400000);
    USB.PID(0x8222);
    USB.productName("ChunithmKEYS");
    USB.manufacturerName("fangxx3863");
    USB.serialNumber("2333");
    USB.begin();
}

void loop() {
    if (isIROpen()) {
        KeyCheck();
    }
    if (isSliderOpen()) {
        // sliderScan();        // 读MPR121处理的触摸值
        sliderRawScan();        // 读MPR121原始值单片机处理
    }
    setKeysMap();
    // KeyTest();
    // KeyTest2();
    // IRTest();
}
