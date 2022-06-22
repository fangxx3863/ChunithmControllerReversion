#include "config.h"
#include "key.h"
#include <Arduino.h>
#include "EEPROM.h"
#include "USB.h"

USBCDC CommunicationSerial;

uint8_t defaultKEYS[38] = {'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                           'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                           's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ',', '.', '0',
                           '1', '2', '3', '4', '5'};

void communicationSerialSetup() {
    EEPROM.begin(64);
    if (EEPROM.read(63)) {
        for (int i=0; i<64; i++) {
            EEPROM.write(i, 0);
        }
        EEPROM.commit();
    }
    if (EEPROM.read(1) == 0x00) {
        for (int i=0; i<38; i++) {
            EEPROM.write(i, defaultKEYS[i]);
        }
        EEPROM.commit();
    }
    CommunicationSerial.begin();
}

bool writeEEPROM() {
    uint8_t* writeKEYS = getKeys();
    for (int i=0; i<38; i++) {
        EEPROM.write(i, writeKEYS[i]);
    }
    EEPROM.commit();
    return 1;
}

bool readEEPROM() {
    uint8_t readKEYS[38];
    for (int i=0; i<38; i++) {
        readKEYS[i] = EEPROM.read(i);
        // DebugSerialDevice.println(EEPROM.read(i));
    }
    setKeys(readKEYS);
    return 1;
}

String cmd;
bool setKeysMap() {
    if (CommunicationSerial.available()) {
        cmd = CommunicationSerial.readString();
        if (cmd == "SetKeys") {
            CommunicationSerial.println("KeySetReady");
            cmd = "";
            uint8_t _setKeys[38];
            while (true) {
                if (CommunicationSerial.available()) {
                    for (int i=0; i<38; i++) {
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
            for (int i=0; i<38; i++) {
                CommunicationSerial.write(getKEYS[i]);
                CommunicationSerial.print("/");
            }
            CommunicationSerial.println();
            cmd = "";
        }
        if (cmd == "check") {
            CommunicationSerial.println("this");
        }
    }
    return 1;
}