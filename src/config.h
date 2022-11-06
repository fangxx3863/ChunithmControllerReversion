#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Adafruit_MPR121.h"
#include "USB.h"
#define IR_ACTIVATION 6500              // 默认红外触发阈值(0-8191)
#define IR_SUN_ACTIVATION 1400          // 白天红外触发阈值(0-8191)
#define IR_NUN_ACTIVATION 400           // 中午红外触发阈值(0-8191)
#define IR_NIGHT_ACTIVATION 5000        // 夜晚红外触发阈值(0-8191)

#define SLIDER_THRESHOLDS 70            // 默认触摸触发阈值

#define DebugSerialDevice Serial        // 调试串口

// 开机时按下任意触摸键进入手套模式,反之进入空手模式
// 空手模式
#define PressThresholds 10             // 按下触发阈值
#define ReleaseThresholds 10           // 释放触发阈值
#define MPR121_CHARGE_CURRENT 0xF0      // 极板充电电流,设置越高灵敏度越高
#define MPR121_ENCODING_PERIOD 0x00     // 极板编码时间,具体设置见MPR121手册

// 手套模式
#define GlovesPressThresholds 3        // 手套模式按下触发阈值
#define GlovesReleaseThresholds 3      // 手套模式释放触发阈值
#define GlovesMPR121_CHARGE_CURRENT 0xFF     // 手套模式极板充电电流,设置越高灵敏度越高
#define GlovesMPR121_ENCODING_PERIOD 0x00    // 手套模式极板编码时间,具体设置见MPR121手册

#define AUTOCONFIG 0                    // 是否开启MPR121自动参数设置,0开启,1关闭

#endif