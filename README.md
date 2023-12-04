# Remote-control-handle

基于 nRF24L01 模块的远距离通讯以及遥控

## 1. 项目介绍

本项目是 2.4G 远距离遥控器的制作，基于 `Arduino` 框架开发。

模型使用的是`soildworks`制作。

## 2. 项目结构

- **code** 代码
- **lib** 库
- **part** 模型部件
- **assembly** 模型装配体
- **stl** 打印模型

## 3. 模型介绍

模型灵感来源于在 Youtube 上看到一位博主自制的遥控器，比较感兴趣，所以参考了一下他的模型

有兴趣的可以去看一看这个视频，链接如下

[Making a 2400 meters LONG RANGE 8-Channel & Digital Trim Radio Control For RC Models](https://www.youtube.com/watch?v=RSDfMaanKXM&list=WL)

### 3.1 模型设计思路

为了更加贴切于航模遥控器和满足人体工程学，制作的还是最简单的盒子式的遥控器。

也是为了方便后期电路的布局不允许正常布线，模型制作的比较简单。

应各位同仁爱好，使用主题颜色使用的粉色和灰色，更加符合我们技术部的猛男特色。

### 3.2 模型视图

- #### 整体视图

<img src="images/../image/1.png" alt="NRF24L01" width="500"/>

- #### 正面视图

<img src="images/../image/2.png" alt="NRF24L01" width="500"/>

- #### 背面视图（透视）

<img src="images/../image/3.png" alt="NRF24L01" width="500"/>

以上三种视图展示了模型整体的结构和各个原件的布局

### 3.3 模型爆炸视图

https://github.com/ptsfdtz/Remote-control-handle/assets/148436840/ea57b409-a363-41d5-a612-20af8ce92d28

展示拆分细节

## 4. 电路部分

### 4.1 模块使用

我使用的是`nRF24L01+PA/LNA`的版本，除了天线外，它还有一个 RFX2401C 芯片，包括 PA（功率放大器）和 LNA（低噪声放大器）。 这放大了 NRF24L01 信号，并在开放空间中实现了长达 1000 米的更好传输范围。

以下是`NRF24L01`引脚排列以及 `NRF24L01+ PA/LNA` 模块的详细介绍。

<img src="images/../image/NRF24L01.jpg" alt="NRF24L01" width="500"/>

发射端我们使用的是`arduino nano`
