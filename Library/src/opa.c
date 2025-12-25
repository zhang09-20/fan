/**
 * @file      opa.c
 * @brief     OPA????
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "opa.h"

/**
 * @brief: OPA通道配置
 * @param  u8channel_P
 * @arg: OPA_PIN0: OPA正端输入通道0 (P06)
 *       OPA_PIN1: OPA正端输入通道1 (P12)
 * @param  u8channel_N
 * @arg: OPA_NIN0: OPA负端输入通道0 (P05)
 *       OPA_NIN1: OPA负端输入通道1 (P13)
 * @param  u8channel_O
 * @arg: OPA_OUT0: OPA输出通道0 (P04)
         OPA_OUT1: OPA输出通道1 (P25)
 * @note: OPA功能复用管脚和其他模拟功能管脚兼容，复用时尽量避免冲突。
 * @retval: None
 */
void OPA_ConfigChannel(uint8_t u8channel_P, uint8_t u8channel_N, uint8_t u8channel_O)
{
    switch (u8channel_P) {
    case OPA_INP0:
        PORT_SET_MUX(OPA_INP_PORT0, ANALOG_MUX_MODE);
        break;
    case OPA_INP1:
        PORT_SET_MUX(OPA_INP_PORT1, ANALOG_MUX_MODE);
        break;
    default:
        break;
    }
    switch (u8channel_N) {
    case OPA_INN0:
        PORT_SET_MUX(OPA_INN_PORT0, ANALOG_MUX_MODE);
        break;
    case OPA_INN1:
        PORT_SET_MUX(OPA_INN_PORT1, ANALOG_MUX_MODE);
    default:
        break;
    }
    switch (u8channel_O) {
    case OPA_OUT0:
        PORT_SET_MUX(OPA_OUT_PORT0, ANALOG_MUX_MODE);
        break;
    case OPA_OUT1:
        PORT_SET_MUX(OPA_OUT_PORT1, ANALOG_MUX_MODE);
    default:
        break;
    }
}