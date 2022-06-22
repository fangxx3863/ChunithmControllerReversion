#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Adafruit_MPR121.h"
#include "USB.h"
#define IR_ACTIVATION 6500    // 默认红外触发阈值(0-8191)
#define IR_SUN_ACTIVATION 2000    // 白天红外触发阈值(0-8191)
#define IR_NUN_ACTIVATION 500    // 中午红外触发阈值(0-8191)
#define IR_NIGHT_ACTIVATION 6500  // 夜晚红外触发阈值(0-8191)
#define DebugSerialDevice Serial    // 调试串口

#endif