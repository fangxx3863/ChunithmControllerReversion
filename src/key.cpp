#include <Arduino.h>
#include <USBHID.h>

#include <map>

#include "USB.h"
#include "config.h"
#include "keyboardMultiple.h"

USBHIDKeyboard Keyboard;
Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();
Adafruit_MPR121 capD = Adafruit_MPR121();

int IR_Activation = IR_ACTIVATION;
static int16_t ir_activation[6];
static int8_t IR_TX_PIN[6] = {33, 34, 35, 36, 37, 38};
static int8_t IR_RX_PIN[6] = {A10, A11, A12, A13, A14, A15};
uint8_t KEYS[40] = {'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    ',', '.', '0', '1', '2', '3', '4', '5', 'y', 'y'};

void KeySetup() {  // 键盘与AIR初始化
    for (int i = 0; i < 6; i++) {
        pinMode(IR_TX_PIN[i], OUTPUT);
    }
    for (int i = 0; i < 6; i++) {
        pinMode(IR_RX_PIN[i], INPUT);
    }
    Keyboard.begin();
}

void IRAutoSetup() {  // 检测环境红外强度设置触发阈值
    for (int i = 0; i < 6; i++) {
        pinMode(IR_RX_PIN[i], INPUT);
    }
    if (analogRead(A15) > 2000 && analogRead(A15) < 8000) {
        IR_Activation = IR_SUN_ACTIVATION;
        DebugSerialDevice.println("IR-->SUN_MODE");
    } else if (analogRead(A15) > 0 && analogRead(A15) < 2000) {
        IR_Activation = IR_NUN_ACTIVATION;
        DebugSerialDevice.println("IR-->NUN_MODE");
    } else {
        IR_Activation = IR_NIGHT_ACTIVATION;
        DebugSerialDevice.println("IR-->NIGHT_MODE");
    }
}

bool isIROpen() {
    if (KEYS[38] == 'y') {
        return 1;
    }
    return 0;
}

bool isSliderOpen() {
    if (KEYS[39] == 'y') {
        return 1;
    }
    return 0;
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
        if (pinval > (IR_Activation)) {
            if (!(ir_state & (1 << i))) {
                // DebugSerialDevice.print("IR: ");
                // DebugSerialDevice.println(i);
                Keyboard.addKey(KEYS[i + 32]);
                Keyboard.sendKey();
                ir_state |= 1 << i;
            }
        } else {
            if (ir_state & (1 << i)) {
                Keyboard.delKey(KEYS[i + 32]);
                Keyboard.sendKey();
                ir_state &= ~(1 << i);
            }
        }
        digitalWrite(IR_TX_PIN[i], LOW);
    }
}

bool setKeys(uint8_t keys[]) {
    memcpy(KEYS, keys, 40);
    return 1;
}

uint8_t* getKeys() { return KEYS; }

void sliderSetup() {  // 触摸初始化
    while (!(capA.begin(0x5A) & capB.begin(0x5B) & capC.begin(0x5C) &
             capD.begin(0x5D))) {
        delay(500);
    }
    capA.setThresholds(50, 50);
    capB.setThresholds(55, 50);
    capC.setThresholds(55, 50);
    capD.setThresholds(55, 50);
}

uint32_t last_status;
std::map<uint8_t, int> PKEYS;
void sliderScan() {  // 触摸扫描
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

    if (last_status != sensors) {
        for (int i = 0; i < 32; i++) {
            if (sensors & (1 << i)) {
                if (!(last_status & (1 << i))) {
                    Keyboard.addKey(KEYS[i]);
                    Keyboard.sendKey();
                    PKEYS[KEYS[i]]++;
                    // DebugSerialDevice.print("PressKEY: ");
                    // DebugSerialDevice.println(i + 1);
                }
            } else {
                // DebugSerialDevice.println(last_status, BIN);
                if (last_status & (1 << i)) {
                    PKEYS[KEYS[i]]--;
                    // DebugSerialDevice.print("ReleaseKEY: ");
                    // DebugSerialDevice.println(i + 1);
                    if (!(PKEYS[KEYS[i]])) {
                        Keyboard.delKey(KEYS[i]);
                        Keyboard.sendKey();
                    }
                }
            }
        }
        last_status = sensors;
    }
    // Keyboard.sendKey();
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

void IRTest() {
    static int loop = 0;
    loop++;
    if (loop > 400) {
        DebugSerialDevice.print("IR1: ");
        DebugSerialDevice.print(analogRead(A10));
        DebugSerialDevice.print("  IR2: ");
        DebugSerialDevice.print(analogRead(A11));
        DebugSerialDevice.print("  IR3: ");
        DebugSerialDevice.print(analogRead(A12));
        DebugSerialDevice.print("  IR4: ");
        DebugSerialDevice.print(analogRead(A13));
        DebugSerialDevice.print("  IR5: ");
        DebugSerialDevice.print(analogRead(A14));
        DebugSerialDevice.print("  IR6: ");
        DebugSerialDevice.println(analogRead(A15));
    }
}