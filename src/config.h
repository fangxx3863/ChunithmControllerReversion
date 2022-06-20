#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Adafruit_MPR121.h"
#include "USB.h"
#define IR_ACTIVATION 80    // 默认红外触发阈值(0-99)
#define IR_SUN_ACTIVATION 10    // 白天红外触发阈值(0-99)
#define IR_NIGHT_ACTIVATION 80  // 夜晚红外触发阈值(0-99)
#define DebugSerialDevice Serial    // 调试串口

#endif