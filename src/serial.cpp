#include "config.h"
#include "key.h"
#include <Arduino.h>
#include "EEPROM.h"
#include "USB.h"

USBCDC CommunicationSerial;

uint8_t defaultKEYS[41] = {'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                           'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                           's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ',', '.', '0',
                           '1', '2', '3', '4', '5', 'y', 'y', SLIDER_THRESHOLDS};

void communicationSerialSetup() {
    EEPROM.begin(64);
    if (EEPROM.read(63)) {
        for (int i=0; i<64; i++) {
            EEPROM.write(i, 0);
        }
        EEPROM.commit();
    }
    if (EEPROM.read(1) == 0x00 || EEPROM.read(40) == 0x00 ) {
        for (int i=0; i<41; i++) {
            EEPROM.write(i, defaultKEYS[i]);
        }
        EEPROM.commit();
    }
    CommunicationSerial.begin();
}

bool writeEEPROM() {
    uint8_t* writeKEYS = getKeys();
    for (int i=0; i<41; i++) {
        EEPROM.write(i, writeKEYS[i]);
    }
    EEPROM.commit();
    return 1;
}

bool readEEPROM() {
    uint8_t readKEYS[41];
    for (int i=0; i<41; i++) {
        readKEYS[i] = EEPROM.read(i);
        // DebugSerialDevice.println(EEPROM.read(i));
    }
    setKeys(readKEYS);
    DebugSerialDevice.print("[INFO] Read KEYS: ");
    for (int i=0; i<41; i++) {
        DebugSerialDevice.print(readKEYS[i]);
        DebugSerialDevice.print(" ");
    }
    DebugSerialDevice.println();
    DebugSerialDevice.println("[INFO] Read EEPROM OK");
    return 1;
}

String cmd;
bool setKeysMap() {
    if (CommunicationSerial.available()) {
        cmd = CommunicationSerial.readString();
        if (cmd == "SetKeys") {
            CommunicationSerial.println("KeySetReady");
            cmd = "";
            uint8_t _setKeys[41];
            while (true) {
                if (CommunicationSerial.available()) {
                    for (int i=0; i<41; i++) {
                        _setKeys[i] = CommunicationSerial.read();
                    }
                    setKeys(_setKeys);
                    writeEEPROM();
                    CommunicationSerial.println("KeySetDone");
                    break;
                }
            }
        }
        
        if (cmd == "GetKeys") {
            uint8_t* getKEYS = getKeys();
            for (int i=0; i<40; i++) {
                CommunicationSerial.write(getKEYS[i]);
                CommunicationSerial.print("/");
            }
            CommunicationSerial.print(getKEYS[40]);
            CommunicationSerial.println("/");
            cmd = "";
        }

        if (cmd == "check") {
            CommunicationSerial.println("this");
            cmd = "";
        }

        if (cmd == "Gloves") {
            ChangeMode(1);
            CommunicationSerial.println("Change to gloves");
            cmd = "";
        }

        if (cmd == "Hands") {
            ChangeMode(2);
            CommunicationSerial.println("Change to hands");
        }
    }
    return 1;
}