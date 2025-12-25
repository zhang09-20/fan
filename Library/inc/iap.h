/**
 * @file      iap.h
 * @brief     IAP驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __IAP_H__
#define __IAP_H__

#include "WY8S9003xx.h"

/**@name CHPCON(TA保护)
 * @{
 */
/**
 * IAP错误标志
 * @return 1:（1）访问地址超过其大小的区域\n
 *           （2）IAPCN命令无效\n
 *           （3）IAP擦除或编程操作要更新没有使能的区域\n
 *           （4）当CONFIG.BOIAP为1、BODEN(BODCON0.7)为1以及BORST（BODCON0.2）为0时，擦除或编程工作在VBOD下
 * @note 该位需要手动写1清0
 */
#define IS_IAPFF_FLAG ((CHPCON & BIT6) >> 6)
#define CLR_IAPFF_FLAG                                                                                                 \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        CHPCON |= BIT6;                                                                                                \
    }
/**
 * 复位后MCU由LDROM启动
 */
#define MCU_START_LDROM                                                                                                \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        CHPCON &= ~BIT1;                                                                                               \
    }
/**
 * 复位后MCU由APROM启动
 */
#define MCU_START_APROM                                                                                                \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        CHPCON |= BIT1;                                                                                                \
    }
/**
 * 禁用IAP功能
 */
#define DISABLE_IAP                                                                                                    \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        CHPCON &= ~BIT0;                                                                                               \
    }
/**
 * 使能IAP功能
 */
#define ENABLE_IAP                                                                                                     \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        CHPCON |= BIT0;                                                                                                \
    }
/**@} */

/**@name IAPUEN(TA保护)
 * @{
 */
/**
 * 禁用IAP擦除或者编程CONFIG
 */
#define DISABLE_CFUEN                                                                                                  \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN &= ~BIT2;                                                                                               \
    }
/**
 * 使能IAP擦除或者编程CONFIG
 */
#define ENABLE_CFUEN                                                                                                   \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN |= BIT2;                                                                                                \
    }
/**
 * 禁用IAP擦除或者编程LDROM
 */
#define DISABLE_LDUEN                                                                                                  \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN &= ~BIT1;                                                                                               \
    }
/**
 * 使能IAP擦除或者编程LDROM
 */
#define ENABLE_LDUEN                                                                                                   \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN |= BIT1;                                                                                                \
    }
/**
 * 禁用IAP擦除或者编程APROM
 */
#define DISABLE_APUEN                                                                                                  \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN &= ~BIT0;                                                                                               \
    }
/**
 * 使能IAP擦除或者编程APROM
 */
#define ENABLE_APUEN                                                                                                   \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPUEN |= BIT0;                                                                                                \
    }
/**@} */

/**@name IAPTRG(TA保护)
 * @{
 */
/**
 * IAP开始执行
 */
#define ENABLE_IAPGO                                                                                                   \
    {                                                                                                                  \
        TA = 0xAA;                                                                                                     \
        TA = 0x55;                                                                                                     \
        IAPTRG |= BIT0;                                                                                                \
    }
/**
 * IAP执行结果状态
 * @return  1:IAP正在执行\n
 *          0:IAP执行完成
 */
#define IS_IAPGO_FLAG (IAPTRG & 0x01)
/**@} */

/**@name IAPCN
 * @{
 */
#define AP_READ_BYTE     (0x00)                  /*!< IAPB[1:0]:00  FOEN:0 FCEN:0 FCTRL[3:0]:0000*/
#define AP_REASE_PAGE    (0x22)                  /*!< IAPB[1:0]:00  FOEN:1 FCEN:0 FCTRL[3:0]:0010*/
#define AP_WRITE_BYTE    (0x21)                  /*!< IAPB[1:0]:00  FOEN:1 FCEN:0 FCTRL[3:0]:0001*/
#define LD_READ_BYTE     (0x40)                  /*!< IAPB[1:0]:01  FOEN:0 FCEN:0 FCTRL[3:0]:0000*/
#define LD_REASE_PAGE    (0x62)                  /*!< IAPB[1:0]:01  FOEN:1 FCEN:0 FCTRL[3:0]:0010*/
#define LD_WRITE_BYTE    (0x61)                  /*!< IAPB[1:0]:01  FOEN:1 FCEN:0 FCTRL[3:0]:0001*/

#define APROM_READ_BYTE  (IAPCN = AP_READ_BYTE)  /*!< APROM字节读 */
#define APROM_REASE_PAGE (IAPCN = AP_REASE_PAGE) /*!< APROM页擦除 */
#define APROM_WRITE_BYTE (IAPCN = AP_WRITE_BYTE) /*!< APROM字节编程 */
#define LDROM_READ_BYTE  (IAPCN = LD_READ_BYTE)  /*!< LDROM字节读 */
#define LDROM_REASE_PAGE (IAPCN = LD_REASE_PAGE) /*!< LDROM页擦除 */
#define LDROM_WRITE_BYTE (IAPCN = LD_WRITE_BYTE) /*!< LDROM字节编程 */

#define ROM_PAGE_NUM     (128)                   /*!< LDROM或APROM一个page的大小为128字节 */
#define APROM_END_ADDR   (16 * 1024 - 1)         /*!< APROM的结束地址 */

#define COMPANY_ID_CMD   (0x0B)
#define CHIP_ID_CMD      (0x0C)
#define UID_ID_CMD       (0x04)

#define READ_COMPANY_ID  (IAPCN = COMPANY_ID_CMD) /*!< 读公司ID*/
#define READ_CHIP_ID     (IAPCN = CHIP_ID_CMD)    /*!< 读器件ID*/
#define READ_UID_ID      (IAPCN = UID_ID_CMD)     /*!< 读96位UID*/
/**@} */

/**@name IAP地址
 * @{
 */
/**
 * IAP操作地址
 * @param[in] u16addr IAP操作地址(位宽:16bit)
 */
#define IAP_ADDR(u16addr)                                                                                              \
    IAPAH = ((u16addr) >> 8) & 0xFF;                                                                                   \
    IAPAL = ((u16addr) >> 0) & 0xFF
/**@} */

/**@name IAP数据
 * @{
 */
/**
 * IAP执行结果状态
 * @return  IAP数据(位宽:8bit)
 */
#define IAP_DATA (IAPFD)
/**@} */

/**@name 外部函数
 * @{
 */
void     LDROM_Read(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size);
void     LDROM_ErasePage(uint16_t u16Addr);
void     LDROM_Write(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size);
void     APROM_Read(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size);
void     APROM_ErasePage(uint16_t u16Addr);
void     APROM_Write(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size);
uint8_t  Read_CompanyID(void);
void     Read_ChipID(uint8_t *u8IdBuf);
void     Read_UID(uint8_t *u8IdBuf);
uint16_t IAP_GetChipBandGap(void);
/**@} */

#endif /* __IAP_H__ */
