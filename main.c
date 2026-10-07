#include "driverlib.h"
#include "device.h"

void main(void)
{
    Device_init();          // 时钟、外设时钟、关看门狗
    Device_initGPIO();      // 解除 GPIO 配置锁

    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_enableMaster();

    // ---- LED4 = GPIO20 ----
    GPIO_setPadConfig(20, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(20, GPIO_DIR_MODE_OUT);
    GPIO_setAnalogMode(20, GPIO_ANALOG_DISABLED);   // GPIO20 上电默认模拟模式，必须切数字

    // ---- LED5 = GPIO22 ----
    GPIO_setPadConfig(22, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(22, GPIO_DIR_MODE_OUT);

    GPIO_writePin(20, 1);   // 先熄灭（板上 LED 是低电平点亮）
    GPIO_writePin(22, 1);

    for(;;)
    {
        GPIO_togglePin(20);
        GPIO_togglePin(22);
        DEVICE_DELAY_US(500000);   // 0.5 s 翻转一次 = 1 Hz
    }
}
