/**
 * @file      spi.h
 * @brief     SPI驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "WY8S9003xx.h"

/**@name SPI配置寄存器-SPICFG
 * @{
 */
#define SPI_SPICFG_EN_POS      (7)
#define SPI_SPICFG_EN_MSK      (0x1 << SPI_SPICFG_EN_POS)
#define SPI_SPICFG_MS_POS      (6)
#define SPI_SPICFG_MS_MSK      (0x1 << SPI_SPICFG_MS_POS)
#define SPI_SPICFG_OENMST_POS  (5)
#define SPI_SPICFG_OENMST_MSK  (0x1 << SPI_SPICFG_OENMST_POS)
#define SPI_SPICFG_MSB_POS     (4)
#define SPI_SPICFG_MSB_MSK     (0x1 << SPI_SPICFG_MSB_POS)

#define ENABLE_SPI             (SPICFG |= SPI_SPICFG_EN_MSK)  /*!< 使能SPI */
#define DISABLE_SPI            (SPICFG &= ~SPI_SPICFG_EN_MSK) /*!< 禁止SPI */

#define SPI_SLAVE_NSSI         (0)                            /*!< SPI设置为从机，引脚NSS为输入，作从机的片选信号 */
#define SPI_MULTI_MASTER_NSSI  (2)                            /*!< SPI设置为主机且多主机，引脚NSS为输入 */
#define SPI_SINGLE_MASTER_NSSO (3)                            /*!< SPI设置为单主机，引脚NSS为输出 */
/**
 * SPI工作模式选择
 * @param[in] status SPI_SLAVE_NSSI、SPI_MULTI_MASTER_NSSI、SPI_SINGLE_MASTER_NSSO的高bit
 */
#define SPI_SPICFG_MS_SET(status) (SPICFG = ((SPICFG & (~SPI_SPICFG_MS_MSK)) | ((status) << SPI_SPICFG_MS_POS)))
/**
 * SPI工作模式配置
 * @param[in] status SPI_SLAVE_NSSI、SPI_MULTI_MASTER_NSSI、SPI_SINGLE_MASTER_NSSO的低bit
 */
#define SPI_SPICFG_OENMST_SET(status)                                                                                  \
    (SPICFG = ((SPICFG & (~SPI_SPICFG_OENMST_MSK)) | ((status) << SPI_SPICFG_OENMST_POS)))

#define SPI_LSB_MODE (1)
#define SPI_MSB_MODE (0)
/**
 * 传输起始位配置
 * @param[in] status
 * -# SPI_MSB_MODE:从最高位开始传输
 * -# SPI_LSB_MODE:从最低位开始传输
 */
#define SPI_SPICFG_MSB_SET(status) (SPICFG = ((SPICFG & (~SPI_SPICFG_MSB_MSK)) | ((status) << SPI_SPICFG_MSB_POS)))
/**@} */

/**@name SPI模式寄存器-SPIMOD
 * @{
 */
#define SPI_SPIMOD_CPOL_POS (5)
#define SPI_SPIMOD_CPOL_MSK (0x1 << SPI_SPIMOD_CPOL_POS)
#define SPI_SPIMOD_CPHA_POS (4)
#define SPI_SPIMOD_CPHA_MSK (0x1 << SPI_SPIMOD_CPHA_POS)
#define SPI_SPIMOD_PM_POS   (0)
#define SPI_SPIMOD_PM_MSK   (0x7 << SPI_SPIMOD_PM_POS)

#define SPI_MODE0           (0)
#define SPI_MODE1           (1)
#define SPI_MODE2           (2)
#define SPI_MODE3           (3)
/**
 * SPI工作模式配置位，与CPHA共同作用
 * @param[in] status SPI_MODE0、SPI_MODE1、SPI_MODE2、SPI_MODE3高bit
 */
#define SPI_SPIMOD_CPOL_SET(status) (SPIMOD = ((SPIMOD & (~SPI_SPIMOD_CPOL_MSK)) | ((status) << SPI_SPIMOD_CPOL_POS)))
/**
 * SPI工作模式配置位，与CPOL共同作用
 * @param[in] status SPI_MODE0、SPI_MODE1、SPI_MODE2、SPI_MODE3低bit
 */
#define SPI_SPIMOD_CPHA_SET(status) (SPIMOD = ((SPIMOD & (~SPI_SPIMOD_CPHA_MSK)) | ((status) << SPI_SPIMOD_CPHA_POS)))

#define SPI_DIV_2                   (0x00)
#define SPI_DIV_4                   (0x01)
#define SPI_DIV_8                   (0x02)
#define SPI_DIV_16                  (0x03)
#define SPI_DIV_32                  (0x04)
#define SPI_DIV_64                  (0x05)
#define SPI_DIV_128                 (0x06)
#define SPI_DIV_256                 (0x07)
/**
 * PWM SCK分频系数
 * @param[in] mode
 * -# SPI_DIV_2   系统时钟CLK_P/2分频
 * -# SPI_DIV_4   系统时钟CLK_P/4分频
 * -# SPI_DIV_8   系统时钟CLK_P/8分频
 * -# SPI_DIV_32  系统时钟CLK_P/32分频
 * -# SPI_DIV_64  系统时钟CLK_P/64分频
 * -# SPI_DIV_128 系统时钟CLK_P/128分频
 * -# SPI_DIV_256 系统时钟CLK_P/256分频
 */
#define SPI_DIV_SET(div) (SPIMOD = ((SPIMOD & (~SPI_SPIMOD_PM_MSK)) | ((div) << SPI_SPIMOD_PM_POS)))
/**@} */

/**@name SPI状态寄存器-SPISR
 * @{
 */
#define SPI_SPISR_IF_POS  (7)
#define SPI_SPISR_IF_MSK  (0x1 << SPI_SPISR_IF_POS)
#define SPI_SPISR_MME_POS (6)
#define SPI_SPISR_MME_MSK (0x1 << SPI_SPISR_MME_POS)
#define SPI_SPISR_WOL_POS (5)
#define SPI_SPISR_WOL_MSK (0x1 << SPI_SPISR_WOL_POS)
#define SPI_SPISR_OVF_POS (4)
#define SPI_SPISR_OVF_MSK (0x1 << SPI_SPISR_OVF_POS)
/**
 * 传输完成标志
 * @return 1:SPI传输完成\n
 *         0:SPI传输未完成
 * @note 该位硬件自动置位
 */
#define IS_SPI_IF_FLAG ((SPISR & SPI_SPISR_IF_MSK) >> SPI_SPISR_IF_POS)
/**
 * 清除传输完成标志
 */
#define CLR_SPI_IF_FLAG (SPISR &= ~SPI_SPISR_IF_MSK)
/**
 * 模式故障标志
 * @return 1:产生模式故障\n
 *         0:未发生模式故障
 * @note 该位硬件自动置位
 */
#define IS_SPI_MME_FLAG ((SPISR & SPI_SPISR_MME_MSK) >> SPI_SPISR_MME_POS)
/**
 * 清除模式故障标志
 */
#define CLR_SPI_MME_FLAG (SPISR &= ~SPI_SPISR_MME_MSK)
/**
 * 写冲突位标志
 * @return 1:产生写冲突\n
 *         0:未发生写冲突
 * @note 该位硬件自动置位
 */
#define IS_SPI_WOL_FLAG ((SPISR & SPI_SPISR_WOL_MSK) >> SPI_SPISR_WOL_POS)
/**
 * 清除写冲突位标志
 */
#define CLR_SPI_WOL_FLAG (SPISR &= ~SPI_SPISR_WOL_MSK)
/**
 * 缓存溢出标志位
 * @return 1:产生缓存溢出\n
 *         0:未发生缓存溢出
 * @note 该位硬件自动置位
 */
#define IS_SPI_OVF_FLAG ((SPISR & SPI_SPISR_OVF_MSK) >> SPI_SPISR_OVF_POS)
/**
 * 清除缓存溢出标志位
 */
#define CLR_SPI_OVF_FLAG (SPISR &= ~SPI_SPISR_OVF_MSK)
/**@} */

/**
 * SPITDR写入数据
 * @param[in] u8data 写入的数据
 */
#define SPI_WRITE_SPITDR(u8data) (SPITDR = (u8data))
/**
 * SPIRDR读出数据
 * @return SPIRDR 读出的数据
 */
#define SPI_RAED_SPIRDR (SPIRDR)

/**@name 外部函数
 * @{
 */
void SPI_ConfigMode(uint8_t u8MSmode, uint8_t u8mlsb, uint8_t u8workMode);

/**@} */
#endif /* __SPI_H__ */
