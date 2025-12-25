/**
 * @file      config.h
 * @brief     CONFIG驱动配置
 * @author   Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
 * @brief 使能调试功能
 * @return 0: 执行成功
 *         1: 执行失败
 * @note 如果需要禁用调试功能，可在keil的settings界面配置
 */
uint8_t CONFIG_Enable_OCD(void);

#define OCD_ENABLE CONFIG_Enable_OCD()

#endif /* __CONFIG_H__ */
