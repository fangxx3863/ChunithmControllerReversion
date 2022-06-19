#include <Arduino.h>
#include "config.h"
#include "key.h"

void setup() {
    DebugSerialDevice.begin(115200);
    DebugSerialDevice.setTimeout(0);
    KeySetup();
    sliderSetup();
    Wire.setClock(3400000);
    USB.productName("ChunithmKEYS");
    USB.manufacturerName("fangxx3863");
    USB.serialNumber("2333");
    USB.begin();
}

void loop() {
    KeyCheck();
    // KeyTest();
    // KeyTest2();
    sliderScan();
}
