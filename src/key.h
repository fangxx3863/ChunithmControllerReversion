#include "config.h"
void KeySetup();
bool isIROpen();
bool isSliderOpen();
int calTouch(int bl, int fd);
void KeyCheck();
void KeyTest();
void KeyTest2();
uint8_t* getKeys();
bool setKeys(uint8_t keys[]);
void IRTest();
void IRAutoSetup();
void sliderSetup();
int mapRealKeys(int i);
void sliderRawScan();
void sliderKalmanScan();
void sliderImproveKalmanScan();
void sliderScanUpDown();
void ChangeMode(int i);
