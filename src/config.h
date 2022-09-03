#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Adafruit_MPR121.h"
#include "USB.h"
#define IR_ACTIVATION 6500    // 默认红外触发阈值(0-8191)
#define IR_SUN_ACTIVATION 1800    // 白天红外触发阈值(0-8191)
#define IR_NUN_ACTIVATION 500    // 中午红外触发阈值(0-8191)
#define IR_NIGHT_ACTIVATION 6500  // 夜晚红外触发阈值(0-8191)
#define DebugSerialDevice Serial    // 调试串口
#define PressThresholds 45          // 按下触发阈值
#define ReleaseThresholds 45        // 释放触发阈值
#define MPR121_CHARGE_CURRENT 0x18      // 极板充电电流,设置越高灵敏度越高
#define MPR121_ENCODING_PERIOD 0x40     // 极板编码时间,具体设置见MPR121手册


#endif