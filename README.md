# ChunithmControllerReversion  
低成本Chunithm控制器(仅80RMB)
![01c451d0c26c28da0fa7c66af54b895](https://user-images.githubusercontent.com/48589001/174531189-dbdf7255-bfd1-4cbe-8069-07f8f9f01af1.jpg)

# 注意  
工程使用PlatformIO配合ESP32S2的ArduinoFramework进行开发,构建源码前请先下载VSCode并安装PlatformIO插件  
请尽量在PlatformIO下载框架文件时保持科学上网连接,避免下载出错造成不必要的时间浪费  

# DIY制作指南  
**本项目全部元件均使用贴片件,有一定的焊接难度,请准备好适合的工具**  

## 准备工具及材料  
### 工具  
1. 一把合适的烙铁,推荐T12(不要弄那些几十块的那种来焊,你会自闭的)  
2. 加热台,买淘宝那种十几块的LED拆焊台即可  
3. 热风枪(非必须)
4. 电磨(非必须)
5. 万用表
6. 镊子

### 材料  
1. 有铅中温锡膏(用以焊接贴片元件)
2. 助焊剂/焊宝/松香(辅助焊接)
3. 砂纸(辅助打磨天键PCB)
4. 打样主控PCB
5. 打样天键PCB
6. [此目录下的元件](https://github.com/fangxx3863/ChunithmControllerReversion/tree/main/extra)

## 开始制作  
### 焊接  
#### 最右边主控板
1. 将所有焊点涂上焊膏,注意量不要太多  
2. 使用立创专业版的辅助焊接工具对照3D预览将除了TypeC,按钮,拨码开关,Mpr121以外的的元件全部用镊子小心放置于焊盘上  
3. `注意`印有JP丝印的元件位请用0R电阻,最右边的主控板请将0x5A用0R填充  
4. 将PCB移至加热台加热,待焊锡融化后用镊子将未归位的元件推齐  
5. 用镊子把Mpr121位置的多余焊膏去掉,对准位置小心的将Mpr121放置于焊盘上,待自动归位后稍微向下压一压  
6. 完成后将电路板放于地板加速冷却

# 配套上位机改键软件 
https://github.com/fangxx3863/ChunithmControllerReversionHost
![image](https://user-images.githubusercontent.com/48589001/174819279-b126e2a4-ecf0-4bac-9959-3cc2d2d13013.png)
