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
### 滑条焊接  
#### 最右边主控板
1. 将所有焊点涂上焊膏,注意量不要太多  
2. 使用立创专业版的辅助焊接工具对照3D预览将除了TypeC,按钮,拨码开关,Mpr121以外的的元件全部用镊子小心放置于焊盘上  
3. `注意`印有JP丝印的元件位请用0R电阻,最右边的主控板请将0x5A用0R填充  
4. 将PCB移至加热台加热,待焊锡融化后用镊子将未归位的元件推齐  
5. 用镊子把Mpr121位置的多余焊膏去掉,对准位置小心的将Mpr121放置于焊盘上,待自动归位后稍微向下压一压  
6. 完成后将电路板放于地板加速冷却
7. 接着打开烙铁,用刀头将Mpr121周围多余焊锡拖干净,如果拖不干净可以加一点焊宝或者松香
8. 焊接两个复位开关,注意温度最好不要超过300度,因为底部是塑料
9. 在TypeC焊盘上涂一条焊膏,然后对准定位孔把TypeC母座放上去,再在引脚上涂一条焊膏
10. 用烙铁刀头轻挨TypeC母座引脚,待焊锡融化,注意千万不要怼着后面的塑料焊,会融化TypeC母座
11. 至此右侧主控板焊接完成

#### 左边3块主控板  
1. 步骤如上
2. 只需要焊接5P插座,AMS1117及其输入输出电容,Mpr121及其外围(75K,100nF)
3. 注意Mpr121地址选择点请从右到左依次使用0R填充0x5B,0x5C,0x5D

#### 供参考的完成后的图片   
![-495ddbc46826c114](https://user-images.githubusercontent.com/48589001/175773574-3582a1a7-644c-4c94-888d-0baa1c2bde74.jpg)

### 切割  
由于嘉立创免费打板10x10的限制,天键打样后需自行切割
#### 步骤  
1. 使用电磨,锉刀,钳子等工具沿着开槽区域切开  
2. 使用砂纸将切口打磨平整  
3. 用M3螺丝螺母将两块切割出来的板固定起来  
4. 将链接位置填上焊锡(TX_,RX_的焊盘)  
5. 一共需要6片,所以需重复3次以上步骤  

#### 供参考的完成后的图片  
![image](https://user-images.githubusercontent.com/48589001/175773887-1db5d24e-37e9-4a01-ae09-b537d3138cfe.png)

### 天键焊接  
天键的TX,RX做在了一块板子上,焊接要分开来做
#### 步骤  
1. 焊接TX板
2. 请只焊接如图的元件,注意LED不要接反(长腿正)  

3. 焊接RX板
4. 请只焊接如图的元件,注意LED不要接反(长腿对应丝印二极管正极)  

5. 焊接8P排线

|TX板|RX板|
|--|--|
| ![image](https://user-images.githubusercontent.com/48589001/175774249-f796644b-7e97-4a42-ba95-194261c5f39f.png)  | ![image](https://user-images.githubusercontent.com/48589001/175774557-cf5d54c1-225d-42f8-a84e-1c6afd232392.png) |

#### 供参考的完成后的图片  
|||
|--|--|
| ![IMG_20220625_210555](https://user-images.githubusercontent.com/48589001/175774754-1382e351-0c62-4e46-b387-3400e5231a4f.jpg) | ![IMG_20220625_210607](https://user-images.githubusercontent.com/48589001/175774760-62d6334d-a372-413a-8dae-9a8e012174cc.jpg) |

### 组装  
将所有物品至于基板上(基板可以是亚克力,ABS,~~或者日历硬纸皮~~)
#### 步骤  
1. 从右到左依次把0x5A-0x5D的主控板拼接  
2. 用M2铜柱加上M2螺丝固定
3. 连接TX,RX排线
4. 切割基板并把主控板粘在基板上
5. 用角码固定天键

### 程序  
克隆本项目并用PIO打开  
连接SERIAL的USB接口,点击上传图标,等待上传完成即可  
键盘映射请参考[此目录下的SegaTools](https://github.com/fangxx3863/ChunithmControllerReversion/tree/main/extra)  

### 后记  
Mpr121已调参至可以使用手套触摸  
祝各位早日AJ!!!  
![IMG_20220619_225755](https://user-images.githubusercontent.com/48589001/175777178-d6c7cfee-5464-4fc4-aea8-1edbff9c0c26.jpg)


# 配套上位机改键软件 
https://github.com/fangxx3863/ChunithmControllerReversionHost
![image](https://user-images.githubusercontent.com/48589001/174819279-b126e2a4-ecf0-4bac-9959-3cc2d2d13013.png)
