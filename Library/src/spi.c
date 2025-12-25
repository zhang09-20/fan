/**
 * @file      spi.c
 * @brief     SPI模块驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "spi.h"

/**
* SPI模式配置
* @param[in] u8MSmode 主/从模式
* -# SPI_SLAVE_NSSI         SPI设置为从机，引脚NSS为输入，作从机的片选信号
* -# SPI_MULTI_MASTER_NSSI  SPI设置为主机且多主机，引脚NSS为输入
* -# SPI_SINGLE_MASTER_NSSO SPI设置为单主机，引脚NSS为输出
* @param[in] u8mlsb 传输起始位配置
* -# SPI_MSB_MODE:从最高位开始传输
* -# SPI_LSB_MODE:从最低位开始传输
* @param[in] u8workMode 工作模式配置位
* -# SPI_MODE0
* -# SPI_MODE1
* -# SPI_MODE2
* -# SPI_MODE3
* @note 通过CPOL和CPHA配置SPI模式 \n
@verbatim
  CPOL  CPHA  MODE
  0      0    mode0
  0      1    mode1
  1      0    mode2
  1      1    mode3
@endverbatim
*/
void SPI_ConfigMode(uint8_t u8MSmode, uint8_t u8mlsb, uint8_t u8workMode)
{
    SPI_SPICFG_MS_SET((u8MSmode >> 1) & 0x01); /* 模式选择 */
    SPI_SPICFG_OENMST_SET(u8MSmode & 0x01);
    SPI_SPICFG_MSB_SET(u8mlsb);
    SPI_SPIMOD_CPOL_SET((u8workMode >> 1) & 0x01); /* 模式选择 */
    SPI_SPIMOD_CPHA_SET(u8workMode & 0x01);
}
