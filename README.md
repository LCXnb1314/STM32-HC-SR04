# HC-SR04+（超声波模块）
## 基于 正点原子战舰（stm32f103zet6）

### LCXnb1314 2021.6.29
***
# 接线
HC-SR04+ 超声波测距模块与HC-SR04完全兼容，工作电压**3V-5.5V**
- **VCC：+5V**
- **Trig:Pb7**
- **Echo:Pb6**
- **GND:GND脚为此模块作为防盗模块时的开关输出量，测距模块不用此脚！！！**

# 原理
## ![原理图](https://img1.baidu.com/it/u=3720495336,2999906006&fm=26&fmt=auto&gp=0.jpg)

## 
采用IO（Trig）触发测距，给至少10us的高电平，实际40-50us效果好
有信号返回，通过IO（Echo）输出一高电平，高电平持续的时间就是超声波从发射到返回的时间

# 误差的产生与分析
## 
- 计数器的周期和计数器的最大计数值（每记一数所用时间），将是误差产生的主要原因

  TIM_TimeBaseInitStructure.TIM_Period=9999;//计数器最大寄到10000，周期0.01s，每记一数10us
	TIM_TimeBaseInitStructure.TIM_Prescaler=719;
# 注意
1. **代码只提供了主函数部分和模块部分！！！**
1. 功能：若物体靠近模块（<0.1m）灯亮，移开灯灭
