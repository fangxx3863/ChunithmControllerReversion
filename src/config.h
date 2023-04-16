#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Adafruit_MPR121.h"
#include "USB.h"
#define IR_ACTIVATION 300                // 默认红外触发阈值(0-8191)
//#define IR_UPDOWN 200                    // 默认红外上升下降阈值(0-8191)
#define IRDEBUG 0                        // 红外调试

// ----------------------------------弃用------------------------------------------- //
#define IR_SUN_ACTIVATION 1200           // 白天红外触发阈值(0-8191)
#define IR_NUN_ACTIVATION 400            // 中午红外触发阈值(0-8191)
#define IR_NIGHT_ACTIVATION 6200         // 夜晚红外触发阈值(0-8191)
// ----------------------------------弃用------------------------------------------- //

#define SLIDER_THRESHOLDS 45             // 默认触摸触发阈值

#define DebugSerialDevice Serial         // 调试串口

// 开机时按下任意触摸键进入手套模式,反之进入空手模式
// 配置参考AN3890文档
#define SLIDERDEBUG 0                    // 滑条调试
// 空手模式
#define PressThresholds 0                // 按下触发阈值
#define ReleaseThresholds 0              // 释放触发阈值
#define MPR121_CHARGE_CURRENT 0x30       // 极板充电电流,设置越高灵敏度越高
#define MPR121_ENCODING_PERIOD 0x20      // 极板编码时间,具体设置见MPR121手册

// 手套模式
#define GlovesPressThresholds 0              // 手套模式按下触发阈值
#define GlovesReleaseThresholds 0            // 手套模式释放触发阈值
#define GlovesMPR121_CHARGE_CURRENT 0x3F     // 手套模式极板充电电流,设置越高灵敏度越高
#define GlovesMPR121_ENCODING_PERIOD 0x20    // 手套模式极板编码时间,具体设置见MPR121手册

#define AUTOCONFIG 1                         // 是否开启MPR121自动参数设置,1开启,0关闭

#endif