#include <Arduino.h>
#include <USBHID.h>

#include "USB.h"
#include "config.h"
#include "keyboardMultiple.h"

USBHIDKeyboard Keyboard;
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();
Adafruit_MPR121 capD = Adafruit_MPR121();

static int16_t ir_activation[6];
static int8_t IR_TX_PIN[6] = {33, 34, 35, 36, 37, 38};
static int8_t IR_RX_PIN[6] = {A10, A11, A12, A13, A14, A15};
const u_int8_t IR_KEYS[6] = {'0', '1', '2', '3', '4', '5'};
#define IR_COND pinval > (8192 * IR_ACTIVATION / 100)

void KeySetup() {  // 键盘与AIR初始化
    for (int i = 0; i < 6; i++) {
        pinMode(IR_TX_PIN[i], OUTPUT);
    }
    for (int i = 0; i < 6; i++) {
        pinMode(IR_RX_PIN[i], INPUT);
    }
    Keyboard.begin();
}

void KeyCheck() {  // AIR检查
    static uint32_t ir_state = 0;
    for (int i = 0; i < 6; i++) {
        digitalWrite(IR_TX_PIN[i], HIGH);
        int pinval = analogRead(IR_RX_PIN[i]);
        // DebugSerialDevice.print("IRPIN: ");
        // DebugSerialDevice.print(IR_RX_PIN[i]);
        // DebugSerialDevice.print("  IRVAL: ");
        // DebugSerialDevice.println(pinval);
        if (IR_COND) {
            if (!(ir_state & (1 << i))) {
                // DebugSerialDevice.print("IR: ");
                // DebugSerialDevice.println(i);
                Keyboard.addKey(IR_KEYS[i]);
                ir_state |= 1 << i;
            }
        } else {
            if (ir_state & (1 << i)) {
                Keyboard.delKey(IR_KEYS[i]);
                ir_state &= ~(1 << i);
            }
        }
        digitalWrite(IR_TX_PIN[i], LOW);
    }
}

uint8_t KEYS[32] = {'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ',', '.'};

void sliderSetup() {  // 触摸初始化
    while (!(capA.begin(0x5A) & capB.begin(0x5B) & capC.begin(0x5C) &
             capD.begin(0x5D))) {
        delay(500);
    }
    capA.setThreshholds(2, 1);
    capB.setThreshholds(2, 1);
    capC.setThreshholds(2, 1);
    capD.setThreshholds(2, 1);
}

void sliderScan() {  // 触摸扫描
    static uint32_t last_status = 0;
    uint32_t sensors;
    uint8_t capa_data, capb_data, capc_data, capd_data;

    capa_data = capA.touched();
    capb_data = capB.touched();
    capc_data = capC.touched();
    capd_data = capD.touched();

    sensors |= (u_int32_t)((capa_data & 0b11000000) >> 6) << 0;
    sensors |= (u_int32_t)((capa_data & 0b110000) >> 4) << 2;
    sensors |= (u_int32_t)((capa_data & 0b1100) >> 2) << 4;
    sensors |= (u_int32_t)((capa_data & 0b11) >> 0) << 6;

    sensors |= (u_int32_t)((capb_data & 0b11000000) >> 6) << 8;
    sensors |= (u_int32_t)((capb_data & 0b110000) >> 4) << 10;
    sensors |= (u_int32_t)((capb_data & 0b1100) >> 2) << 12;
    sensors |= (u_int32_t)((capb_data & 0b11) >> 0) << 14;

    sensors |= (u_int32_t)((capc_data & 0b11000000) >> 6) << 16;
    sensors |= (u_int32_t)((capc_data & 0b110000) >> 4) << 18;
    sensors |= (u_int32_t)((capc_data & 0b1100) >> 2) << 20;
    sensors |= (u_int32_t)((capc_data & 0b11) >> 0) << 22;

    sensors |= (u_int32_t)((capd_data & 0b11000000) >> 6) << 24;
    sensors |= (u_int32_t)((capd_data & 0b110000) >> 4) << 26;
    sensors |= (u_int32_t)((capd_data & 0b1100) >> 2) << 28;
    sensors |= (u_int32_t)((capd_data & 0b11) >> 0) << 30;

    static bool st = false;
    for (int i = 0; i < 32; i++) {
        if (sensors & (1 << i)) {
            st = true;
            Keyboard.addKey(KEYS[i]);
            // DebugSerialDevice.print("Press: ");
            // DebugSerialDevice.println(i + 1);
        } else {
            Keyboard.delKey(KEYS[i]);
        }
    }
    if (st) Keyboard.sendKey();
}

void KeyTest() {  // 用以测试键盘按下
    delay(1000);
    DebugSerialDevice.println("StartPressKeys");
    Keyboard.press('1');
    Keyboard.press('2');
    Keyboard.press('3');
    Keyboard.press('4');
    Keyboard.press('5');
    Keyboard.press('6');
    Keyboard.press('7');
    Keyboard.press('8');
    delay(1000);
    DebugSerialDevice.println("StopPressKeys");
    Keyboard.releaseAll();
}

void KeyTest2() {  // 用以测试原始键盘报文
    delay(1000);
    DebugSerialDevice.println("StartPressKeys");
    hid_keyboard_report60_t report;
    report.modifier = 0x00;
    report.reserved = 0x00;
    report.keycode[0] = 0x04;
    report.keycode[1] = 0x05;
    report.keycode[2] = 0x06;
    report.keycode[3] = 0x07;
    report.keycode[4] = 0x08;
    report.keycode[5] = 0x09;
    report.keycode[6] = 0x0a;
    report.keycode[7] = 0x0b;
    report.keycode[8] = 0x0c;
    report.keycode[9] = 0x0d;
    report.keycode[10] = 0x0e;
    report.keycode[11] = 0x0f;
    report.keycode[12] = 0x10;
    report.keycode[13] = 0x11;
    report.keycode[14] = 0x12;
    report.keycode[15] = 0x13;
    report.keycode[16] = 0x14;
    report.keycode[17] = 0x15;
    for (int i = 17; i < 60; i++) {
        report.keycode[i] = 0x00;
    }
    Keyboard.hidRaw(report);
    delay(1000);
    DebugSerialDevice.println("StopPressKeys");
    report.modifier = 0x00;
    report.reserved = 0x00;
    for (int i = 0; i < 60; i++) {
        report.keycode[i] = 0x00;
    }
    Keyboard.hidRaw(report);
}