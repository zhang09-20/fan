/**
 * @file      main.c
 * @brief     project master function
 * @author    Way-On MCU Application Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "application.h"
#include "bldc.h"
#include "pid.h"

/**
 * execute bldc motor controller main loop program.
 */
int main(void)
{
    PWMD1L = 0;
    PWMD1H = 0;

    motor_init_param();
    motor_init_periph();

    // 自定义初始化
    Systerm_Init();

    //    uart_config();
    while (1) {

        // 电机驱动
        motor_work();

        // 应用层
        if (Flag_5ms == 1) {
            Flag_5ms = 0;
            application();
        }
    }
}
