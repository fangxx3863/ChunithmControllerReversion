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
    // IRAutoSetup();
    IRSetup();
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
        // KeyCheck();
        IRImproveCheck();
    }
    if (isSliderOpen()) {
        // sliderKalmanScan();       // 读MPR121原始值单片机卡尔曼滤波处理
        sliderImproveKalmanScan();   // 读MPR121原始值单片机改进BaseLine的卡尔曼滤波处理
        // sliderScanUpDown();       // 读MPR121原始值通过上升下降检测处理
    }
    setKeysMap();
    // KeyTest();
    // KeyTest2();
    // IRTest();
}
