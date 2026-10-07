# C2000-F280039C-LED-Blink
LAUNCHXL-F280039C GPIO LED闪烁例程
LAUNCHXL-F280039C（TMS320F280039C）GPIO LED 闪烁例程，DSP 学习计划 W1 的第一个实验。

## 目标
用 C2000Ware DriverLib 配置 GPIO，让板上两颗用户 LED 以 1 Hz 同步闪烁，
并跑通 CCS 的编译 → 下载 → 调试完整流程。

## 硬件
- LAUNCHXL-F280039C（板载 XDS110 调试器）
- LED4 → GPIO20，LED5 → GPIO22，低电平点亮

## 关键点
- `Device_init()` + `Device_initGPIO()`（后者解除 GPIO 配置锁，不能省）
- `GPIO_setAnalogMode(20, GPIO_ANALOG_DISABLED)`：GPIO20 上电默认是模拟模式
- 主循环 `GPIO_togglePin()` + `DEVICE_DELAY_US(500000)` → 1 Hz

## 遇到的问题与解决
1. Test Connection 报 `SC_ERR_PATH_BROKEN (-233)`：目标配置器件选错，且 TCLK 需固定为 1 MHz
2. 调试启动卡在 45%：工程实际用的是 Flash 链接文件，每次调试都在擦写 Flash；
   改用 RAM 链接文件 `28003x_generic_ram_lnk.cmd` 后秒启动
3. LED 不亮：GPIO20 上电默认模拟模式，需显式切回数字模式

## 环境
CCS 12.1.0 / C2000Ware 5.04.00.00 / C2000 编译器 v22.6.0
构建配置：RAM 链接，JTAG TCLK 1 MHz

## 依赖与编译说明
本仓库只包含本人编写的代码与工程配置，不含 TI 的 SDK 文件。

编译步骤：
1. 安装 CCS 12.x + C2000Ware 5.04
2. 新建一个 C2000 工程（器件选 TMS320F280039C），
   把 C2000Ware 的 `device_support/f28003x/` 与 `driverlib/f28003x/` 复制到工程目录
3. 用本仓库的 `main.c`、`F280039_ram_lnk.cmd`、`targetConfigs/` 覆盖对应文件
4. Ctrl+B 编译，F11 下载
